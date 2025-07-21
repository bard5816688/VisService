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

#include "param_loader.h"    // ����������
#include "image_loader_node.h"
#include "image_filter_node.h"
#include "image_display_node.h"

VISSERVICE_NAMESPACE_BEGIN

class TaskFlowManager
{
public:
    explicit TaskFlowManager(const QString& flowName);
    // ��������JSON�ļ�
    bool loadFlowFromJson(const QString& jsonFile);
    // �����������ݴ����ڵ㣬����CGraphͼ�ṹ
    bool buildGraph();
    // ����������
    bool runFlow();

private:
    QString flowName_;                      // ��������
    QJsonObject flowJson_;                  // ����������JSON����

    QMap<QString, QSharedPointer<BaseNode>> moduleNodes_;  // ģ��ID -> ģ��ʵ��
    QMap<QString, CGraph::GNode*> graphNodes_;             // ģ��ID -> CGraph�ڵ�
    CGraph::GElement* root_ = nullptr;     // CGraph���ڵ�

private:
    // ����ģ��ʵ����������
    QSharedPointer<BaseNode> createModuleInstance(const QString& type);
    // ����input_bindings������ģ�������
    bool parseAndConnectBindings();
    // ����CGraph�ڵ�
    void connectGraphNodes();
    // ����ģ�����в���
    void loadModuleParams();
    // ����ȫ�ֱ���
    QMap<QString, QVariant> globalVars_;
    // ����ȫ�ֱ���JSON����
    void parseGlobalVars(const QJsonObject& globals);
};


VISSERVICE_NAMESPACE_END