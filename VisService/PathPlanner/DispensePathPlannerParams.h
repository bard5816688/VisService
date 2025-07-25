#pragma once
#include "../Basic/BasicObject.h"
#include <QPointF>

VISSERVICE_NAMESPACE_BEGIN

enum class DispenserOperationMode
{
	Camera,//���ģʽ
	Needle,//��ͷģʽ
};

struct PlanDispensePathParams
{
	DispenserOperationMode dispenserOperationMode_;
	WorkStation stationModel_;
	WorkStation stationCurrent_;
	double relativeAngleToTemplate_;
	QPointF relativePositionToTemplate_;//ƥ�䵽��ģ�����ĵ����꣨��ο�ϵ��
	std::vector<QPointF> dispensingPath_;

};

enum class TransformCoorType
{
	Needle,//ת������ͷ������ϵ
	Camera,//ת�������������ϵ
};

struct TransformWorkCoord2ImageCoordParams
{
	QPointF workCoorPt_; //��ǰ��Ҫת���Ļ�е������
	QPointF cameraCoorPt_;	//��ǰ������е����
	WorkStation stationCurrent_;//��Ӧ�Ĺ�λ��Ϣ
};

struct  Transform2TemplateCoordParams
{
	QPointF dispensingPath_;		//��ǰ�켣��λ�����꣨���Ի�е���꣩
	QPointF positionWorkCoor_;		//ƥ�����꣨��е��
	double angle_;					//ƥ��Ƕ�
};



VISSERVICE_NAMESPACE_END