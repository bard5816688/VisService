#pragma once
#include "../Basic/BasicObject.h"
#include <QPointF>

VISSERVICE_NAMESPACE_BEGIN

enum class DispenserMechanicalStructureMode
{
	Together,//�㽺ͷ�����һ��
	Separate,//�㽺ͷ���������
};

enum class DispenserOperationMode
{
	Camera,//���ģʽ
	Needle,//��ͷģʽ
};

struct PlanDispensePathParams
{
	DispenserMechanicalStructureMode dispenserMechanicalStructureMode_;
	WorkStation stationModel_;
	WorkStation stationCurrent_;
	double relativeAngleToTemplate_;
	QPointF relativePositionToTemplate_;//ƥ�䵽��ģ�����ĵ����꣨��ο�ϵ��
	std::vector<QPointF> dispensingPath_;

};

struct PlanDispensePathParams_Together : public PlanDispensePathParams
{

};

struct PlanDispensePathParams_Separate : public PlanDispensePathParams
{
	DispenserOperationMode dispenserOperationMode_;
	QString syringeNeedlePositionCalibrateName_;
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

struct TransformWorkCoord2ImageCoordParams_Together : public TransformWorkCoord2ImageCoordParams
{

};

struct TransformWorkCoord2ImageCoordParams_Separate : public TransformWorkCoord2ImageCoordParams
{
	TransformCoorType type_;//ʹ���Ǹ�������ϵ�£���ͷ��\����ᣩ
	QString m_syringeNeedlePositionCalibrateName_;//��ǰ��λ��ͷλ�ñ궨������(ʹ����ͷ���������˲���)
};


struct  Transform2TemplateCoordParams
{
	QPointF trajectoryPt_;		//��ǰ�켣��λ�����꣨���Ի�е���꣩
	QPointF positionWorkCoor_;	//ƥ�����꣨��е��
	double angle_;				//ƥ��Ƕ�
};



VISSERVICE_NAMESPACE_END