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
        qWarning() << "�޷��������ļ���" << jsonFile;
        return false;
    }

    QByteArray data = file.readAll();
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(data, &err);
    if (err.error != QJsonParseError::NoError)
    {
        qWarning() << "����JSON��������:" << err.errorString();
        return false;
    }

    flowJson_ = doc.object();

    // ����ȫ�ֱ���
    if (flowJson_.contains("global_vars") && flowJson_["global_vars"].isObject())
    {
        parseGlobalVars(flowJson_["global_vars"].toObject());
    }

    // ����ģ��ڵ�
    if (!flowJson_.contains("nodes") || !flowJson_["nodes"].isArray())
    {
        qWarning() << "�����ļ�ȱ�� nodes ����";
        return false;
    }

    const QJsonArray nodesArray = flowJson_["nodes"].toArray();

    // �����ʷ����
    moduleNodes_.clear();
    graphNodes_.clear();

    // ����ģ��ʵ��
    for (auto nodeVal : nodesArray)
    {
        if (!nodeVal.isObject())
            continue;
        QJsonObject nodeObj = nodeVal.toObject();

        QString id = nodeObj["id"].toString();
        QString type = nodeObj["type"].toString();

        if (id.isEmpty() || type.isEmpty())
        {
            qWarning() << "ģ��ID������Ϊ�գ����Ըýڵ�";
            continue;
        }

        // ����ģ��ʵ��
        QSharedPointer<BaseNode> mod = createModuleInstance(type);
        if (!mod)
        {
            qWarning() << "δ֪ģ�����ͣ�" << type;
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

    // TODO: ��չ����ģ��

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
        qWarning() << "û��ģ��ڵ㣬�޷�����ͼ";
        return false;
    }

    // ���� CGraph ���ڵ�
    root_ = new CGraph::GElement("root");
    if (!root_)
        return false;

    graphNodes_.clear();

    // ���� GNode����ע��ģ���߼�
    for (auto it = moduleNodes_.begin(); it != moduleNodes_.end(); ++it)
    {
        CGraph::GNode* gnode = new CGraph::GNode(it.key().toStdString());
        gnode->setLogic(it.value().data()); // ��ģ���߼�������ȷ��BaseNode�̳���CGraph::GElement::ILogic�ӿ�
        graphNodes_[it.key()] = gnode;

        root_->addNode(gnode);
    }

    // ���� input_bindings ����������
    if (!parseAndConnectBindings())
        return false;

    // ����ÿ��ģ������в���
    loadModuleParams();

    return true;
}

bool TaskFlowManager::parseAndConnectBindings()
{
    if (!flowJson_.contains("nodes") || !flowJson_["nodes"].isArray())
        return false;
    const QJsonArray nodesArray = flowJson_["nodes"].toArray();

    // ��������ģ��ڵ�
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

        // ����ÿ����
        for (auto it = bindings.begin(); it != bindings.end(); ++it)
        {
            QString inputName = it.key();
            QString bindStr = it.value().toString();

            if (bindStr.startsWith("$global."))
            {
                // �󶨵�ȫ�ֱ���
                QString globalVarName = bindStr.mid(QString("$global.").length());
                if (globalVars_.contains(globalVarName))
                {
                    QVariant val = globalVars_[globalVarName];
                    mod->setInputParameter(inputName, val);
                }
                else
                {
                    qWarning() << "ȫ�ֱ���δ����:" << globalVarName;
                }
            }
            else
            {
                // ������ģ���������ʽ�� moduleId.paramName
                QStringList parts = bindStr.split(".");
                if (parts.size() != 2)
                {
                    qWarning() << "����󶨸�ʽ����:" << bindStr;
                    continue;
                }
                QString srcModule = parts[0];
                QString outputName = parts[1];

                if (!graphNodes_.contains(srcModule))
                {
                    qWarning() << "�󶨵�Դģ�鲻����:" << srcModule;
                    continue;
                }

                // CGraph���ӣ�srcModule.outputName -> mod.inputName
                // �����������ģ��GNode�Ķ˿����Ƽ�Ϊ��������
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

        // �����ݿ��ж�ȡģ�����в���
        QJsonObject params = ParamLoader::loadModuleParams(flowName_, moduleId);

        mod->loadParams(params); // ��ģ������ʵ�ֲ�������
    }
}

bool TaskFlowManager::runFlow()
{
    if (!root_)
    {
        qWarning() << "������δ�������޷�����";
        return false;
    }

    CGraph::GResult result = root_->run();

    if (result.isOK())
    {
        qInfo() << "������ִ�гɹ�";
        return true;
    }
    else
    {
        qWarning() << "������ִ��ʧ��";
        return false;
    }
}

VISSERVICE_NAMESPACE_END