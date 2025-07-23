
#pragma once
#include <QString>
#include <QPointF>
#include <QVector>
#include <QJsonObject>
#include <vector>
#include "MS_ImageParam.h"
#include "MS_DataDefine.h"

#ifndef BUILD_STATIC
# if defined(VISIONLIBRARY_LIB)
#  define VISIONLIBRARY_API Q_DECL_EXPORT
# else
#  define VISIONLIBRARY_API Q_DECL_IMPORT
# endif
#else
# define VISIONLIBRARY_API
#endif

using MN_VisionImage::MS_Image_Param;

namespace MN_VisionAlgorithm
{
#pragma region Common
	// 阵列方向类型
	enum class ME_DirectionType
	{
		DIRECTIONTYPE_HORIZONTAL = 0,               // 横向
		DIRECTIONTYPE_VERTICAL = 1					// 纵向
	};

	// 换行类型
	enum class ME_NewLineType
	{
		NEWLINETYPE_S = 0,						    // S类型
		NEWLINETYPE_Z = 1						    // Z类型
	};

	// 起始点位置类型
	enum class ME_StartPointType
	{
		STARTPOINTTYPE_LEFTUP = 0,					// 左上角
		STARTPOINTTYPE_LEFTDOWN = 1,                // 左下角
		STARTPOINTTYPE_RIGHTUP = 2,					// 右上角
		STARTPOINTTYPE_RIGHTDOWN = 3                // 右下角
	};

	//算法任务类型，根据此字段筛选算法任务，显示可供选择的任务
	enum ME_AlgorithmTaskType
	{
		ALGTASKTYPE_PREDISPENSINGDETECT,		//点胶前检测
		ALGTASKTYPE_DISPENSINGDETECT,			//点胶定位
		ALGTASKTYPE_POSTDISPENSINGDETECT,		//点胶后检测
		ALGTASKTYPE_PREBONDDETECT,				//贴装前检测
		ALGTASKTYPE_BONDDETECT,					//贴装定位
		ALGTASKTYPE_POSTBONDDETECT,				//贴装后检测,
		ALGTASKTYPE_WAFERDETECT,                //拾取
		ALGTASKTYPE_LOCATE,                     //防反
		ALGTASKTYPE_DIELOCATE,                  //晶片定位
		ALGTASKTYPE_UPLOOKDETECT,               //uplook检测流程
		ALGTASKTYPE_FLUXIMPRINTDETECT,          //焊锡压印检测
	};

	//算法是否执行功能开关
	enum class ME_AlgFunctionID
	{
		ALGFUNCTIONID_EXISTDETECT,                    //有无检测
		ALGFUNCTIONID_INKDOTDETECT                   //墨点检测开关
	};

	enum ME_CalibrateType
	{
		CALIBRATETYPE_HANDEYE,                      //手眼标定
		CALIBRATETYPE_CAMERASCENTER,                //相机位置关系标定,外部未使用
		CALIBRATETYPE_ROTATECENTER,                 //旋转中心标定
		CALIBRATETYPE_CAMERAANDTIPS,                //通过上视相机校正吸嘴中心和拾取相机位置关系,2024添加
		CALIBRATETYPE_CAMERAANDTIPSBYPRESS,         //通过压痕校正吸嘴中心和对应相机位置关系
		CALIBRATETYPE_CAMERAANDTIPSBYHOLE,          //通过中心孔校正吸嘴中心和对应相机位置关系
		CALIBRATETYPE_CAMERAANDAXISRELATION,        //相机与轴同步标定 
		CALIBRATETYPE_CAMERAANDDISPENSE,            //相机与点胶头校正(有机械坐标)
		CALIBRATETYPE_CAMERAANDTHIMBLE,              //校正顶针与相机位置(没有机械坐标)
		CALIBRATETYPE_ROTATECENTERMANUAL,            //旋转中心标定
		CALIBRATETYPE_FLYSNAPANDPOS,				 //飞拍位置偏移标定
		CALIBRATETYPE_COLLETALIGNMENT,				 //夹持头校准(使用规则图形圆或矩形)
		CALIBRATETYPE_POSSHIFT,				         //位置偏移标定
	};

	//视觉模块执行结果类型
	enum ME_ExcuteState
	{
		EXECUTESTATE_OK,
		EXECUTESTATE_NOPRODUCT,                     //无产品	
		EXECUTESTATE_EXCEPTION,                     //异常
		EXECUTESTATE_PRODUCTERROR                   //产品错误
	};

	//特定的一些功能
	enum class ME_SpecificFunction
	{
		SPECIFICFUNCTION_MANUALLOCATE,              //手动定位功能
	};

	enum ME_GetImageState
	{
		GET_IMAGE_SUCCESS,
		GET_IMAGE_FALSE
	};

	//搜索的位置，上下左右
	enum class ME_SerachDirection
	{
		SEARCHDIRECTION_CENTER = 0,                 //中心位置
		SEARCHDIRECTION_UP = 1,					    // 上
		SEARCHDIRECTION_DOWN = 2,                   // 下
		SEARCHDIRECTION_LEFT = 3,				    // 左
		SEARCHDIRECTION_RIGHT = 4,                  // 右
		SEARCHDIRECTION_LEFTUP,					    // 左上角
		SEARCHDIRECTION_RIGHTUP,                    // 右上角
		SEARCHDIRECTION_LEFTDOWN,				    // 左下角
		SEARCHDIRECTION_RIGHTDOWN,                  // 右下角
	};

	//拍照执行的速度
	enum class ME_SnapSpeed
	{
		SNAPSPEED_SPEED0 = 0,               //速度0
		SNAPSPEED_SPEED1 = 1,				//速度1
		SNAPSPEED_SPEED2 = 2,               //速度2
		SNAPSPEED_SPEED3 = 3,				//速度3
		SNAPSPEED_SPEED4 = 4,               //速度4
		SNAPSPEED_SPEED5,					//速度5
		SNAPSPEED_SPEED6,                   //速度6
		SNAPSPEED_SPEED7,				    //速度7
		SNAPSPEED_SPEED8,                   //速度8
	};

	struct MS_VisionAxisParam
	{
		MS_VisionAxisParam(double _x = 0, double _y = 0, double _z = 0, double _u = 0, double _t = 0)
		{
			m_X = _x;
			m_Y = _y;
			m_Z = _z;
			m_U = _u;
			m_T = _t;
		}

		QJsonObject toJson()
		{
			QJsonObject jsonObj;
			jsonObj.insert("m_X", m_X);
			jsonObj.insert("m_Y", m_Y);
			jsonObj.insert("m_Z", m_Z);
			jsonObj.insert("m_U", m_U);
			jsonObj.insert("m_T", m_T);

			return jsonObj;
		}

		void fromJson(const QJsonObject& _jsonObj)
		{
			if (_jsonObj.isEmpty())
			{
				return;
			}

			m_X = _jsonObj.value("m_X").toDouble();
			m_Y = _jsonObj.value("m_Y").toDouble();
			m_Z = _jsonObj.value("m_Z").toDouble();
			m_U = _jsonObj.value("m_U").toDouble();
			m_T = _jsonObj.value("m_T").toDouble();

		}

		double m_X;                                 //X轴
		double m_Y;                                 //y轴
		double m_Z;                                 //Z轴
		double m_U;                                 //u轴
		double m_T;                                 //倾斜轴
	};

	enum ME_CameraAcquisitionType
	{
		ACQUSITIONTYPE_STATIC,
		ACQUSITIONTYPE_ONTHEFLY,//飞拍
	};

	struct MS_VisionCameraInfo
	{
		MS_VisionCameraInfo() : m_cameraNum(MN_VisionDevice::CAMERA_NO_NULL), m_workStation(-1), m_eCameraAcquisitionType(ACQUSITIONTYPE_STATIC)
		{
		}
		MN_VisionDevice::ME_CameraNo m_cameraNum;    //相机编号
		int m_workStation;                              //工位号
		ME_CameraAcquisitionType m_eCameraAcquisitionType;
	};

	struct MR_Result : public MS_VisionCameraInfo
	{
		MR_Result() : m_stateType(ME_ExcuteState::EXECUTESTATE_OK)
		{
		}
		virtual ~MR_Result() = default;

		ME_ExcuteState m_stateType;                             //执行状态
	};

	struct MS_DieSize
	{
		MS_DieSize()
		{
		}

		double m_dieSizeX = 0;                      //单位mm
		double m_dieSizeY = 0;                      //单位mm
		double m_dieThickness = 0;                  //单位mm
		double m_diePitchX = 0;                     //单位：mm
		double m_diePitchY = 0;                     //单位：mm
	};

	struct MS_VisionParamGeneral : public MS_VisionCameraInfo
	{
		MS_VisionParamGeneral() : m_taskName("Default"), m_subTaskName(""), m_algTaskType(ME_AlgorithmTaskType::ALGTASKTYPE_LOCATE)
		{
		}
		QString m_taskName;                         //任务名称，带|
		QString m_subTaskName;                      //副任务名称，带|
		ME_AlgorithmTaskType m_algTaskType;         //算法任务类型

		MS_DieSize m_dieSize;
	};

	struct MS_CalibrateModuleParam : public MS_VisionParamGeneral
	{
		MS_CalibrateModuleParam() : m_calibrateType(CALIBRATETYPE_HANDEYE), m_calibrateProp(CALIBRATETYPE_CAMERAANDTIPSBYHOLE, true)
		{
		}
		ME_CalibrateType m_calibrateType;           //标定类型
		std::pair<ME_CalibrateType, bool>  m_calibrateProp;   //对应标定的某些特殊属性
															  //CALIBRATETYPE_CAMERAANDTIPSBYHOLE 上视相机标定吸嘴中心时参数
															 //false：快捷校正时（关闭部分功能）； true:通用标定流程；
	};

	struct MS_ObjectInfo
	{
		MS_ObjectInfo() : m_flag(true), m_row(0), m_col(0)
		{
		}
		bool m_flag;                                        //是否定位或检测该工件
		int m_row;                                          //工件在大阵列中的行号
		int m_col;                                          //工件在大阵列中的列号
	};

	struct MS_ImageInfo : public MS_VisionParamGeneral
	{
		MS_ImageInfo() : m_getImageState(ME_GetImageState::GET_IMAGE_FALSE)
		{
		}
		MS_ObjectInfo m_objectInfo;                         //工件信息
		ME_GetImageState m_getImageState;                   //获取图像的状态
		MS_Image_Param m_image;                             //图像
	};

	//设置飞拍参数 
	struct MS_FlySnapExecuteParam
	{
		std::vector<MS_ObjectInfo> m_vecObjectInfo;             //待执行飞拍的工件信息，向量长度表示工件个数
		std::vector<MS_VisionAxisParam> m_vecSnapAixsP;         //对应的图像拍照机械坐标
	};

	//一个基岛位置检测多个目标,相对与基岛偏差
	struct MS_ObjectsParam
	{
		MS_ObjectsParam() : m_shiftXY(0, 0), m_angel(0)
		{
		}
		QPointF m_shiftXY;    //相对于基准偏移
		double m_angel;       //相对于基准角度
	};

	//一个基岛位置检测多个目标
	struct MS_MultiObjectsParam
	{
		MS_MultiObjectsParam() : m_multiNum(1, 1)
		{
		}
		std::pair<int, int> m_multiNum;                      //执行时输入多个工件阵列信息行列数
		std::vector<MS_ObjectsParam> m_objectsParam;         //执行贴装后检测时输入的参数: 两个参数值，序号0为示教模板时参数，序号1为当前执行颗的参数;
															 //执行贴装匹配时若有叠芯片检测时输入的参数:对应多个位置的参数值(默认序号0对应为示教模板时参数)
															 //执行多工件参数：对应多个位置的参数值(默认序号0对应为示教模板时参数)
	};

	struct MS_ExcuteParam
	{
		MS_ExcuteParam() : m_isNeedGetImage(true), m_serDir(ME_SerachDirection::SEARCHDIRECTION_CENTER), m_modelOffsetAngle(false, 0)
		{
		}

		std::vector<MS_ObjectInfo> m_vecObjectInfo;             //工件信息，向量长度表示工件个数
																//向量中的顺序，和图像中工件的执行顺序相同
		ME_SerachDirection m_serDir;                           //模板搜索方向
		bool m_isNeedGetImage;                                  //是否视觉取图
		std::vector<MS_Image_Param> m_vecImage;                 //输入图像数组
		std::vector<MS_VisionAxisParam> m_vecSnapAixsP;         //对应的图像拍照机械坐标
		std::pair<bool, double> m_modelOffsetAngle;             //模板偏移角度

		MS_MultiObjectsParam m_multiObjectsParam;				//一个基岛位置检测多个目标
	};

	struct MS_SetImagesParameter : public MS_VisionParamGeneral
	{
		MS_SetImagesParameter() : m_snapSpeed(ME_SnapSpeed::SNAPSPEED_SPEED0)
		{
		}
		ME_SnapSpeed m_snapSpeed;
		std::vector<MS_Image_Param> m_inImages;
		std::vector<MS_VisionAxisParam> m_snapAxisPfs;
		std::vector<MS_VisionAxisParam> m_cameraAxisPfs;
	};

	struct MS_SetCalibParameter
	{
		MS_SetCalibParameter()
		{
		}
		MS_VisionAxisParam m_startAxisPfs;       //飞拍标定时拾取轴位置
	};

	//模板阵列参数
	struct MS_ModelMatrixParam
	{
		int m_rows;													//行数
		int m_colums;												//列数
		int m_modelRowNo;										    //模板所在行位置
		int m_modelColNo;										    //模板所在列位置
		ME_StartPointType m_startPointType;							//起始点类型
		ME_DirectionType m_directionType;							//执行方向类型
		ME_NewLineType m_newLineType;								//换行类型

		MS_ModelMatrixParam() :
			m_startPointType(ME_StartPointType::STARTPOINTTYPE_LEFTUP),
			m_directionType(ME_DirectionType::DIRECTIONTYPE_HORIZONTAL),
			m_newLineType(ME_NewLineType::NEWLINETYPE_Z),
			m_rows(1),
			m_colums(1),
			m_modelRowNo(0),
			m_modelColNo(0)
		{
		}
	};

	//创建模板返回的信息
	struct MS_ModelInfo
	{
		MS_ModelInfo() : m_modelCenterPoint(QPointF(0, 0))
		{
		}
		QPointF m_modelCenterPoint;                             //模板中心
		MS_ModelMatrixParam m_modelMatrixParam;                 //模板阵列参数
	};

	//手动强制定位参数
	struct MS_SpecificFunctionParam : public MS_VisionParamGeneral
	{
		MS_SpecificFunctionParam() : m_specificFunction(ME_SpecificFunction::SPECIFICFUNCTION_MANUALLOCATE), m_isFlySnap(false)
		{
		}
		ME_SpecificFunction m_specificFunction;
		bool m_isFlySnap;                            //之前该工位执行任务是否是飞拍,飞拍的话执行完恢复硬触发状态
		std::vector<MS_ObjectInfo> m_vecObjectInfo;  //按照顺序存放的需要强制定位的工件的序号
													 //如：工件中第0和第2匹配失败，第1成功，则传入false，true, false
													 //m_flag在false时执行手动匹配
		MS_MultiObjectsParam m_multiObjectsParam;	 //一个基岛位置贴多个目标
	};
#pragma endregion


#pragma region Calibrate
	struct MS_CheckCalibrateIsAvailabe
	{
		MS_CheckCalibrateIsAvailabe()
		{
		}
		MS_CheckCalibrateIsAvailabe(const std::vector<int> _nums, ME_CalibrateType _type) :m_cameraNums(_nums), m_checkType(_type)
		{
		}
		std::vector<int> m_cameraNums;
		ME_CalibrateType m_checkType;
	};

	//标定结果结构体
	struct MR_HandEyeCalibResult : public MR_Result
	{
		std::vector<double> m_handEyeMat;//相机到轴间移动间距转换矩阵
		QPointF m_scale;//像素当量
	};

	struct MR_RotateCenterCalibResult : public MR_Result
	{
		QPointF m_rotateCenter;//旋转中心图像坐标
		double m_radius;//旋转半径
		QPointF m_shiftRotate2ImageCenter;//旋转中心到图像中心的位移（轴坐标）。
	};

	struct MR_CameraAndAxisRelationCalibResult : public MR_Result
	{
		std::vector<QPointF> m_errorValue1;//相机和手臂1误差值,实际值-理论值
		std::vector<QPointF> m_errorValue2;//相机和手臂2误差值,实际值-理论值
		std::vector<QPointF> m_errorValue3;//相机和手臂3误差值,实际值-理论值
	};

	struct MR_CameraAndTipsAlignCalibResult : public MR_Result
	{
		QPointF m_axisTips;//拾取XY位置
		double m_axisTipsAngle;//拾取U位置
		QPointF m_shiftTips;//吸嘴中心相较于视野中心偏差
		QPointF m_axisHollow;             //中空孔对准中心坐标
	};

	struct MR_AlignCameraPositionCalibResult : public MR_Result
	{
		//默认排列顺序(1to2, 1to3, 2to3)
		std::vector<QPointF> m_shiftCamCenter;//Cam1到Cam2中心点位移。(1to2,1to3,2to3)
		std::vector<double> m_deltaCamAngle;//Cam1到Cam2安装角度（弧度）
	};

	struct MR_CameraAndDispenseCalibResult : public MR_Result
	{
		//std::vector<QPointF> m_axisPos; //标定轴基准位置
		//std::vector<QPointF> m_camPos; //相机轴基准位置
		QPointF m_axisPos; //标定轴基准位置
		QPointF m_camPos; //相机轴基准位置
	};

	struct MR_CameraAndThimbleCalibResult : public MR_Result
	{
		QPointF m_thimblePosPixel; //顶针像素坐标位置
		QPointF m_shift2ImgC;//顶针中心和视野中心偏移距离
		MS_VisionAxisParam m_thimblePosAxis; //顶针坐标位置
	};

	struct MR_FlysnapAndPosCalibResult : public MR_Result
	{
		MR_FlysnapAndPosCalibResult() :m_snapSpeed(ME_SnapSpeed::SNAPSPEED_SPEED0)
		{
		}
		ME_SnapSpeed m_snapSpeed;
		QPointF m_locatePosPixel;                 //基准点对应像素坐标
		QPointF m_locatePosMm;					  //基准点对应坐标(mm)
		double m_locatePosAngle;                  //角度（弧度）
	};

	struct MR_CalibratePosResult : public MR_Result
	{
		QPointF m_axisPos;				//标定轴基准位置
		QPointF m_camPos;				//相机轴基准位置
		QPointF m_axisShift;            //轴偏移的距离
	};

	enum class ME_CameraAndAxisRelationCalibAxis
	{
		CALIBAXIS_X = 0,
		CALIBAXIS_Y,

	};

	//相机轴同步标定数据结构
	struct MS_CameraAndAxisRelationCalibParam
	{
		MS_CameraAndAxisRelationCalibParam() :m_cameraNum(-1), m_workStation(-1), m_numberOfCycles(0), m_snapTimes(0), m_snapStep(1), m_snapDelayed(5000),
			m_camRangeMax(0), m_camRangeMin(0), m_axisRangeMax(0), m_axisRangeMin(0), m_speed(100), m_acceleration(1000),
			m_calibAxis(ME_CameraAndAxisRelationCalibAxis::CALIBAXIS_Y)
		{
			m_absPixPos.clear();
		}
		int m_cameraNum;
		int m_workStation;
		QString m_groupName;

		ME_CameraAndAxisRelationCalibAxis m_calibAxis; //执行标定轴标记位
		std::pair<double, double> m_camStartPos;//相机起始位置坐标,mm
		std::pair<double, double> m_axisStartPos;//轴起始位置坐标,mm
		int m_numberOfCycles;//循环次数

		int m_snapTimes;//采样次数
		double m_snapStep;//采样步长,mm
		double m_snapDelayed;//采样延时,ms

		double m_speed;//运动速度
		double m_acceleration;//加速度

		double m_camRangeMax;
		double m_camRangeMin;
		double m_axisRangeMax;
		double m_axisRangeMin;
		std::vector<std::pair<double, double>> m_absPixPos;//同步标定获取的结果 每张图片的匹配数据 first：x second：y

		std::pair<double, double> m_axisXLineBegin; //以camera的y作为坐标系x轴,轴的x偏差为y轴拟合直线
		std::pair<double, double> m_axisXLineEnd;
		std::pair<double, double> m_axisYLineBegin;//以camera的y作为坐标系x轴,轴的y偏差为y轴拟合直线
		std::pair<double, double> m_axisYLineEnd;

		std::pair<double, double> m_axisLineBegin; //以camera的y作为坐标系x轴,轴的x偏差为y轴拟合直线
		std::pair<double, double> m_axisLineEnd;
		std::pair<double, double> m_axisRefPos; //bond的参考位置坐标
		std::pair<double, double> m_axisRefCurrentTipPos; //bond的参考位置坐标记录位置时，吸嘴在顶针中心的位置
		std::pair<double, double> m_cameraRefPos; //bond的参考位置坐标时相机的坐标
		std::map<int, std::pair<double, double>> m_axisCalibData; //相机y和轴位置

	};

#pragma endregion

#pragma region transform

	struct MS_GetPixelEquivalent_Inparm
	{
		MS_VisionCameraInfo m_cameraInfo;//相机信息
	};

	struct MS_GetPixelEquivalent_Outparm
	{
		QPointF m_pixelScale;//X，Y方向的像素尺度值
	};

	struct MS_GlueSprayTaskPoint//示教点结构体，示教完成后不会变化（修正轨迹除外）
	{
		MS_GlueSprayTaskPoint(const QPointF& _trajectoryP, const QPointF& _cameraP) :m_trajectoryPoint(_trajectoryP), m_cameraPoint(_cameraP)
		{
		}
		QPointF m_trajectoryPoint;//轨迹点图像坐标（左上角原点）
		QPointF m_cameraPoint;//轨迹点示教相机拍照位置（绝对相机轴机械坐标）
	};


	struct MS_GenerateTrajectoryModel_Outparm
	{
		std::vector<QPointF> m_trajectoryModel;//输出轨迹点的产品模型做坐标（相对模板中心的机械坐标）
	};


	enum ME_HandEyeStructureType
	{
		HANDEYESTRUCTURETYPE_HANDEYE_INONE,//点胶头和相机一体
		HANDEYESTRUCTURETYPE_HANDEYE_SEPARATE,//点胶头和相机分离
	};

	struct  MS_CalculateTrajectory_handeyeInone_Inpram//计算点胶作业的轴偏移输入参数
	{
		MS_CalculateTrajectory_handeyeInone_Inpram()
		{
		}
		MS_CalculateTrajectory_handeyeInone_Inpram(MS_VisionCameraInfo _modelCam, MS_VisionCameraInfo _curCam, double _matchAngle, QPointF _matchPoint, std::vector<QPointF> _tra)
			:m_modelCameraInfo(_modelCam), m_currentCameraInfo(_curCam), m_matchingAngle(_matchAngle), m_matchingPoint(_matchPoint), m_trajectoryPoints(_tra)
		{
		}
		MS_VisionCameraInfo m_modelCameraInfo;//模板相机信息
		MS_VisionCameraInfo m_currentCameraInfo;//当前相机信息
		double m_matchingAngle;//匹配到的模板旋转角度,单位弧度，逆时针正
		QPointF m_matchingPoint;//匹配到的模板中心点坐标（机械坐标）
		std::vector<QPointF> m_trajectoryPoints;//点胶任务轨迹点（相对模板的机械坐标）：传绝对机械坐标？传相对及机械坐标？（双模板情况下）
	};

	enum ME_CalculateTrajectoryModel
	{
		CALCULATETARJECTORYMODEL_CAMERA,//相机模式
		CALCULATETARJECTORYMODEL_HAND,//针头模式
	};

	struct  MS_CalculateTrajectory_handeyeSeparate_Inpram//计算点胶作业的轴偏移输入参数
	{
		MS_CalculateTrajectory_handeyeSeparate_Inpram()
		{
		}
		MS_CalculateTrajectory_handeyeSeparate_Inpram(MS_VisionCameraInfo _modelCamInfo, MS_VisionCameraInfo _currentCamInfo, double _matchingAngle, QPointF _matchingPos, QPointF _curCameraPos, std::vector<QPointF> _trajectoryPoints, QString _syringeNeedlePositionCalibrateName = "")
			: m_modelCameraInfo(_modelCamInfo), m_currentCameraInfo(_currentCamInfo), m_matchingAngle(_matchingAngle), m_matchingPoint(_matchingPos), m_currentCameraPosition(_curCameraPos), m_trajectoryPoints(_trajectoryPoints), m_syringeNeedlePositionCalibrateName(_syringeNeedlePositionCalibrateName)
		{
		}
		ME_CalculateTrajectoryModel m_calculateModel;//计算模式（相机模式/针头模式）
		MS_VisionCameraInfo m_modelCameraInfo;//模板相机信息
		MS_VisionCameraInfo m_currentCameraInfo;//当前相机信息
		double m_matchingAngle;//匹配角度，单位弧度，逆时针正
		QPointF m_matchingPoint;//匹配中心坐标（相机轴机械坐标）
		QPointF m_currentCameraPosition;//实时相机拍照位置（绝对相机轴机械坐标）
		std::vector<QPointF> m_trajectoryPoints;//点胶任务轨迹点
		QString m_syringeNeedlePositionCalibrateName;//针头位置标定参数名
	};

	struct MS_CalculateTrajectory_Inparm
	{
		ME_HandEyeStructureType m_calculateType;//计算轨迹的类型（点胶头和相机是一体的还是分离的）
		MS_CalculateTrajectory_handeyeInone_Inpram m_parm_handeyeInone;//点胶头和相机一体情况下的输入参数
		MS_CalculateTrajectory_handeyeSeparate_Inpram m_parm_handeyeSeparate;//点胶头和相机分离情况下的输入参数
	};

	struct  MS_CalculateTrajectory_Outpram
	{
		std::vector<QPointF> m_resPoints;
	};

	struct MS_MatchingResData
	{
		MS_MatchingResData() : m_matchingAngle(0), m_matchingPoint(0, 0), m_snapAxisPf(0, 0)
		{
		}
		double m_matchingAngle;             //匹配到的角度
		QPointF m_matchingPoint;            //匹配的mark点像素坐标
		QPointF m_snapAxisPf;               //相机对应机械坐标
		MS_VisionCameraInfo m_cameraInfo;   //相机号及对应的工位号
	};

	//贴装引导参数
	// 1. wafer->bond  (没有使用uplook定位,bond不启用旋转)
	//参数：   m_isUsingUpLook(false), m_isUsingBondRotate(false)
	//         m_isUsingThimblePos //是否使用顶针位置作为相机2输入参数,true表示使用顶针位置作为相机2输入参数,false表示使用相机2输入参数
	//         std::vector <MS_MatchingResData> matchingResData1st;     //相机1(贴装相机）匹配到的结果
	//         std::vector <MS_MatchingResData> matchingResData2nd;     //相机2(拾取相机）匹配到的结果
	//         m_tipInBondLookCalibName;                   //吸嘴中心标定任务名(bondLook)
	// 2. wafer->bond  (没有使用uplook定位,bond不启用旋转)
	//参数：   m_isUsingUpLook(false), m_isUsingBondRotate(true)
	//         m_isUsingThimblePos //是否使用顶针位置作为相机2输入参数,true表示使用顶针位置作为相机2输入参数,false表示使用相机2输入参数
	//         std::vector <MS_MatchingResData> matchingResData1st;     //相机1(贴装相机）匹配到的结果
	//         std::vector <MS_MatchingResData> matchingResData2nd;     //相机2(拾取相机）匹配到的结果
	//         m_tipInBondLookCalibName;                   //吸嘴中心标定任务名(bondLook)
	//         m_tipInUpLookCalibName;                     //吸嘴中心标定任务名(uplook)
	//         m_tipInUpLookRotateCalibName;              //tip在uplook旋转中心标定任务名
	//         m_bondLookLocateName;                     //bondlook的定位任务名
	// 3. uplook->bond  (使用uplook定位,都会启用bond旋转)
	//参数：   m_isUsingUpLook(true)
	//         m_isUsingModelPosUpLook 是否使用Uplook做模板时的固定位置
	//         std::vector <MS_MatchingResData> matchingResData1st;     //相机1(贴装相机）匹配到的结果
	//         std::vector <MS_MatchingResData> matchingResData2nd;     //相机2(uplook相机）匹配到的结果 bond位置坐标
	//         m_tipInBondLookCalibName;                   //吸嘴中心标定任务名(bondLook)
	//         m_tipInUpLookCalibName;                     //吸嘴中心标定任务名(uplook)
	//         m_tipInUpLookRotateCalibName;              //tip在uplook旋转中心标定任务名
	//         m_upLookLocateName;                     //uplook的定位任务名
	//		   m_upLookSnapSpeed;					    //upLook拍照时运行速度
	struct MS_CalculateAxisPositionBy2Camera_InputParm
	{
		MS_CalculateAxisPositionBy2Camera_InputParm() :m_isUsingThimblePos(true), m_isUsingBondRotate(true), m_isUsingUpLook(false),
			m_offsetAngle(0), m_tipInBondLookCalibName(""), m_tipInUpLookCalibName(""), m_tipInUpLookRotateCalibName(""),
			m_upLookSnapSpeed(ME_SnapSpeed::SNAPSPEED_SPEED0)
		{
		}
		bool m_isUsingThimblePos;   //是否使用顶针位置作为相机2输入参数,true表示使用顶针位置作为相机2输入参数,false表示使用相机2输入参数
		bool m_isUsingBondRotate;   //是否启用bond的旋转
		bool m_isUsingUpLook;       //是否使用Uplook定位
		bool m_isUsingModelPosUpLook;    //是否使用Uplook做模板时的固定位置
		double m_offsetAngle;       //补偿角度，逆时针为正，顺时针为负，单位弧度。
		std::vector <MS_MatchingResData> matchingResData1st;     //相机1(主要相机如：贴装相机）匹配到的结果
		std::vector <MS_MatchingResData> matchingResData2nd;     //相机2(次要相机如：拾取相机,uplook相机）匹配到的结果
		QString m_tipInBondLookCalibName;                   //吸嘴中心标定任务名(bondLook)
		QString m_tipInUpLookCalibName;                     //吸嘴中心标定任务名(uplook)
		QString m_tipInUpLookRotateCalibName;              //tip在uplook旋转中心标定任务名
		QString m_upLookLocateName;                       //uplook的定位任务名
		QString m_bondLookLocateName;                     //bondlook的定位任务名
		ME_SnapSpeed m_upLookSnapSpeed;                   //upLook拍照时运行速度
		MS_VisionAxisParam m_pickPos;					 //拾取位置

	};

	//struct MS_CalculateAxisPositionBy2Camera_InputParm1
	//{
	//    MS_CalculateAxisPositionBy2Camera_InputParm1() :m_isUsingThimblePos(true), m_isUsingBondRotate(true), m_isUsingUpLook(false),
	//        m_alignAngle_1st(0), m_alignAngle_2nd(0), m_offsetAngle(0), m_alignPoint_1st(0, 0), m_snapAxisPf_1st(0, 0), m_alignPoint_2nd(0, 0), m_snapAxisPf_2nd(0, 0)
	//    {
	//    }
	//    bool m_isUsingThimblePos; //是否使用顶针位置作为相机2输入参数,true表示使用顶针位置作为相机2输入参数,false表示使用相机2输入参数
	//    bool m_isUsingBondRotate;  //是否启用bond的旋转
	//    bool m_isUsingUpLook;     //是否使用Uplook定位
	//    double m_alignAngle_1st;//相机1匹配到的角度,相对于图像X（_1st 主要相机例如：“贴装相机”）
	//    double m_alignAngle_2nd;//相机2匹配到的角度,相对于图像X（_2nd 次要相机例如：“拾取相机”）
	//    double m_offsetAngle;//补偿角度，顺时针为正，逆时针为负，单位弧度。
	//    QPointF m_alignPoint_1st;//相机1定位到的mark点像素坐标
	//    QPointF m_snapAxisPf_1st;//相机1对应机械坐标
	//    QPointF m_alignPoint_2nd;//相机2定位到的mark点像素坐标
	//    QPointF m_snapAxisPf_2nd;//相机2时bond对应机械坐标
	//    MS_VisionCameraInfo m_cameraInfo_1st;//相机1及对应的工位号
	//    MS_VisionCameraInfo m_cameraInfo_2nd;//相机2及对应的工位号
	//    QString m_tipInBondLookCalibName;   //吸嘴中心标定任务名(bondLook)
	//};

	struct MS_CalculateAxisPositionBy2Camera_OutputParm
	{
		double m_angle;//旋转角度，顺时针为正，逆时针为负，单位弧度。
		QPointF m_axisPosition;//输出机械坐标点
	};

	enum ME_TransformAxisType
	{
		TRANSFORMAXISTYPE_HAND,//转换到针头轴坐标系
		TRANSFORMAXISTYPE_CAMERA,//转换到相机轴坐标系
	};

	struct MS_TransformPixel2Axis_handeyeSeparate_InputParm
	{
		MS_TransformPixel2Axis_handeyeSeparate_InputParm()
		{
		}
		MS_TransformPixel2Axis_handeyeSeparate_InputParm(ME_TransformAxisType _type, QPointF _inPixelP, MS_VisionCameraInfo _camInfo, QPointF _curCameraAxisP, QString _syringeNeedlePositionCalibrateName = "")
			:m_transformAxisType(_type), m_inPixelPf(_inPixelP), m_cameraInfo(_camInfo), m_curCameraAxisPf(_curCameraAxisP), m_syringeNeedlePositionCalibrateName(_syringeNeedlePositionCalibrateName)
		{
		}
		ME_TransformAxisType m_transformAxisType;//转换到那个轴坐标系下（针头轴\相机轴）
		QPointF m_inPixelPf;//当前需要转换的像素点坐标
		MS_VisionCameraInfo m_cameraInfo;//对应的工位信息
		QPointF m_curCameraAxisPf;//当前相机轴机械坐标(绝对的相机轴位置)
		QString m_syringeNeedlePositionCalibrateName;//当前工位针头位置标定参数名(转到针头轴必须输入此参数)
	};

	struct MS_TransformPixel2Axis_handeyeInone_InputParm
	{
		QPointF m_inPixelPf;//当前需要转换的像素点坐标
		MS_VisionCameraInfo m_cameraInfo;//对应的工位信息
		QPointF m_curCameraAxisPf;//当前相机轴机械坐标
	};

	struct MS_TransformPixel2Axis_InputParm
	{
		ME_HandEyeStructureType m_handeyeStructureType;//相机和轴结构类型参数
		MS_TransformPixel2Axis_handeyeSeparate_InputParm m_handeyeSeparateParm;//相机和轴分离结构下的参数
		MS_TransformPixel2Axis_handeyeInone_InputParm m_handeyeInoneParm;//相机和轴一体结构下的参数
	};

	struct MS_TransformPixel2Axis_OutputParm
	{
		QPointF m_position;//输出位置坐标
	};

	struct MS_TransformAxis2Pixel_handeyeSeparate_InputParm
	{
		MS_TransformAxis2Pixel_handeyeSeparate_InputParm()
		{
		}
		MS_TransformAxis2Pixel_handeyeSeparate_InputParm(ME_TransformAxisType _type, QPointF _inAxisP, MS_VisionCameraInfo _camInfo, QPointF _curSnapAxisP, QString _syringeNeedlePositionCalibrateName = "")
			:m_transformAxisType(_type), m_inAxisPf(_inAxisP), m_cameraInfo(_camInfo), m_curSnapAxisPf(_curSnapAxisP), m_syringeNeedlePositionCalibrateName(_syringeNeedlePositionCalibrateName)
		{
		}
		ME_TransformAxisType m_transformAxisType;//使用那个轴坐标系下（针头轴\相机轴）
		QPointF m_inAxisPf;//当前需要转换的机械点坐标
		MS_VisionCameraInfo m_cameraInfo;//对应的工位信息
		QPointF m_curSnapAxisPf;//当前相机轴机械坐标
		QString m_syringeNeedlePositionCalibrateName;//当前工位针头位置标定参数名(使用针头轴必须输入此参数)
	};

	struct MS_TransformAxis2Pixel_handeyeInone_InputParm
	{
		QPointF m_inAxisPf;//当前需要转换的机械点坐标
		MS_VisionCameraInfo m_cameraInfo;//对应的工位信息
		QPointF m_curSnapAxisPf;//当前相机轴机械坐标
	};

	struct MS_CalcAxis2PixelCoordInputParm
	{
		MS_CalcAxis2PixelCoordInputParm()
		{
		}
		MS_VisionCameraInfo m_cameraInfo;	//对应的工位信息
		QPointF m_curCameraAxisPf;			//当前相机轴机械坐标
		QPointF m_curWorkingAxisPf;			//当前作业轴机械坐标
		QPointF m_targetCameraAxisPf;		//待计算的相机轴机械坐标
		QPointF m_targetWorkingAxisPf;		//待计算的作业轴机械坐标
	};

	struct MS_CalcAxis2PixelCoordOutputParm
	{
		QPointF m_position;  //输出位置图像坐标
	};

	struct MS_TransformAxis2Pixel_InputParm
	{
		ME_HandEyeStructureType m_handeyeStructureType;//相机和轴结构类型参数
		MS_TransformAxis2Pixel_handeyeSeparate_InputParm m_handeyeSeparateParm;//相机和轴分离结构下的参数
		MS_TransformAxis2Pixel_handeyeInone_InputParm m_handeyeInoneParm;//相机和轴一体结构下的参数
	};

	struct MS_TransformAxis2Pixel_OutputParm
	{
		QPointF m_position;//输出位置坐标
	};

	struct MS_TransformPixel2TrajectoryModel_Inparm
	{
		QPointF m_curTrajectoryPosition;//当前轨迹点位置坐标（绝对机械坐标）
		QPointF m_matchingPosition;//匹配坐标（机械）
		double m_matchingAngle;//匹配角度
		//ME_HandEyeStructureType m_handeyeStructureType;//相机和轴结构类型参数
		//MS_TransformPixel2TrajectoryModel_handeyeSeparate_Inparm m_handeyeSeparateParm;//相机和轴分离结构下的参数
		//MS_TransformPixel2TrajectoryModel_handeyeInone_Inparm m_handeyeInoneParm;//相机和轴一体结构下的参数
	};

	struct MS_TransformPixel2TrajectoryModel_Outparm
	{
		QPointF m_trajectoryPosition;//转换后的轨迹点
	};

	struct MS_CalculateAxisPositionByCamera_Inparm
	{
		QString m_calibrateTaskName;//作业机械头和相机间的位置关系标定任务名
		QPointF m_alignP;//对准像素点坐标
		double m_alignAngle;//对准角度
		QPointF m_curLookPosition;//当前相机轴机械坐标
	};

	struct MS_CalculateAxisPositionByCamera_Outparm
	{
		QPointF m_alignP;//对准机械点坐标
		double m_alignAngle;//对准角度
	};

	struct MS_TransfromBondlook2HeadInputParam
	{
		MS_VisionCameraInfo m_cameraInfo;//Bond相机及对应的工位号
		QString m_bondlookLocateName;   //当前贴装定位任务名
		QString m_upLookNozzleCalibName;//吸嘴中心标定任务名(upLook)
		QString m_tipsInBondLookCalibName;//吸嘴中心在bondlook标定任务名
	};

	struct MS_CalculateAxisRotatePositionByCameraInputParm
	{
		MS_CalculateAxisRotatePositionByCameraInputParm() :m_isUsingThimblePos(false), m_offsetAngle(0), m_waferRotateCalibName("")
		{
		}
		bool m_isUsingThimblePos;
		double m_offsetAngle;//补偿角度，顺时针为负，逆时针为正，单位度。
		QString m_waferRotateCalibName;     //晶圆台旋转中心标定任务名
		MS_VisionAxisParam m_alignPos;  //相机定位到的mark点像素坐标(若有对齐则是对齐点像素坐标)
		MS_VisionAxisParam m_axis;  //轴对应机械坐标
		MS_VisionCameraInfo m_cameraInfo;//相机及对应的工位号
	};

	struct MS_CalculateAxisRotatePositionByCameraOutputParm
	{
		double m_angle;//旋转角度，顺时针为负，逆时针为正，单位弧度。
		MS_VisionAxisParam m_axis;      //输出机械坐标点
	};

	struct MS_CalculateAxisRotateBondPositionByCameraInputParm
	{
		MS_CalculateAxisRotateBondPositionByCameraInputParm() :m_offsetAngle(0), m_tipInUplookRotateCalibName("")
		{
		}
		double m_offsetAngle;                           //补偿角度，顺时针为负，逆时针为正，单位弧度。
		QString m_tipInUplookRotateCalibName;          //bond在uplook旋转中心标定任务名
		QString m_bondInUplookLocateName;               //bond在uplook定位任务名
		MS_VisionAxisParam  m_alignPos;                 //相机定位到的mark点像素坐标(若有对齐则是对齐点像素坐标)
		MS_VisionAxisParam  m_axis;                     //轴对应机械坐标
		MS_VisionCameraInfo m_cameraInfo;               //相机及对应的工位号
	};

	struct MS_CalculateAxisRotateBondPositionByCameraOutputParm
	{
		double m_angle;                 //旋转角度，顺时针为负，逆时针为正，单位弧度。
		MS_VisionAxisParam m_axis;      //输出机械坐标点
	};

	//获取拾取位置坐标
	struct MS_GetTipMove2PickPosInParam
	{
		MS_GetTipMove2PickPosInParam() : m_tipsInWaferCalibName("")
		{
		}

		QString m_tipsInWaferCalibName;     //晶圆吸嘴中心标定任务名
	};

	struct MS_GetTipMove2PickPosOutParam
	{
		MS_VisionAxisParam m_axis;              //输出机械坐标点
	};

#pragma endregion

#pragma region Wafer
	struct MS_WaferMapCoor
	{
		MS_WaferMapCoor() :m_row(0), m_col(0)
		{
		}
		MS_WaferMapCoor(int _row, int _col) :m_row(_row), m_col(_col)
		{
		}
		int m_row;                                  //map 行坐标
		int m_col;                                  //map 列坐标
	};

	struct MS_DiePosition
	{
		MS_DiePosition() :m_mappingCoor(), m_tabPos(0, 0)
		{
		}
		MS_WaferMapCoor m_mappingCoor;              //map坐标
		QPointF m_tabPos;                           //晶圆台机械坐标，单位mm
	};

	enum ME_ComfirmMappingCoordinateDirection
	{
		MAPPINGCOORDINATEDIRECTION_INCREMENT,       //map坐标系（X方向向右，Y方向下）方向递增
		MAPPINGCOORDINATEDIRECTION_DECREASING       //map坐标系（X方向向右，Y方向下）方向递减
	};

	struct MS_GetWaferGuideParm
	{
		QString m_taskName;                         //任务名
	};

	struct MS_WaferInputParameter
	{
		ME_ComfirmMappingCoordinateDirection m_mappingCoordinateDirectionX;     //map坐标系X方向递进状态
		ME_ComfirmMappingCoordinateDirection m_mappingCoordinateDirectionY;     //map坐标系Y方向递进状态
		int m_refDieCount;                          //参考die数量
	};

	struct MS_ComfirmRefDieParm
	{
		int m_index;                                //参考die索引
		MS_DiePosition m_dieposition;               //参考die坐标
	};

	struct MS_ComfirmStartDieParm
	{
		MS_DiePosition m_dieposition;               //起始die坐标
	};

	struct MS_GetDiePositionParmByMap
	{
		bool m_isEnableSrcCoor;                     //是否启用起始Map坐标
		MS_WaferMapCoor m_srcCoor;                  //起始map坐标
		MS_WaferMapCoor m_desCoor;                  //目标map坐标
	};

	enum ME_WaferUiType
	{
		WAFERUITYPE_BASEINFO,                       //晶圆基础数据
		WAFERUITYPE_CONTOUR                         //晶圆轮廓
	};

	struct MS_WaferShowUiParm : public MS_VisionCameraInfo
	{
		QString m_name;                             //任务名
		ME_WaferUiType m_waferType;                 //WaferUi类型
	};

	struct MS_WaferContourResult
	{
		bool m_state;                               //计算状态，true：计算成功
		double m_radius;                            //晶圆半径
		QPointF m_center;                           //晶圆中心坐标(机械坐标)
	};

	enum ME_WaferDiePRResultState
	{
		WAFERDIEPRRESULTSTATE_OK,                   //成功
		WAFERDIEPRRESULTSTATE_NG,                   //芯片定位失败
		WAFERDIEPRRESULTSTATE_NOPRODUCT,            //缺少芯片导致的定位失败
		WAFERDIEPRRESULTSTATE_DETECTNG              //芯片缺陷检测失败
	};

	struct MS_WaferDiePRResult
	{
		MS_WaferDiePRResult() : m_diePixelPosition(0, 0), m_dieAxisPosition(0, 0), m_dieRotationRadian(0), m_dieContour()
		{
		}
		ME_WaferDiePRResultState m_state;           //芯片定位状态
		QPointF m_diePixelPosition;                 //芯片中心像素坐标
		QPointF m_dieAxisPosition;                  //芯片中心机械坐标（相对图像中心）
		double m_dieRotationRadian;                 //芯片旋转弧度
		QVector<QPointF> m_dieContour;              //芯片轮廓
	};

#pragma endregion

	enum ME_AutoFocusAxisName
	{
		AUTOFOCUSAXISNAME_CAMERA,                       //相方调焦轴(相机轴)
		AUTOFOCUSAXISNAME_OBJECT                        //物方调焦轴（平台轴）
	};

	struct MS_AutoFocusSingnalParam
	{
		MS_AutoFocusSingnalParam() :m_axisMoveRangeMin(-1), m_axisMoveRangeMax(1), m_axisMoveRangeStep(0.1), m_autoFocusAxisName(AUTOFOCUSAXISNAME_CAMERA)
		{
		}
		double m_axisMoveRangeMin;                      //移动范围下限
		double m_axisMoveRangeMax;                      //移动范围上限
		double m_axisMoveRangeStep;                     //移动步长
		ME_AutoFocusAxisName m_autoFocusAxisName;       //自动对焦当前对应轴
	};

	struct MS_AutoFocusData
	{
		MS_AutoFocusData()
		{
		}
		MS_Image_Param m_img;                           //图像
		double m_axisCoor;                              //对应的调焦轴绝对机械坐标
	};

	struct MS_AutoFocusResult
	{
		MS_AutoFocusResult() :m_state(false), m_axisCoor(0)
		{
		}
		bool m_state;                                   //自动聚焦状态，true：成功，false：失败
		double m_axisCoor;                              //最清晰位置绝对机械坐标
	};

	enum ME_ShowWidgetType
	{
		WIDGET_TYPE_LIGHT,
		WIDGET_TYPE_MOVE
	};

	struct MS_TaskOperationParam
	{
		MS_TaskOperationParam() : m_paramName(""), m_desParamName(""), m_filePath(""), m_isCompress(false)
		{
		}
		QString m_paramName;                            //任务名，带|
		QString m_desParamName;                         //目标任务名，带|
		QString m_filePath;
		bool m_isCompress;								//是否压缩数据
	};

	typedef std::vector<MS_ImageInfo> MS_ImageInfoVec;
	typedef std::vector<QJsonObject> QJsonObjectVec;

	struct MS_PointContourData
	{
		std::vector<QPointF> m_points; //单个轮廓的点集
		QString color; //当前轮廓颜色
	};

	struct MS_ImgContourInfo
	{
		MS_ImgContourInfo()
		{
		}
		std::vector<MS_PointContourData> m_contourPointData;//轮廓结果点 及 相应的绘制颜色
		std::vector<std::pair<QString, QString>> m_imgDispInfo; //图像显示结果信息
	};

	enum class  ME_OperationMode
	{
		PRODUCTION,//生成模式
		DEBUGING,//调试模式
	};

	struct MS_OperationMode
	{
		MS_OperationMode() : m_OperationMode(ME_OperationMode::PRODUCTION)
		{
		}
		ME_OperationMode m_OperationMode;
	};

	struct MS_VisionInitParam
	{
		std::map<int, MN_VisionDevice::MS_StationInformation> m_mpAllStstionInfo;//上位机配置的所有运动轴信息
	};
}
