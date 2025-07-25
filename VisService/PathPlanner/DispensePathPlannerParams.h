#pragma once
#include "../Basic/BasicObject.h"
#include <QPointF>

VISSERVICE_NAMESPACE_BEGIN

enum class DispenserMechanicalStructureMode
{
	Together,//点胶头和相机一体
	Separate,//点胶头和相机分离
};

enum class DispenserOperationMode
{
	Camera,//相机模式
	Needle,//针头模式
};

struct PlanDispensePathParams
{
	DispenserMechanicalStructureMode dispenserMechanicalStructureMode_;
	WorkStation stationModel_;
	WorkStation stationCurrent_;
	double relativeAngleToTemplate_;
	QPointF relativePositionToTemplate_;//匹配到的模板中心点坐标（轴参考系）
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
	Needle,//转换到针头轴坐标系
	Camera,//转换到相机轴坐标系
};

struct TransformWorkCoord2ImageCoordParams
{
	QPointF workCoorPt_; //当前需要转换的机械点坐标
	QPointF cameraCoorPt_;	//当前相机轴机械坐标
	WorkStation stationCurrent_;//对应的工位信息
};

struct TransformWorkCoord2ImageCoordParams_Together : public TransformWorkCoord2ImageCoordParams
{

};

struct TransformWorkCoord2ImageCoordParams_Separate : public TransformWorkCoord2ImageCoordParams
{
	TransformCoorType type_;//使用那个轴坐标系下（针头轴\相机轴）
	QString m_syringeNeedlePositionCalibrateName_;//当前工位针头位置标定参数名(使用针头轴必须输入此参数)
};


struct  Transform2TemplateCoordParams
{
	QPointF trajectoryPt_;		//当前轨迹点位置坐标（绝对机械坐标）
	QPointF positionWorkCoor_;	//匹配坐标（机械）
	double angle_;				//匹配角度
};



VISSERVICE_NAMESPACE_END