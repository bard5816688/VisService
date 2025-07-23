#pragma once
#include <QMap>
#include <QObject>
#include "ML_Global.h"

namespace MN_DeviceVisionError
{
    //模块代码：3位
    enum ME_VisionModelCode
    {
        VISIONMODELCODE_DEVICE = 600               //硬件模块
    };

    const QMap<ME_VisionModelCode, QString> g_VisionModelCode =
    {
        { VISIONMODELCODE_DEVICE, QObject::tr("视觉硬件模块") }
    };

    //错误代码：6位 
    //编码范围 101000~102999软件分配给视觉使用
    //100050-100099  硬件错误
    enum ME_VisionErrorCode
    {
        VISION_ERRORCODE_DEVICEOK = 100050,
        VISION_ERRORCODE_CAMERA_CONNECT_FAILED = 100051,            //通讯连接失败
        VISION_ERRORCODE_CAMERA_OPEN_FAILED = 100060,               //工业相机 100060~100069
        VISION_ERRORCODE_CAMERA_PARAM_ERROR,
        VISION_ERRORCODE_CAMERA_FRAMLOSS,
        VISION_ERRORCODE_LIGHT_CONNECT_FAILED = 100070,             //光源控制器 100070~100079
        VISION_ERRORCODE_LIGHT_PARAM_ERROR,			                //设置光源参数失败
    };

    const QMap<ME_VisionErrorCode, QString> g_VisionErrorCode =
    {
        { VISION_ERRORCODE_DEVICEOK, QObject::tr("硬件正常!") },
        { VISION_ERRORCODE_CAMERA_CONNECT_FAILED, QObject::tr("相机连接失败!") },
        { VISION_ERRORCODE_CAMERA_OPEN_FAILED, QObject::tr("相机打开失败!") },
        { VISION_ERRORCODE_CAMERA_PARAM_ERROR, QObject::tr("相机参数错误!") },
        { VISION_ERRORCODE_CAMERA_FRAMLOSS, QObject::tr("相机丢帧!") },
        { VISION_ERRORCODE_LIGHT_CONNECT_FAILED, QObject::tr("光源连接失败!") },
        { VISION_ERRORCODE_LIGHT_PARAM_ERROR, QObject::tr("光源参数错误!") },
    };

    struct MS_DeviceVisionErrorInfo
    {
        MS_DeviceVisionErrorInfo()
        {
        };
        MS_DeviceVisionErrorInfo(int _modelCode, int _errorcode) : m_modelCode(_modelCode), m_errorcode(_errorcode)
        {
        }
        int m_modelCode = ME_VisionModelCode::VISIONMODELCODE_DEVICE;
        int m_errorcode = ME_VisionErrorCode::VISION_ERRORCODE_CAMERA_CONNECT_FAILED;
    };

    class MI_DeviceVisionError
    {
    public:
        static QString getDeviceModelString(int  _modelCode)                       //获取模块字符串
        {
            if (!g_VisionModelCode.contains(ME_VisionModelCode(_modelCode)))
            {
                return "";
            }
            return g_VisionModelCode[ME_VisionModelCode(_modelCode)];
        }

        static QString getDeviceErrorString(int _errorCode)                       //获取错误字符串
        {
            if (!g_VisionErrorCode.contains(ME_VisionErrorCode(_errorCode)))
            {
                return "";
            }
            return g_VisionErrorCode[ME_VisionErrorCode(_errorCode)];
        }

        static QString getDeviceVisionErrorString(const MS_DeviceVisionErrorInfo& _visionErrorInfo)           //获取完整的错误字符串
        {
            return QString("%1 : %2").arg(getDeviceModelString(_visionErrorInfo.m_modelCode)).arg(getDeviceErrorString(_visionErrorInfo.m_errorcode));
        }
    };


}
