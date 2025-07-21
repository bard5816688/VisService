#pragma once
#include <QObject>
#include <QString>
#include <QMap>
#include <QJsonObject>
#include <QJsonArray>
#include <QSharedPointer>
#include <QVariant>
#include <QDebug>
#include "BaseNode.h"
#include "BasicDefs.h"
#include "CGraph.h"

#include "param_loader.h"    // 参数加载器
#include "image_loader_node.h"
#include "image_filter_node.h"
#include "image_display_node.h"

VISSERVICE_NAMESPACE_BEGIN

class TaskFlowManager
{
public:
    explicit TaskFlowManager(const QString& flowName);
    // 加载流程JSON文件
    bool loadFlowFromJson(const QString& jsonFile);
    // 根据流程数据创建节点，建立CGraph图结构
    bool buildGraph();
    // 运行任务流
    bool runFlow();

private:
    QString flowName_;                      // 流程名称
    QJsonObject flowJson_;                  // 解析的流程JSON对象

    QMap<QString, QSharedPointer<BaseNode>> moduleNodes_;  // 模块ID -> 模块实例
    QMap<QString, CGraph::GNode*> graphNodes_;             // 模块ID -> CGraph节点
    CGraph::GElement* root_ = nullptr;     // CGraph根节点

private:
    // 创建模块实例工厂函数
    QSharedPointer<BaseNode> createModuleInstance(const QString& type);
    // 解析input_bindings，建立模块间连接
    bool parseAndConnectBindings();
    // 连接CGraph节点
    void connectGraphNodes();
    // 加载模块自有参数
    void loadModuleParams();
    // 加载全局变量
    QMap<QString, QVariant> globalVars_;
    // 解析全局变量JSON对象
    void parseGlobalVars(const QJsonObject& globals);
};


VISSERVICE_NAMESPACE_END