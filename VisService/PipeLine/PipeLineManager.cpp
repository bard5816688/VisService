#include "PipeLineManager.h"
#include <QFile>
#include <QJsonDocument>

VISSERVICE_NAMESPACE_BEGIN

TaskFlowManager::TaskFlowManager(const QString& flowName)
    : flowName_(flowName)
{
}

bool TaskFlowManager::loadFlowFromJson(const QString& jsonFile)
{
    QFile file(jsonFile);
    if (!file.open(QIODevice::ReadOnly))
    {
        qWarning() << "无法打开流程文件：" << jsonFile;
        return false;
    }

    QByteArray data = file.readAll();
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(data, &err);
    if (err.error != QJsonParseError::NoError)
    {
        qWarning() << "流程JSON解析错误:" << err.errorString();
        return false;
    }

    flowJson_ = doc.object();

    // 解析全局变量
    if (flowJson_.contains("global_vars") && flowJson_["global_vars"].isObject())
    {
        parseGlobalVars(flowJson_["global_vars"].toObject());
    }

    // 解析模块节点
    if (!flowJson_.contains("nodes") || !flowJson_["nodes"].isArray())
    {
        qWarning() << "流程文件缺少 nodes 数组";
        return false;
    }

    const QJsonArray nodesArray = flowJson_["nodes"].toArray();

    // 清空历史数据
    moduleNodes_.clear();
    graphNodes_.clear();

    // 创建模块实例
    for (auto nodeVal : nodesArray)
    {
        if (!nodeVal.isObject())
            continue;
        QJsonObject nodeObj = nodeVal.toObject();

        QString id = nodeObj["id"].toString();
        QString type = nodeObj["type"].toString();

        if (id.isEmpty() || type.isEmpty())
        {
            qWarning() << "模块ID或类型为空，忽略该节点";
            continue;
        }

        // 创建模块实例
        QSharedPointer<BaseNode> mod = createModuleInstance(type);
        if (!mod)
        {
            qWarning() << "未知模块类型：" << type;
            continue;
        }
        mod->setId(id);

        moduleNodes_[id] = mod;
    }

    return true;
}

QSharedPointer<BaseNode> TaskFlowManager::createModuleInstance(const QString& type)
{
    if (type == "ImageLoader")
        return QSharedPointer<BaseNode>(new ImageLoaderNode());
    else if (type == "ImageFilter")
        return QSharedPointer<BaseNode>(new ImageFilterNode());
    else if (type == "ImageDisplay")
        return QSharedPointer<BaseNode>(new ImageDisplayNode());

    // TODO: 扩展更多模块

    return nullptr;
}

void TaskFlowManager::parseGlobalVars(const QJsonObject& globals)
{
    globalVars_.clear();
    for (auto it = globals.begin(); it != globals.end(); ++it)
    {
        globalVars_[it.key()] = it.value().toVariant();
    }
}

bool TaskFlowManager::buildGraph()
{
    if (moduleNodes_.isEmpty())
    {
        qWarning() << "没有模块节点，无法构建图";
        return false;
    }

    // 创建 CGraph 根节点
    root_ = new CGraph::GElement("root");
    if (!root_)
        return false;

    graphNodes_.clear();

    // 创建 GNode，并注册模块逻辑
    for (auto it = moduleNodes_.begin(); it != moduleNodes_.end(); ++it)
    {
        CGraph::GNode* gnode = new CGraph::GNode(it.key().toStdString());
        gnode->setLogic(it.value().data()); // 绑定模块逻辑对象，需确保BaseNode继承自CGraph::GElement::ILogic接口
        graphNodes_[it.key()] = gnode;

        root_->addNode(gnode);
    }

    // 解析 input_bindings 并建立连接
    if (!parseAndConnectBindings())
        return false;

    // 载入每个模块的自有参数
    loadModuleParams();

    return true;
}

bool TaskFlowManager::parseAndConnectBindings()
{
    if (!flowJson_.contains("nodes") || !flowJson_["nodes"].isArray())
        return false;
    const QJsonArray nodesArray = flowJson_["nodes"].toArray();

    // 遍历所有模块节点
    for (auto nodeVal : nodesArray)
    {
        if (!nodeVal.isObject())
            continue;
        QJsonObject nodeObj = nodeVal.toObject();

        QString modId = nodeObj["id"].toString();
        if (!moduleNodes_.contains(modId))
            continue;

        auto mod = moduleNodes_[modId];
        CGraph::GNode* gnode = graphNodes_.value(modId, nullptr);
        if (!gnode)
            continue;

        // input_bindings: inputName -> binding string ("otherModule.outputParam" or "$global.var")
        if (!nodeObj.contains("input_bindings"))
            continue;
        if (!nodeObj["input_bindings"].isObject())
            continue;

        QJsonObject bindings = nodeObj["input_bindings"].toObject();

        // 解析每个绑定
        for (auto it = bindings.begin(); it != bindings.end(); ++it)
        {
            QString inputName = it.key();
            QString bindStr = it.value().toString();

            if (bindStr.startsWith("$global."))
            {
                // 绑定到全局变量
                QString globalVarName = bindStr.mid(QString("$global.").length());
                if (globalVars_.contains(globalVarName))
                {
                    QVariant val = globalVars_[globalVarName];
                    mod->setInputParameter(inputName, val);
                }
                else
                {
                    qWarning() << "全局变量未定义:" << globalVarName;
                }
            }
            else
            {
                // 绑定其他模块输出，格式： moduleId.paramName
                QStringList parts = bindStr.split(".");
                if (parts.size() != 2)
                {
                    qWarning() << "输入绑定格式错误:" << bindStr;
                    continue;
                }
                QString srcModule = parts[0];
                QString outputName = parts[1];

                if (!graphNodes_.contains(srcModule))
                {
                    qWarning() << "绑定的源模块不存在:" << srcModule;
                    continue;
                }

                // CGraph连接：srcModule.outputName -> mod.inputName
                // 这里假设所有模块GNode的端口名称即为参数名称
                gnode->addInput(inputName);
                graphNodes_[srcModule]->addOutput(outputName);

                root_->addEdge(graphNodes_[srcModule], outputName.toStdString(),
                    gnode, inputName.toStdString());
            }
        }
    }

    return true;
}

void TaskFlowManager::loadModuleParams()
{
    for (auto it = moduleNodes_.begin(); it != moduleNodes_.end(); ++it)
    {
        QString moduleId = it.key();
        QSharedPointer<BaseNode> mod = it.value();

        // 从数据库中读取模块自有参数
        QJsonObject params = ParamLoader::loadModuleParams(flowName_, moduleId);

        mod->loadParams(params); // 由模块自行实现参数加载
    }
}

bool TaskFlowManager::runFlow()
{
    if (!root_)
    {
        qWarning() << "任务流未构建，无法运行";
        return false;
    }

    CGraph::GResult result = root_->run();

    if (result.isOK())
    {
        qInfo() << "任务流执行成功";
        return true;
    }
    else
    {
        qWarning() << "任务流执行失败";
        return false;
    }
}

VISSERVICE_NAMESPACE_END