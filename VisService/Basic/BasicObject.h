﻿#pragma once
#include "ReturnDefs.h"
#include <QJsonObject>
#include <QObject>

VISSERVICE_NAMESPACE_BEGIN

class BasicObject
{
public:
	virtual ~BasicObject()
	{
	}

};

struct AxisParams
{
	AxisParams(double _x = 0, double _y = 0, double _z = 0, double _u = 0, double _t = 0)
	{
		x_ = _x;
		y_ = _y;
		z_ = _z;
		u_ = _u;
		t_ = _t;
	}

	QJsonObject toJson()
	{
		QJsonObject jsonObj;
		jsonObj.insert("x_", x_);
		jsonObj.insert("y_", y_);
		jsonObj.insert("z_", z_);
		jsonObj.insert("u_", u_);
		jsonObj.insert("t_", t_);

		return jsonObj;
	}

	void fromJson(const QJsonObject& _jsonObj)
	{
		if (_jsonObj.isEmpty())
		{
			return;
		}

		x_ = _jsonObj.value("x_").toDouble();
		y_ = _jsonObj.value("y_").toDouble();
		z_ = _jsonObj.value("z_").toDouble();
		u_ = _jsonObj.value("u_").toDouble();
		t_ = _jsonObj.value("t_").toDouble();

	}

	double x_;                            
	double y_;                            
	double z_;                            
	double u_;                            
	double t_;                            
};

enum class AcquisitionType
{
	StaticAcquisition,
	OtfAcquisition,
};

struct WorkStation
{
	int cameraNum_;
	int stationNum_;
};

struct VisInitParams
{
	//std::map<int, MN_VisionDevice::MS_StationInformation> allStstionInfoMap;
};

enum class VisOperationMode
{
	PRODUCTION,
	DEBUGING,
};


VISSERVICE_NAMESPACE_END