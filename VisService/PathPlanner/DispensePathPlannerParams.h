#pragma once
#include "../Basic/BasicObject.h"
#include <QPointF>

VISSERVICE_NAMESPACE_BEGIN

enum class DispenserOperationMode
{
	Camera,//相机模式
	Needle,//针头模式
};

struct PlanDispensePathParams
{
	DispenserOperationMode dispenserOperationMode_;
	WorkStation stationModel_;
	WorkStation stationCurrent_;
	double relativeAngleToTemplate_;
	QPointF relativePositionToTemplate_;//匹配到的模板中心点坐标（轴参考系）
	std::vector<QPointF> dispensingPath_;

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

struct  Transform2TemplateCoordParams
{
	QPointF dispensingPath_;		//当前轨迹点位置坐标（绝对机械坐标）
	QPointF positionWorkCoor_;		//匹配坐标（机械）
	double angle_;					//匹配角度
};



VISSERVICE_NAMESPACE_END