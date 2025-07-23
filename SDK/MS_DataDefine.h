#pragma once
#include <QObject>
#include <QJsonValue>
#include "MS_ImageParam.h"
#include "MD_CameraParameter.h"
#include "ML_Global.h"
#include <map>
#include <QJsonObject>
#include <QJsonDocument>

#define DEVICE_UNKOWN "device_unkown"

namespace MN_VisionDevice
{
#pragma region Common 
    //硬件状态
    enum ME_DeviceState
    {
        DEVICESTATE_ERROR = -1,
        DEVICESTATE_FAILED,                     //连接失败
        DEVICESTATE_SUCCSED,                    //连接成功
        DEVICESTATE_START,
        DEVICESTATE_BREAK
    };
#pragma endregion

#pragma region Camera
    //相机编号
    enum ME_CameraNo
    {
        CAMERA_NO_NULL = -1,
        CAMERA_NO_1,
        CAMERA_NO_2,
        CAMERA_NO_3,
        CAMERA_NO_4,
        CAMERA_NO_5,
        CAMERA_NO_6,
        CAMERA_NO_7,
        CAMERA_NO_8,
        CAMERA_NO_9,
        CAMERA_NO_10,
        CAMERA_NO_11,
        CAMERA_NO_12,
        CAMERA_NO_13,
        CAMERA_NO_14,
        CAMERA_NO_15,
        CAMERA_NO_MAX
    };

    //光源编号
    enum ME_LightNo
    {
        LIGHT_NO_NULL = -1,
        LIGHT_NO_1,
        LIGHT_NO_2,
        LIGHT_NO_3,
        LIGHT_NO_4,
        LIGHT_NO_5,
        LIGHT_NO_6,
        LIGHT_NO_7,
        LIGHT_NO_8,
        LIGHT_NO_9,
        LIGHT_NO_10,
        LIGHT_NO_11,
        LIGHT_NO_12,
        LIGHT_NO_13,
        LIGHT_NO_14,
        LIGHT_NO_15,
        LIGHT_NO_MAX
    };

    //相机分辨率:行*列
    enum ME_ResolutionKind
    {
        RESOLUTION_KIND_NULL = -1,
        RESOLUTION_KIND_640_480,
        RESOLUTION_KIND_1000_1000,
        RESOLUTION_KIND_1080_1080,
        RESOLUTION_KIND_1200_1200,
        RESOLUTION_KIND_1280_960,
        RESOLUTION_KIND_1520_1520,
        RESOLUTION_KIND_1600_1200,
        RESOLUTION_KIND_1920_1080,
        RESOLUTION_KIND_1920_1200,
        RESOLUTION_KIND_1920_1920,
        RESOLUTION_KIND_2048_1520,
        RESOLUTION_KIND_2048_2048,
        RESOLUTION_KIND_2448_2048,
        RESOLUTION_KIND_1072_1072,
        RESOLUTION_KIND_320_320,
        RESOLUTION_KIND_480_480,
    };

    class MF_ResolutionKind
    {
    public:
        MF_ResolutionKind()
        {
            m_mpResolutionKind = {
                {RESOLUTION_KIND_320_320,{320,320,"320*320"}},
                {RESOLUTION_KIND_480_480,{480,480,"480*480"}},
                {RESOLUTION_KIND_640_480,{640,480,"640*480"}},
                {RESOLUTION_KIND_1000_1000,{1000,1000,"1000*1000"}},
                {RESOLUTION_KIND_1072_1072,{1072,1072,"1072*1072"}},
                {RESOLUTION_KIND_1080_1080,{1080,1080,"1080*1080"}},
                {RESOLUTION_KIND_1200_1200,{1200,1200,"1200*1200"}},
                {RESOLUTION_KIND_1280_960,{1280,960,"1280*960"}},
                {RESOLUTION_KIND_1520_1520,{1520,1520,"1520*1520"}},
                {RESOLUTION_KIND_1600_1200,{1600,1200,"1600*1200"}},
                {RESOLUTION_KIND_1920_1080,{1920,1080,"1920*1080"}},
                {RESOLUTION_KIND_1920_1200,{1920,1200,"1920*1200"}},
                {RESOLUTION_KIND_1920_1920,{1920,1920,"1920*1920"}},
                {RESOLUTION_KIND_2048_1520,{2048,1520,"2048*1520"}},
                {RESOLUTION_KIND_2048_2048,{2048,2048,"2048*2048"}},
            };
            m_mpResolutionKindDescrible =
            {
                {RESOLUTION_KIND_320_320,"320*320"},
                {RESOLUTION_KIND_480_480,"480*480"},
                {RESOLUTION_KIND_640_480,"640*480"},
                {RESOLUTION_KIND_1000_1000,"1000*1000"},
                {RESOLUTION_KIND_1072_1072,"1072*1072"},
                {RESOLUTION_KIND_1080_1080,"1080*1080"},
                {RESOLUTION_KIND_1200_1200,"1200*1200"},
                {RESOLUTION_KIND_1280_960,"1280*960"},
                {RESOLUTION_KIND_1520_1520,"1520*1520"},
                {RESOLUTION_KIND_1600_1200,"1600*1200"},
                {RESOLUTION_KIND_1920_1080,"1920*1080"},
                {RESOLUTION_KIND_1920_1200,"1920*1200"},
                {RESOLUTION_KIND_1920_1920,"1920*1920"},
                {RESOLUTION_KIND_2048_1520,"2048*1520"},
                {RESOLUTION_KIND_2048_2048,"2048*2048"},
            };
        }
        int getWidth(ME_ResolutionKind _enum)
        {
            if (m_mpResolutionKind.find(_enum) != m_mpResolutionKind.end())
            {
                return m_mpResolutionKind.at(_enum).m_nWidth;
            }
            return -1;
        }
        int getHeight(ME_ResolutionKind _enum)
        {
            if (m_mpResolutionKind.find(_enum) != m_mpResolutionKind.end())
            {
                return m_mpResolutionKind.at(_enum).m_nHeight;
            }
            return -1;
        }
        QString getText(ME_ResolutionKind _enum)
        {
            if (m_mpResolutionKind.find(_enum) != m_mpResolutionKind.end())
            {
                return m_mpResolutionKind.at(_enum).m_strText;
            }
            return "";
        }
        ME_ResolutionKind getResolutionEnum(const QString& _strText)
        {
            for (auto var : m_mpResolutionKind)
            {
                if (var.second.m_strText == _strText)
                {
                    return var.first;
                }
            }
            return RESOLUTION_KIND_NULL;
        }
        struct MS_ResolutionKind
        {
            int m_nWidth;
            int m_nHeight;
            QString m_strText;
        };
        std::map<ME_ResolutionKind, MS_ResolutionKind>m_mpResolutionKind;
        std::map<ME_ResolutionKind, QString>m_mpResolutionKindDescrible;
    };
    static MF_ResolutionKind s_ResolutionKind;

    struct MS_CameraCropParameter
    {
        MS_CameraCropParameter()
            : m_eCropImgSize(RESOLUTION_KIND_480_480)
            , m_dProductSizeProportionThreshold(0.8)
        {

        }
        ME_ResolutionKind m_eCropImgSize;//裁剪图像尺寸
        double m_dProductSizeProportionThreshold;//产品尺寸占比阈值
    };

    //相机工作模式
    enum ME_CameraSnapState
    {
        CAMERASNAPSTATE_SYSTEM,             //相机系统状态
        CAMERASNAPSTATE_TASK                //相机任务状态
    };
#pragma endregion

#pragma region Light
    enum ME_LightFactory
    {
        LIGHTFACTORY_MS,
        LIGHTFACTORY_OPT,
        LIGHTFACTORY_JL
    };

    //光源通道号
    enum ME_LightChannel
    {
        LIGHT_CHANNEL_1,
        LIGHT_CHANNEL_2,
        LIGHT_CHANNEL_3,
        LIGHT_CHANNEL_4
    };

    enum ME_LightMode
    {
        LIGHTMODE_NETWORK,                  //网口
        LIGHTMODE_SERIALPORT                //串口
    };

    struct MS_LightSettingParam
    {
        MS_LightSettingParam()
        {
            m_mLightValue.clear();
            m_mLightEnable.clear();
            m_mLightValue = { {1,255},{2,255},{3,255},{4,255} };
            m_mLightEnable = { {1,true},{2,true},{3,true},{4,true} };
            //m_mLightValue = { {1,255} };
            //m_mLightEnable = { {1,true} };
            m_isLink = false;
        }
        std::map<int, int> m_mLightValue;       //光源值<channel,value>
        std::map<int, bool> m_mLightEnable;      //光源使能<channel,value>
        bool m_isLink;					    //是否联动
    };
#pragma endregion

#pragma region CameraAndLight 
    //相机和光源参数
    struct MS_CameraAndLightSettingParam
    {
        MS_CameraAndLightSettingParam()
        {
            m_cameraParam.m_gainRaw = 1;
            m_cameraParam.m_gammaValue = 1.0;
            m_cameraParam.m_exposureTimeAbs = 100;
            m_cameraParam.m_redBalanceRatio = 500;
            m_cameraParam.m_greenBalanceRatio = 500;
            m_cameraParam.m_blueBalanceRatio = 500;
            m_cameraParam.m_isEnableGamma = false;
            m_cameraParam.m_isAutoExposure = false;
        }

        bool DEVICE_LIBRARY_API operator == (const MS_CameraAndLightSettingParam& _param) const;
        QString DEVICE_LIBRARY_API toJson();
        void DEVICE_LIBRARY_API fromJson(const QString& _jsonStr);

        MS_LightSettingParam m_lightParam;  //光源参数
        MS_CameraParam m_cameraParam;		//相机参数
    };

#pragma endregion

#pragma region COMM //通讯
    // 通讯状态
    enum ME_CommStatus
    {
        COMM_STATUAS_CAMERA_1,
        COMM_STATUAS_CAMERA_2,
        COMM_STATUAS_CAMERA_3,
        COMM_STATUAS_CAMERA_4,
        COMM_STATUAS_CAMERA_5,
        COMM_STATUAS_CAMERA_6,
        COMM_STATUAS_LIGHT_1,
        COMM_STATUAS_LIGHT_2,
        COMM_STATUAS_LIGHT_3,
        COMM_STATUAS_LIGHT_4,
        COMM_STATUAS_LIGHT_5,
        COMM_STATUAS_LIGHT_6,
        COMM_STATUAS_MAX
    };
#pragma endregion

    struct MS_VisiomSystemParameterBase
    {
        MS_VisiomSystemParameterBase(const QString& _strDescrible)
            : m_strDescrible(_strDescrible)
        {

        }
        QString m_strDescrible;
    };

/**
 * @brief 跟相机硬件设备相关的参数，跟相机走
 */
    struct MS_CameraDeviceParameter : public MS_VisiomSystemParameterBase
    {
        MS_CameraDeviceParameter()
            : MS_VisiomSystemParameterBase(u8"新建相机")
            , m_serialNum("")
            , m_brand(UNKNOW_BRAND)
            , m_class(UNKNOW_CLASS)
            , m_pixelSize(0.00345)
        {
        }
        QString m_serialNum;																	//序列号
        ME_CameraBrand m_brand;																	//品牌
        ME_CameraDeviceClass m_class;															//接口类型
        double m_pixelSize;																		//相机像元尺寸
    };

    /**
     * @brief 相机的配置参数，属于系统对视觉硬件的配置参数，跟系统走
     */
    struct MS_CameraCfgParameter
    {
        MS_CameraCfgParameter()
            : m_serialNum("")
            , m_isColor(false)
            , m_imageMirrorRotate()
            , m_ResolutionKind(RESOLUTION_KIND_480_480)
            , m_strobeLine(STROBE_LINE_1)
            , m_strobeLineSrc(STROBE_LINE_SOURCE_EXPOSURE_ACTIVE)
            , m_eHardwareTriggerLineSource(STROBE_LINE_0)
        {
        }
        QString m_serialNum;																	//序列号
        bool m_isColor;																			//是否彩色
        MS_ImageMirrorRotate m_imageMirrorRotate;
        ME_ResolutionKind m_ResolutionKind;														//分辨率
        ME_StrobeLine m_strobeLine;																//频闪通道
        ME_StrobeLineSource m_strobeLineSrc;													//频闪通道触发源
        ME_StrobeLine m_eHardwareTriggerLineSource;												//硬触发通道
    };

    /**
     * @brief 镜头的配置参数，属于系统对视觉硬件的配置参数，跟系统走
     * 虽然该结构体中的参数都是硬件相关的参数，但在此处为系统配置的不同的镜头硬件对应的参数
     */
    struct  MS_LensCfgParamter
    {
        MS_LensCfgParamter()
            : m_lensMultiplying(1.0)
            , m_depthOfField(1.0)
        {

        }
        double m_lensMultiplying;
        double m_depthOfField;//景深
    };

    struct MS_VisionCfgParameter
    {
        MS_VisionCfgParameter()
            : m_strCfgDescirble(QObject::tr(u8"新建配置"))
        {

        }
        QString m_strCfgDescirble;//配置描述
        MS_CameraCfgParameter m_cameraCfg;
        MS_LensCfgParamter m_lensCfg;
    };

    enum class ME_VisionCfgType
    {
        VISION_CFG_TYPE0,
        VISION_CFG_TYPE1,
        VISION_CFG_TYPE2,

        VISION_CFG_TYPE_COUNT
    };

    struct MS_VisionStationParameter : public MS_VisiomSystemParameterBase
    {
        MS_VisionStationParameter()
            : MS_VisiomSystemParameterBase(u8"新建配置")
            , m_nVisionStationId(-1)
            , m_LightControllerId(-1)
            , m_eActiveCfg(ME_VisionCfgType::VISION_CFG_TYPE0)
            , m_mpVisionCfgParam({ {ME_VisionCfgType::VISION_CFG_TYPE0,MS_VisionCfgParameter()} })
        {

        }
        int m_nVisionStationId; 																//视觉站点编号
        int m_LightControllerId;																//对应光源控制器编号
        std::map<ME_VisionCfgType, MS_VisionCfgParameter> m_mpVisionCfgParam;			//视觉配置参数（多套配置）
        ME_VisionCfgType m_eActiveCfg;                                                   //正在使用的配置
        MS_CameraCropParameter m_cameraCropParam;
        MS_VisionCfgParameter DEVICE_LIBRARY_API getActiveCfg();
        QJsonObject mpVisionCfgParamToJson();
        void mpVisionCfgParamFromJson(const QJsonObject& _jsonObj);
        bool isConfigured()
        {
            if (m_strDescrible == DEVICE_UNKOWN)
            {
                return false;
            }
            return true;
        }
    };



#define EYEONHAND "eyeOnHand"
#define EYENOTONHAND "eyeNotOnHand"

    struct MS_WorkStationParameter : public MS_VisiomSystemParameterBase
    {
        MS_WorkStationParameter()
            : MS_VisiomSystemParameterBase(u8"新建工位")
            , m_relatedVisionStationId(-1)
            , m_workstationId(-1)
            , m_directionalConsistencyX("positive")
            , m_directionalConsistencyY("positive")
            , m_positionalRelationship(EYEONHAND)
        {

        }
        QString getWorkStationGroupName(ME_VisionCfgType _nVisionCfgId)
        {
            QString strName;
            if (_nVisionCfgId == ME_VisionCfgType::VISION_CFG_TYPE0)//配置0的命名方式兼容老版
            {
                strName = QString("camera_%1_workStation_%2_calib").arg(m_relatedVisionStationId).arg(m_workstationId);
            }
            else
            {
                strName = QString("camera_%1_workStation_%2_HandEyeType%3calib").arg(m_relatedVisionStationId).arg(m_workstationId).arg(static_cast<int>(_nVisionCfgId));
            }
            return strName;
        }

        bool isConfigured()
        {
            if (m_strDescrible == DEVICE_UNKOWN)
            {
                return false;
            }
            return true;
        }

        int m_relatedVisionStationId; 															//相关联的视觉站点编号
        int m_workstationId;
        QString m_directionalConsistencyX;														//相关相机和轴参考坐标系的X方向的一致性（参考坐标系统一为操作员面对机器）
        QString m_directionalConsistencyY;														//相关相机和轴参考坐标系的Y方向的一致性（参考坐标系统一为操作员面对机器）
        QString m_positionalRelationship;														//手眼位置关系
    };

    typedef std::vector<MS_WorkStationParameter> WorkStationParamterVector;
    typedef std::vector<MS_VisionStationParameter> VisionStationParamVector;
    typedef std::vector<MS_CameraDeviceParameter> CameraDeviceParamVector;

    struct MS_StationInformation
    {
        QString m_strDescrible = "";		//工位描述信息
        double m_dPositiveLimitX = 10;		//X正极限(mm)
        double m_dNegativeLimitX = 0;		//X负极限(mm)
        double m_dPositiveLimitY = 10;		//Y正极限(mm)
        double m_dNegativeLimitY = 0;		//Y负极限(mm)
        MS_StationInformation() :m_strDescrible(""), m_dPositiveLimitX(10), m_dNegativeLimitX(0), m_dPositiveLimitY(10), m_dNegativeLimitY(0)
        {
        }
        MS_StationInformation(QString _strDescrible, double _dPositiveLimitX, double _dNegativeLimitX, double _dPositiveLimitY, double _dNegativeLimitY)
        {
            m_strDescrible = _strDescrible;
            m_dPositiveLimitX = _dPositiveLimitX;
            m_dNegativeLimitX = _dNegativeLimitX;
            m_dPositiveLimitY = _dPositiveLimitY;
            m_dNegativeLimitY = _dNegativeLimitY;
        }
    };
    extern DEVICE_LIBRARY_API std::map<int, MS_StationInformation> g_mpWorkStationInformation;


    //光源品牌
    enum ME_LightModel
    {
        LIGHTMODEL_MS,                      //铭赛
        LIGHTMODEL_MAX
    };

    //光源通讯方式
    enum ME_LightCommunication
    {
        LIGHTCOMMUNICAYION_LAN,              //网口
        LIGHTCOMMUNICAYION_COM,              //串口
        LIGHTCOMMUNICAYION_MAX
    };

    //光源配置参数
    struct MS_LightConfigParam
    {
        MS_LightConfigParam()
            : m_lightModel(LIGHTMODEL_MS)
            , m_channels(1)
            , m_lightCommunication(LIGHTCOMMUNICAYION_LAN)
            , m_name("")
            , m_lightNo(LIGHT_NO_1)
            , m_mpChannelName({ {1,""} })
        {
        }

        ME_LightModel m_lightModel;                     //品牌
        int m_channels;                                 //通道数
        ME_LightCommunication m_lightCommunication;     //通讯方式
        ME_LightNo m_lightNo;          //光源编号
        QString m_name;                                 //备注
        std::map<int, QString> m_mpChannelName;             //通道名称
    };

    struct MS_LightConfigParamList
    {
        MS_LightConfigParamList()
        {

        }
        std::vector<MS_LightConfigParam> m_lightConfigList;
    };
}