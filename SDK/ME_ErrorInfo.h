#pragma once
#include <QMap>
#include <QObject>
#include "ML_Global.h"

namespace MN_VisionError
{
    //模块代码：3位
    enum ME_VisionModelCode
    {
        VISIONMODELCODE_DEVICE = 600,               //硬件模块
        VISIONMODELCODE_LOCATE,                     //定位模块
        VISIONMODELCODE_MEASURE,                    //测量模块
        VISIONMODELCODE_DETECT,                     //检测模块
        VISIONMODELCODE_CALIBRATE,                  //标定模块
        VISIONMODELCODE_3D,                         //3D模块
        VISIONMODELCODE_AI,                         //深度学习模块
        VISIONMODELCODE_TASK,                       //任务模块
        VISIONMODELCODE_Transformation,             //引导模块
        VISIONMODELCODE_WAFER,
        VISIONMODELCODE_NORMAL = 699                //其他模块
    };

    const QMap<ME_VisionModelCode, QString> g_VisionModelCode =
    {
        { VISIONMODELCODE_DEVICE, QObject::tr("视觉硬件模块") },
        { VISIONMODELCODE_LOCATE, QObject::tr("视觉定位模块") },
        { VISIONMODELCODE_MEASURE, QObject::tr("视觉测量模块") },
        { VISIONMODELCODE_DETECT, QObject::tr("视觉检测模块") },
        { VISIONMODELCODE_CALIBRATE, QObject::tr("视觉标定模块") },
        { VISIONMODELCODE_3D, QObject::tr("视觉3D模块") },
        { VISIONMODELCODE_AI, QObject::tr("视觉深度学习模块") },
        { VISIONMODELCODE_TASK, QObject::tr("视觉任务模块") },
        { VISIONMODELCODE_Transformation, QObject::tr("视觉引导模块") },
        { VISIONMODELCODE_WAFER, QObject::tr("视觉晶圆模块") },
        { VISIONMODELCODE_NORMAL, QObject::tr("视觉模块") }
    };


    //错误代码：6位 
    //编码范围 101000~102999软件分配给视觉使用
    //100000  OK
    //100001  系统错误
    //100002~100999  相机应用库
    //101000~102999  视觉库
    enum ME_VisionErrorCode
    {
        VISION_ERRORCODE_OK = 100000,
        VISION_ERRORCODE_DEFAULT = 100001,                          //系统错误
        VISION_ERRORCODE_CAMERA_GRABIMAGE_FAILED = 100012,
        VISION_ERRORCODE_CAMERA_SET_PARAM_FAILED,
        VISION_ERRORCODE_LIGHT_SET_PARAM_FAILED = 100022,			//设置光源参数失败
        //Common Error 101000-101199
        VISION_ERRORCODE_COMMON_IMAGE_NULL = 101000,
        VISION_ERRORCODE_NORMAL_NO_LICENSE = 101099,              //License Error
        VISION_ERRORCODE_COMMON_EXCEPTION,                        //程序异常或Bug
        //Calibrate Error 101200-101699
        VISION_ERRORCODE_FITCIRCLE_ERROR = 101200,                   //圆拟合失败
        VISION_ERRORCODE_FITRECT_ERROR,                              //矩形拟合失败
         //101200~101219         
		VISION_ERRORCODE_HANDEYECALIB_MODEL_UNAVALABLE = 101220,    //101220~101239
        VISION_ERRORCODE_HANDEYECALIB_PARMA_ERROR,                  //参数异常
		VISION_ERRORCODE_ROTATECALIB_MODEL_UNAVALABLE = 101240,     //101240~101259
        VISION_ERRORCODE_ROTATECALIB_FIT_FAILED,
        VISION_ERRORCODE_ROTATECALIB_FITNUM_ERROR,
        VISION_ERRORCODE_CAMERAANDAXISCALIB_UNAVALABLE = 101260,     //101280~101279
        //视觉检测 Error 101700-102999
        VISION_ERRORCODE_MATCHING_MODEL_UNAVAILABLE = 101700,       //Matching Error 101700 ~ 101719
        VISION_ERRORCODE_MATCHING_MULTIOBJ_SEARCH_REGION_NULL,
        VISION_ERRORCODE_MATCHING_FAILED,
        VISION_ERRORCODE_MATCHING_SHAPEMODEL_FEWPOINTS,
        VISION_ERRORCODE_MATCHING_TIMEOUT,
        VISION_ERRORCODE_ALIGN_MODEL_UNAVALABLE = 101720,           //Align Error 101720 ~ 101739
        VISION_ERRORCODE_METROLOGY_FEWFITPOINTS = 101800,           //Metrology Error 101800 ~ 101819
        VISION_ERRORCODE_METROLOGY_MODEL_UNAVALIBLE,
        VISION_ERRORCODE_GLUEDETECT_MODULE_NULL = 101820,               //Gluedetect Error  101820 
        VISION_ERRORCODE_GENERADEFECT_MODEL_UNAVALIBLE,
        VISION_ERRORCODE_INKDOT_MODEL_UNAVALIBLE,
        VISION_ERRORCODE_LOCATEDETECT_MODEL_UNAVALIBLE,
		VISION_ERRORCODE_CHIPGLUEDETECT_MODEL_UNAVALIBLE = 101840,//ChipSurroundingsGlueDetect Error  101840 ~ 101849
         //Wafer 101900-101999                 
        VISION_ERRORCODE_WAFER_GUIDE_ALIGNOTCOMPLETED = 101900,
        //Task 102000-102099
        VISION_ERRORCODE_TASK_ERROR = 102000,  
        //102899 -  
    };

	const QMap<ME_VisionErrorCode, QString> g_VisionErrorCode =
	{
		{ VISION_ERRORCODE_OK, QObject::tr("成功") },
		{ VISION_ERRORCODE_DEFAULT, QObject::tr("系统错误") },
		{ VISION_ERRORCODE_CAMERA_GRABIMAGE_FAILED, QObject::tr("相机采图失败!") },
		{ VISION_ERRORCODE_CAMERA_SET_PARAM_FAILED, QObject::tr("相机参数设置失败!") },
		{ VISION_ERRORCODE_LIGHT_SET_PARAM_FAILED, QObject::tr("光源参数设置失败!") },
		{ VISION_ERRORCODE_COMMON_IMAGE_NULL, QObject::tr("空图像!") },
		{ VISION_ERRORCODE_NORMAL_NO_LICENSE, QObject::tr("视觉库License不可用!") },
        { VISION_ERRORCODE_COMMON_EXCEPTION, QObject::tr("视觉库捕获异常!") },
		{ VISION_ERRORCODE_HANDEYECALIB_MODEL_UNAVALABLE, QObject::tr("手眼关系标定无数据!") },
		{ VISION_ERRORCODE_HANDEYECALIB_PARMA_ERROR, QObject::tr("手眼标定参数错误!") },
		{ VISION_ERRORCODE_ROTATECALIB_MODEL_UNAVALABLE, QObject::tr("旋转中心标定无数据!") },
        { VISION_ERRORCODE_ROTATECALIB_FIT_FAILED, QObject::tr("旋转中心标定拟合圆失败!") },
        { VISION_ERRORCODE_ROTATECALIB_FITNUM_ERROR, QObject::tr("旋转中心标定拟合点太少错误!") },
        { VISION_ERRORCODE_CAMERAANDAXISCALIB_UNAVALABLE, QObject::tr("相机和轴关系标定不可用!")},
		{ VISION_ERRORCODE_MATCHING_MODEL_UNAVAILABLE, QObject::tr("匹配模板不可用!") },
		{ VISION_ERRORCODE_MATCHING_MULTIOBJ_SEARCH_REGION_NULL, QObject::tr("搜索区域为空!") },
        { VISION_ERRORCODE_MATCHING_FAILED, QObject::tr("匹配寻找模板失败!") },
        { VISION_ERRORCODE_MATCHING_SHAPEMODEL_FEWPOINTS, QObject::tr("形状匹配模板特征点太少!") },
        { VISION_ERRORCODE_MATCHING_TIMEOUT, QObject::tr("匹配寻找模板超时!") },
		{ VISION_ERRORCODE_ALIGN_MODEL_UNAVALABLE, QObject::tr("对齐模板不可用!") },
		{ VISION_ERRORCODE_METROLOGY_FEWFITPOINTS, QObject::tr("测量拟合点太少!") },
		{ VISION_ERRORCODE_METROLOGY_MODEL_UNAVALIBLE, QObject::tr("测量模板不可用!") },
        { VISION_ERRORCODE_GLUEDETECT_MODULE_NULL, QObject::tr("参数异常，重新配置胶水检测参数！") },
		{ VISION_ERRORCODE_GENERADEFECT_MODEL_UNAVALIBLE, QObject::tr("通用检测模板不可用!") },
		{ VISION_ERRORCODE_INKDOT_MODEL_UNAVALIBLE, QObject::tr("墨点检测模板不可用!") },
		{ VISION_ERRORCODE_LOCATEDETECT_MODEL_UNAVALIBLE, QObject::tr("定位检测模板不可用!") },
        { VISION_ERRORCODE_CHIPGLUEDETECT_MODEL_UNAVALIBLE, QObject::tr("芯片四周胶水检测模板不可用!") },
		{ VISION_ERRORCODE_WAFER_GUIDE_ALIGNOTCOMPLETED, QObject::tr("未完成晶圆对准!") },
		{ VISION_ERRORCODE_TASK_ERROR, QObject::tr("任务错误!") },
        { VISION_ERRORCODE_FITCIRCLE_ERROR, QObject::tr("圆拟合失败!") },
        { VISION_ERRORCODE_FITRECT_ERROR, QObject::tr("矩形拟合失败!") },

	};

    const QMap<ME_VisionErrorCode, QString> g_errSolutionMap =
    {
        { VISION_ERRORCODE_OK, QObject::tr("成功") },
        { VISION_ERRORCODE_DEFAULT, QObject::tr("1.系统错误，联系供应商解决。") },
        { VISION_ERRORCODE_CAMERA_GRABIMAGE_FAILED, QObject::tr("1.配置错误,查看当前报错相机的编号是否正确配置;\n2.接口异常,检查相机接口连接情况;\n3.硬件损坏,请联系供应商。") },
        { VISION_ERRORCODE_CAMERA_SET_PARAM_FAILED, QObject::tr("1.参数错误，确认待设置的参数是否正确并调整参数重新设置;\n2.接口异常,检查相机接口连接情况;\n3.硬件损坏,请联系供应商。") },
        { VISION_ERRORCODE_LIGHT_SET_PARAM_FAILED, QObject::tr("1.参数错误，确认待设置的参数是否正确并调整参数重新设置;\n2.接口异常,检查光源控制器网口连接情况;\n3.硬件损坏,请联系供应商。") },
		{ VISION_ERRORCODE_COMMON_IMAGE_NULL, QObject::tr("1.相机丢帧,检查相机接口连接情况;\n2.相机接口异常,检查相机接口连接情况;\n3.程序异常,请联系供应商。") },
        { VISION_ERRORCODE_NORMAL_NO_LICENSE, QObject::tr("1.加密狗丢失,检查加密狗是否安装到位;\n2.加密狗序列号不对应,联系供应商更改。") },
        { VISION_ERRORCODE_COMMON_EXCEPTION, QObject::tr("1.程序异常，联系供应商解决。") },
        { VISION_ERRORCODE_HANDEYECALIB_MODEL_UNAVALABLE, QObject::tr("1.未进行相关标定，重新标定手眼关系;\n2.标定参数或操作错误，请调整正确参数和操作重新标定。") },
        { VISION_ERRORCODE_HANDEYECALIB_PARMA_ERROR, QObject::tr("1.相机配置参数错误，确认相机配置是否正确并调整;\n2.工位配置参数错误，确认工位配置是否正确并调整;\n3.镜头配置参数错误，确认镜头配置正确并调整。") },
        { VISION_ERRORCODE_ROTATECALIB_MODEL_UNAVALABLE, QObject::tr("1.未进行相关标定，重新标定旋转中心;\n2.标定参数或操作错误，请调整正确参数和操作重新标定。") },
        { VISION_ERRORCODE_ROTATECALIB_FIT_FAILED, QObject::tr("1.标定参数错误，检查旋转中心标定配置参数;\n2.标定操作错误，请参考手册操作。") },
        { VISION_ERRORCODE_ROTATECALIB_FITNUM_ERROR, QObject::tr("1.标定参数错误，请增加旋转中心标定点数目(标定点登记数目)。") },
		{ VISION_ERRORCODE_CAMERAANDAXISCALIB_UNAVALABLE, QObject::tr("1.未进行相关标定，先对相机和轴关系标定后在进行;\n2.标定参数或操作错误，请调整正确参数和操作重新标定。")},
        { VISION_ERRORCODE_MATCHING_MODEL_UNAVAILABLE, QObject::tr("1.匹配模板不可用，当前任务对应的匹配模板未创建，请重新创建。") },
        { VISION_ERRORCODE_MATCHING_MULTIOBJ_SEARCH_REGION_NULL, QObject::tr("1.多工件匹配模板未船创建，重新创建匹配模板；\n2.多工件匹配模板搜索区域设置错误或无效，请重新设置。") },
        { VISION_ERRORCODE_MATCHING_FAILED, QObject::tr("1.图像异常,检查输入的图像是否存在理想模板特征,检查图像的成像效果(包含亮度,对比度等)和模板是否一致;\n2.查找模板参数错误,根据图像再次确认模板参数(包含目标包含区域,目标搜索区域的设置)是否设置得当;\n3.正常的匹配失败,图像中的目标本身存在缺陷。") },
        { VISION_ERRORCODE_MATCHING_SHAPEMODEL_FEWPOINTS, QObject::tr("1.图像不佳,调整光源相机成像参数至黑白分明效果;\n2.对比度参数不合适,减小最小对比度参数;\n3.金字塔层数不合适,降低金字塔层数。") },
        { VISION_ERRORCODE_MATCHING_TIMEOUT, QObject::tr("1.图像异常,检查输入的图像是否存在理想模板特征,检查图像的成像效果(包含亮度,对比度等)和模板是否一致;\n2.模板参数不合适,调整合适的对比度参数(不应包含散乱的无效特征点),调整合适的模板区域(请使用去除区域过滤掉无效区域),金字塔层数不合适(较大的模板区域可以设置较高的层数);\n3.未启用搜索,可以根据情况启用搜索区域。") },
        { VISION_ERRORCODE_ALIGN_MODEL_UNAVALABLE, QObject::tr("1对齐检测模板不可用，当前任务对应的对齐模板未创建，请重新创建模板。") },
        { VISION_ERRORCODE_METROLOGY_FEWFITPOINTS, QObject::tr("1.图像异常,检查输入的图像是否存在待量测的目标特征;\n2.参数不合适,结合图像调整合适的拟合测量参数。") },
        { VISION_ERRORCODE_METROLOGY_MODEL_UNAVALIBLE, QObject::tr("1.量测模板不可用,当前任务对应的量测模板(包括直线,矩形,圆形的拟合测量)未创建，请重新创建模板。") },
        { VISION_ERRORCODE_GENERADEFECT_MODEL_UNAVALIBLE, QObject::tr("1.通用检测模板不可用，当前任务对应的通用检测模板创建不完整或未创建，请重新创建模板。") },
        { VISION_ERRORCODE_INKDOT_MODEL_UNAVALIBLE, QObject::tr("1.墨点检测模板不可用,当前任务对应的墨点检测模板创建不完整或未创建，请重新创建模板。") },
        { VISION_ERRORCODE_LOCATEDETECT_MODEL_UNAVALIBLE, QObject::tr("1.定位检测模板不可用，当前任务对应的定位检测模板创建未创建，请重新创建模板。") },
        { VISION_ERRORCODE_CHIPGLUEDETECT_MODEL_UNAVALIBLE, QObject::tr("1.芯片四周胶水检测模板不可用，请创建四周胶水检测模板后在进行;  \n2.参数异常，重新设置胶水参数和检测区域。") },
        { VISION_ERRORCODE_WAFER_GUIDE_ALIGNOTCOMPLETED, QObject::tr("1.未完成晶圆对齐，重新进行晶圆对齐。") },
        { VISION_ERRORCODE_TASK_ERROR, QObject::tr("1.视觉任务错误，请联系供应商解决。")},
        { VISION_ERRORCODE_GLUEDETECT_MODULE_NULL, QObject::tr("1.参数异常，未绘制胶水检测区域或者未选择胶水检测功能项。")},
        { VISION_ERRORCODE_FITCIRCLE_ERROR, QObject::tr("1.图像异常,检查输入的图像是否存在待拟合的圆特征;\n2.参数不合适,结合图像调整合适的拟合测量参数。")},
        { VISION_ERRORCODE_FITRECT_ERROR, QObject::tr("1.图像异常,检查输入的图像是否存在待拟合的矩形特征;\n2.参数不合适,结合图像调整合适的拟合测量参数。")},
    };

     struct MS_VisionErrorInfo
    {
        MS_VisionErrorInfo()
        {
        };
        MS_VisionErrorInfo(int _modelCode, int _errorcode, QString _additionDesc = ""): 
            m_modelCode(_modelCode), m_errorcode(_errorcode), m_additionDesc(_additionDesc)
        {
        }

        int m_modelCode = (int)ME_VisionModelCode::VISIONMODELCODE_NORMAL;
        int m_errorcode = (int)ME_VisionErrorCode::VISION_ERRORCODE_DEFAULT;
        QString m_additionDesc = "";							//额外信息
        bool operator ==(const MS_VisionErrorInfo& _o)
        {
            auto result{ false };
            result = (m_errorcode == _o.m_errorcode) && (m_modelCode == _o.m_modelCode);
            return result;
        }
    };

    class  MI_VisionError   
    {
    public:
        static QString getModelString(int _modelCode)                       //获取模块字符串
        {
            if (!g_VisionModelCode.contains(ME_VisionModelCode(_modelCode)))
            {
                return "";
            }
            return g_VisionModelCode[ME_VisionModelCode(_modelCode)];
        }

        static QString getErrorString(int _errorCode)                       //获取错误字符串
        {
            if (!g_VisionErrorCode.contains(ME_VisionErrorCode(_errorCode)))
            {
                return "";
            }
            return g_VisionErrorCode[ME_VisionErrorCode(_errorCode)];
        }

        static QString getVisionErrorString(const MS_VisionErrorInfo& _visionErrorInfo)           //获取完整的错误字符串
        {
            return QString("%1 : %2").arg(getModelString(_visionErrorInfo.m_modelCode)).arg(getErrorString(_visionErrorInfo.m_errorcode));
        }

        //获取错误码解决方案
        static QString getErrorCodeSolution(int _errorCode)
        {
            if (g_errSolutionMap.find(ME_VisionErrorCode(_errorCode)) != g_errSolutionMap.end())
            {
                return g_errSolutionMap.value(ME_VisionErrorCode(_errorCode));
            }
            else
            {
                return "";
            }
        }
    };

}

Q_DECLARE_METATYPE(MN_VisionError::MS_VisionErrorInfo)

