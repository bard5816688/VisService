#pragma once
#include <QWidget>
#include <QString>
#include <QMutex>
#include <future>
#include "MS_ImageParam.h"
#include "MS_DataDefine.h"
#include "ME_DeviceErrorInfo.h"
#include "ML_Global.h"

using MN_DeviceVisionError::MS_DeviceVisionErrorInfo;
using MN_VisionImage::MS_Image_Param;

class MD_CameraBase;

namespace MN_VisionDevice
{
    //硬件模块基础类
    class MI_DeviceBase
    {
    public:
        virtual ~MI_DeviceBase()
        {
        }

    public:
        virtual MN_DeviceVisionError::MS_DeviceVisionErrorInfo getErrorInfo() = 0;          //获取当前对象执行的错误代码
        virtual bool isValid() = 0;                             //判断当前对象是否可用
    };

    //相机接口
    class DEVICE_LIBRARY_API MI_DeviceCameraInterface
        : public QObject, public MI_DeviceBase
    {
        Q_OBJECT

    public:
        MI_DeviceCameraInterface(ME_CameraNo);
        virtual ~MI_DeviceCameraInterface();
        MN_DeviceVisionError::MS_DeviceVisionErrorInfo getErrorInfo();                                  //获取当前对象执行的错误代码
        bool isValid();                                                     //判断当前对象是否可用

        bool getImageDirect(MS_Image_Param& _image);                        //同步获取图像(效率高)
        bool changeCameraStateSync(ME_CameraSnapState _state);              //修改相机光源参数 切换到系统参数
        bool getImageSync(MS_Image_Param& _image);                          //同步获取图像
        bool getCameraParamSync(MS_CameraParam& _cameraParam);              //同步获取相机参数
        bool setCameraParamSync(const MS_CameraParam& _cameraParam);        //同步设置相机参数

        bool getLightParamSync(MS_LightSettingParam& _lightParam);          //同步获取光源参数
        bool setLightParamSync(const MS_LightSettingParam& _lightParam);//同步设置光源参数

        bool getCameraAndLightParamSync(MS_CameraAndLightSettingParam& _cameraLightParam);                  //同步获取相机光源参数
        bool setCameraAndLightParamSync(const MS_CameraAndLightSettingParam& _cameraLightParam);            //同步设置相机光源参数
        bool setCameraAndLightParamAsyn(const MS_CameraAndLightSettingParam& _cameraLightParam);            //异步设置相机光源参数

        void setStopCapture(bool _isCapture);                                       //设置停止采图
        void setCameraMode(ME_CameraMode _mode);                                    //设置相机触发模式：软触发、硬触发
        void startHardwareTriggerThread();
        void stopHardwareTriggerThread();

        int getCameraResolutionWidth();
        int getCameraResolutionHeight();

        QPointF mapToGlobal(const QPointF& _ptf, int _nRgnIdx = 0);
        bool setRegionEnable(int _nRgnIdx, bool _bOn);
        bool setRegion(int _nWidth, int _nHeight, int _nOffsetX, int _nOffsetY, int _nRgnIdx);
        bool set1RegionSizeByCenter(int _nWidth, int _nHeight);
        bool getImageSizeRange(int& _widthMin, int& _widthMax, int& _heightMin, int& _heightMax);

    signals:
        void SIG_SetDeviceErrorInfo(ME_CameraNo, MN_DeviceVisionError::MS_DeviceVisionErrorInfo);               //发送硬件错误
        void SIG_SetCameraImage(MS_Image_Param);                                    //发送图像信号
        void SIG_SetFlySnapCameraImage(MS_Image_Param);                             //发送飞拍图像信号
        void SIG_sendExposureEnd(ME_CameraNo);                                      //曝光结束
        void SIG_HardWareSatrted();                                                 //飞拍线程启动完成

    private:
        ME_CameraNo m_cameraNo;
        MD_CameraBase* m_cameraImagePtr{ nullptr };
    };

    //初始化硬件模块：光源控制器接口、相机等
    class DEVICE_LIBRARY_API MI_InitDeviceColtrolInterface
        : public QObject, public MI_DeviceBase
    {
        Q_OBJECT

    public:
        static MI_InitDeviceColtrolInterface* getInstance();
        MI_InitDeviceColtrolInterface();
        virtual ~MI_InitDeviceColtrolInterface();
        void initialize();                                                                              //初始化
        MN_DeviceVisionError::MS_DeviceVisionErrorInfo getErrorInfo();                                                              //获取当前对象执行的错误代码
        bool isValid();                                                                                 //判断当前对象是否可用
        bool getDeviceLightControlStateSync(std::map<ME_LightNo, ME_DeviceState>& _cameraState);        //获取光源状态
        bool getDeviceCameraControlStateSync(std::map<ME_CameraNo, ME_DeviceState>& _lightState);       //获取相机状态
        int getDeviceLightNumbersSync();
        int getDeviceLightControlNumbersSync();
        int getDeviceCameraNumbersSync();
        MS_CameraDeviceParameter getCameraDeviceParam(const QString& _strSn);
        MS_VisionStationParameter getVisionStationParam(int _nVisionStationId);
        MS_WorkStationParameter getWorkStationParam(int _nVisionStationId, int _nWorkStationId);
    signals:
        void SIG_SetDeviceLightControlState(std::map<ME_LightNo, ME_DeviceState>);                      //发送光源状态
        void SIG_SetDeviceCameraControlState(std::map<ME_CameraNo, ME_DeviceState>);                    //发送相机状态

    private:
        void finalize();

    private:
        static QMutex m_initDeviceMutex;
        static MI_InitDeviceColtrolInterface* m_instance;
        std::future<void> m_lightControlFuture;
    };

    /*******************************************************************/
    /* 功    能：初始化硬件库【相机、光源、控制器等】
    /* 输入参数：无
    /* 输出参数：
    /* 返 回 值：成功 or 失败
    /* 注：先初始化，然后才能使用
    /*******************************************************************/
    DEVICE_LIBRARY_API MI_InitDeviceColtrolInterface* initDeviceLibrary();

    /*******************************************************************/
    /* 功    能：获取某个视觉模块
    /* 输入参数：_inParam 视觉参数，如相机编号、工位号、标定类型
    /* 输出参数：无
    /* 返 回 值：标定类的指针
    /*******************************************************************/
    DEVICE_LIBRARY_API MI_DeviceCameraInterface* getDeviceCameraOperation(ME_CameraNo _camID);
}
