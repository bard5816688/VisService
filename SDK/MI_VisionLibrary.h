#pragma once
#include "MS_VisionLibrary.h"
#include "ME_ErrorInfo.h"
#include "ME_DeviceErrorInfo.h"

namespace MN_VisionAlgorithm
{
	struct MS_AuthorityInfo;

	class MI_VisionBase
	{
	public:
		virtual ~MI_VisionBase()
		{
		}

		/*******************************************************************/
		/* 功    能：获取当前对象执行的错误代码
		/* 输入参数：无
		/* 输出参数：无
		/* 返 回 值：错误代码
		/*******************************************************************/
		virtual MN_VisionError::MS_VisionErrorInfo getErrorInfo() = 0;

		/*******************************************************************/
		/* 功    能：判断当前对象是否可用
		/* 输入参数：无
		/* 输出参数：无
		/* 返 回 值：如果可用，返回true ,否则返回false；默认返回false
		/*******************************************************************/
		virtual bool isValid() = 0;

		/*******************************************************************/
		/* 功    能：获取当前对象执行后的结果图像
		/* 输入参数：无
		/* 输出参数：_images 获得的图像数据
		/* 返 回 值：如果执行成功，返回true ,否则返回false
		/*******************************************************************/
		virtual bool getImage(MS_ImageInfoVec& _images)
		{
			return false;
		}

		/*******************************************************************/
		/* 功    能：获取当前对象同步执行后的原始图像
		/* 输入参数：无
		/* 输出参数：_images 获得的图像数据
		/* 返 回 值：如果执行成功，返回true ,否则返回false
		/*******************************************************************/
		virtual bool getOriginalImage(MS_ImageInfoVec& _images)
		{
			return false;
		}

		 /*******************************************************************/
		/* 功    能：获取结果图像的轮廓点及图像显示信息
		/* 输入参数：无
		/* 输出参数：结果图像的轮廓点(包括显示颜色)、图像显示信息(包括显示颜色)
		/* 返 回 值：如果执行成功，返回true ,否则返回false
		/*******************************************************************/
		virtual bool getResImgContour(MS_ImgContourInfo& _resInfo)
		{
			return false;
		}

		/*******************************************************************/
		/* 功    能：使用原始图像和轮廓点，生成结果图像
		/* 输入参数：_inImg 输入图像， _inPoint 输入轮廓点
		/* 输出参数：_outImg 输出结果图像
		/* 返 回 值：如果执行成功，返回true ,否则返回false
		/*******************************************************************/
		virtual bool genResImage(MS_Image_Param& _outImg, const MS_Image_Param& _inImg, const MS_ImgContourInfo& _imgContourInfo)
		{
			return false;
		};
	};

	class VISIONLIBRARY_API MI_VisionGeneral : public QObject, public MI_VisionBase
	{
		Q_OBJECT

	public:
		MI_VisionGeneral()
		{
		};
		virtual ~MI_VisionGeneral()
		{
		}

		/*******************************************************************/
		/* 功    能：执行视觉任务（同步）
		/* 输入参数：_inParam 参数
		/* 输出参数：无
		/* 返 回 值：如果成功，返回true ,否则返回false
		/*******************************************************************/
		virtual bool execute(const MS_ExcuteParam& _inParam) = 0;

		/*******************************************************************/
		/* 功    能：执行视觉任务（异步）
		/* 输入参数：_inParam 参数
		/* 输出参数：无
		/* 返 回 值：如果执行成功，返回true ,否则返回false
		/*******************************************************************/
		virtual bool executeAsyn(const MS_ExcuteParam& _inParam) = 0;

		/*******************************************************************/
		/* 功    能：执行飞拍任务
		/* 输入参数：_inParam 任务参数
		/* 输出参数：无
		/* 返 回 值：如果成功，返回true ,否则返回false
		/*******************************************************************/
		virtual bool executeFlySnapFlow(const MS_ExcuteParam& _inParam) = 0;

		/*******************************************************************/
		/* 功    能：设置当前飞拍工件相关参数
		/* 输入参数：MS_FlySnapExecuteParam 待执行飞拍工件的信息
		/* 输出参数：无
		/* 返 回 值：如果成功，返回true ,否则返回false
		/* 返 回 值：false 代表飞拍任务还没准备好，当前不能执行
		/*******************************************************************/
		virtual bool setFlySnapExecuteParam(const MS_FlySnapExecuteParam& _flySnapExecuteParam) = 0;

		/*******************************************************************/
		/* 功    能：设置飞拍位置走完
		/* 输入参数：无
		/* 输出参数：无
		/* 返 回 值：如果成功，返回true ,否则返回false
		/*******************************************************************/
		virtual bool setFlySnapMoveFinishedFlag(bool _isMoveFinished) = 0;

		/*******************************************************************/
		/* 功    能：获取当前对象执行后的结果数据
		/* 输入参数：无
		/* 输出参数：获得的结果数据
		/* 返 回 值：成功 or 失败
		/*******************************************************************/
		virtual bool getResult(QJsonObjectVec& _resultVec)
		{
			return false;
		}

		/* 功    能：设置相机光源参数
		/* 输入参数：无
		/* 输出参数：获得的结果数据
		/* 返 回 值：成功 or 失败
		/*******************************************************************/
		virtual void setCameraLightParam() = 0;

	signals:
		//异步流程中，发送曝光完成信号，不发送原始图像
		void SIG_VisionGetOriginalImage(MS_ImageInfoVec _imageInfoVec);

		//异步流程中，发送计算结果，发送原始图像
		void SIG_VisionExecuteFinish(QJsonObjectVec _resultVec, MS_ImageInfoVec _imageInfoVec);

		//异步流程中，发送结果图像
		void SIG_VisionGetResultImage(MS_ImageInfoVec _imageInfoVec);

		//发送错误码
		void SIG_SendErrorInfo(MN_VisionError::MS_VisionErrorInfo);
	};

	class MI_Transformation : public MI_VisionBase
	{
	public:
		virtual ~MI_Transformation()
		{
		}

		/*******************************************************************/
		/* 功    能：获取相机的像素当量
		/* 输入参数：相机信息
		/* 输出参数：像素X,Y方向的尺度值
		/* 返 回   ：值标定完成返回true，否则返回false
		/*******************************************************************/
		virtual bool getPixelEquivalent(const MS_GetPixelEquivalent_Inparm& _in, MS_GetPixelEquivalent_Outparm& _out) = 0;

		/*******************************************************************/
		/* 功    能：执行点胶作业的计算
		/* 输入参数：MS_TransformTrajectoryParam _inParam  计算点胶作业的轴偏移输入参数
		/* 输出参数： vector<QPointF>& _resPoints  纠正偏移后的轴坐标点
		/* 返 回 值：当前对象可用，返回true，否则返回false
		/*******************************************************************/
		virtual bool calculateTrajectory(const MS_CalculateTrajectory_Inparm& _in, MS_CalculateTrajectory_Outpram& _out) = 0;

		/*******************************************************************/
		/* 功    能：通过相机获取图像中点对应的机械坐标
		/* 输入参数：MS_AlignPixel2Axis_Inparm
		/* 输出参数：MS_AlignPixel2Axis_Outparm
		/* 返 回 值：bool 程序是否执行成功
		/*******************************************************************/
		virtual bool calculateAxisPositionByCamera(const MS_CalculateAxisPositionByCamera_Inparm& _in, MS_CalculateAxisPositionByCamera_Outparm& _out) = 0;

		/*******************************************************************/
		/* 功    能：通过两个相机获取的图像点，计算两点间的机械移动间距计算轴移动
		/* 输入参数：MS_CalculateAxisPositionBy2Camera_InputParm
		/* 输出参数：MS_CalculateAxisPositionBy2Camera_OutputParm
		/* 返 回 值：计算成功，返回true，否则返回false
		/*******************************************************************/
		virtual bool calculateAxisPositionBy2Camera(const MS_CalculateAxisPositionBy2Camera_InputParm& _in, MS_CalculateAxisPositionBy2Camera_OutputParm& _out) = 0;

		/*******************************************************************/
		/* 功    能：将像素转换为轴坐标
		/* 输入参数：m_inPixelPf 当前需要转换的像素点坐标
		/*           m_camNum 当前相机编号
		/*           m_curSnapAxisPf  当前相机/相机相关轴机械坐标
		/* 输出参数：移动到图像中心的轴机械坐标
		/* 返 回 值：计算成功，返回true，否则返回false
		/*******************************************************************/
		virtual bool transformPixel2Axis(const MS_TransformPixel2Axis_InputParm& _in, MS_TransformPixel2Axis_OutputParm& _out) = 0;

		/*******************************************************************/
		/* 功    能：图像上显示当前图像的轨迹线时，将机械轨迹点坐标转成当前图像上坐标点
		/* 输入参数：QPointF _inAxisPf 当前需要转换的机械点坐标
		/*           QPointF _curSnapAxisPf 当前相机/相机相关轴机械坐标
		/*           int _camNum 当前相机编号
		/* 输出参数：转换后的图像绝对坐标
		/* 返 回 值：计算成功，返回true，否则返回false
		/*******************************************************************/
		virtual bool transformAxis2Pixel(const MS_TransformAxis2Pixel_InputParm& _in, MS_TransformAxis2Pixel_OutputParm& _out) = 0;

		/*******************************************************************/
		/* 功    能：以图像中心点为起点(此时相机轴和运动轴的位置为起点)，
		/*			 目标位置的相机轴和运动轴的位置为目标点，转换为图像上像素坐标
		/* 输入参数：当前位置相机和作业轴机械点坐标
		/*           目标位置相机和作业轴机械点坐标
		/*           工位信息
		/* 输出参数：转换后的图像坐标
		/* 返 回 值：计算成功，返回true，否则返回false
		/*******************************************************************/
		virtual bool calcAxis2PixelCoord(const MS_CalcAxis2PixelCoordInputParm& _in, MS_CalcAxis2PixelCoordOutputParm& _out) = 0;

		/*******************************************************************/
		/* 功    能：修正轨迹时，当前轨迹点反算到模板轨迹点
		/* 输入参数：当前轨迹点及相关参数
		/* 输出参数：模板轨迹点
		/* 返 回 值：计算成功，返回true，否则返回false
		/*******************************************************************/
		virtual bool transformPixel2TrajectoryModel(const MS_TransformPixel2TrajectoryModel_Inparm& _in, MS_TransformPixel2TrajectoryModel_Outparm& _out) = 0;

		/*******************************************************************/
		/* 功    能：贴装时贴装头预先跑到的位置
		/* 输入参数：QPointF _lookCoor 相机坐标（X:0,Y:实际值）
		/* 输出参数：QPointF _headCoor 贴装头坐标
		/* 返 回 值：bool 程序是否执行成功
		/*******************************************************************/
		virtual bool transfromBondlook2Head(const MS_TransfromBondlook2HeadInputParam& _in, QPointF& _headCoor) = 0;

		/*******************************************************************/
		/* 功    能：初始化晶圆台根据匹配坐标计算出移动坐标功能
		/* 输入参数：MS_CalculateAxisRotatePositionByCameraInputParm
		/* 输出参数：MS_CalculateAxisRotatePositionByCameraOutputParm
		/* 返 回 值：计算成功，返回true，否则返回false
		/*******************************************************************/
		virtual bool initCalculateAxisRotatePositionByCamera(const MS_CalculateAxisRotatePositionByCameraInputParm& _in) = 0;

		/*******************************************************************/
		/* 功    能：晶圆台根据匹配坐标计算出移动坐标
		/* 输入参数：MS_CalculateAxisRotatePositionByCameraInputParm
		/* 输出参数：MS_CalculateAxisRotatePositionByCameraOutputParm
		/* 返 回 值：计算成功，返回true，否则返回false
		/*******************************************************************/
		virtual bool calculateAxisRotatePositionByCamera(const MS_CalculateAxisRotatePositionByCameraInputParm& _in, MS_CalculateAxisRotatePositionByCameraOutputParm& _out) = 0;

		/*******************************************************************/
		/* 功    能：获取拾取位置坐标
		/* 输入参数：MS_GetTipMove2PickPosInParam
		/* 输出参数：MS_GetTipMove2PickPosOutParam
		/* 返 回 值：计算成功，返回true，否则返回false
		/*******************************************************************/
		virtual bool getTipMove2PickPos(const MS_GetTipMove2PickPosInParam& _in, MS_GetTipMove2PickPosOutParam& _out) = 0;

		//贴装位置计算  先初始化参数，再执行 
		/*******************************************************************/
		/* 功    能：先初始化参数 通过两个相机获取的图像点，计算两点间的机械移动间距计算轴移动
		/* 输入参数：MS_CalculateAxisPositionBy2Camera_InputParm
		/* 输出参数：MS_CalculateAxisPositionBy2Camera_OutputParm
		/* 返 回 值：计算成功，返回true，否则返回false
		/*******************************************************************/
		virtual bool initCalculateAxisPositionBy2Camera(const MS_CalculateAxisPositionBy2Camera_InputParm& _in) = 0;

		/*******************************************************************/
		/* 功    能：初始化功能bond根据匹配坐标计算出移动坐标(移动到模板位置)参数
		/* 输入参数：MS_CalculateAxisRotateBondPositionByCameraInputParm
		/* 输出参数：MS_CalculateAxisRotateBondPositionByCameraOutputParm
		/* 返 回 值：计算成功，返回true，否则返回false
		/*******************************************************************/
		virtual bool initCalculateAxisRotateBondPositionByCamera(const MS_CalculateAxisRotateBondPositionByCameraInputParm& _in) = 0;

		/*******************************************************************/
		/* 功    能：bond根据匹配坐标计算出移动坐标(移动到模板位置)
		/* 输入参数：MS_CalculateAxisRotateBondPositionByCameraInputParm
		/* 输出参数：MS_CalculateAxisRotateBondPositionByCameraOutputParm
		/* 返 回 值：计算成功，返回true，否则返回false
		/*******************************************************************/
		virtual bool calculateAxisRotateBondPositionByCamera(const MS_CalculateAxisRotateBondPositionByCameraInputParm& _in, MS_CalculateAxisRotateBondPositionByCameraOutputParm& _out) = 0;

	};

	class MI_TaskOperation
	{
	public:
		/*******************************************************************/
		/* 功    能：删除任务
		/* 输入参数：MS_TaskOperationParam _param 任务参数
		/* 输出参数：无
		/* 返 回 值：无
		/*******************************************************************/
		virtual bool deleteTask(const MS_TaskOperationParam& _param) = 0;

		/*******************************************************************/
		/* 功    能：复制任务
		/* 输入参数：MS_TaskOperationParam _param 任务参数
		/* 输出参数：无
		/* 返 回 值：无
		/*******************************************************************/
		virtual bool copyTask(const MS_TaskOperationParam& _param) = 0;

		/*******************************************************************/
		/* 功    能：导出任务
		/* 输入参数：MS_TaskOperationParam _param 任务参数
		/* 输出参数：QJsonObject _jsonData 导出的所有任务相关json数据
		/* 返 回 值：bool
		/*******************************************************************/
		virtual bool exportTask(QJsonObject& _jsonData, const MS_TaskOperationParam& _param) = 0;

		/*******************************************************************/
		/* 功    能：导入任务
		/* 输入参数：MS_TaskOperationParam _param 任务参数  QJsonObject _jsonData 导出的所有任务相关json数据
		/* 输出参数：无
		/* 返 回 值：bool
		/*******************************************************************/
		virtual bool importTask(const MS_TaskOperationParam& _param, const QJsonObject& _jsonData) = 0;

		/*******************************************************************/
		/* 功    能：获取当前对象执行的错误代码
		/* 输入参数：无
		/* 输出参数：无
		/* 返 回 值：错误代码
		/*******************************************************************/
		virtual MN_VisionError::MS_VisionErrorInfo getErrorInfo() = 0;

		/*******************************************************************/
		/* 功    能：复制吸嘴中心标定数据
		/* 输入参数：QString _originalTaskName  待复制任务名
		/*           QString _toCopyTaskName 目标任务名
		/* 返 回 值：bool 程序是否执行成功
		/*******************************************************************/
		virtual bool copyHeadAndLookPositionRelationData(const QString& _originalTaskName, const QString& _toCopyTaskName) = 0;

		/*******************************************************************/
		/* 功    能：删除吸嘴中心标定数据
		/* 输入参数：QString _originalTaskName  待删除任务名
		/* 返 回 值：bool 程序是否执行成功
		/*******************************************************************/
		virtual bool deleteHeadAndLookPositionRelationData(const QString& _originalTaskName) = 0;

		/*******************************************************************/
		/* 功    能：复制点胶头位置关系标定数据
		/* 输入参数：QString _originalTaskName  待复制任务名
		/*           QString _toCopyTaskName 目标任务名
		/* 返 回 值：bool 程序是否执行成功 T_CameraAndDispenseCalib
		/*******************************************************************/
		virtual bool copyCameraAndDispenseRelationData(const QString& _originalTaskName, const QString& _toCopyTaskName) = 0;

		/*******************************************************************/
		/* 功    能：删除点胶头位置关系标定数据
		/* 输入参数：QString _originalTaskName  待删除任务名
		/* 返 回 值：bool 程序是否执行成功
		/*******************************************************************/
		virtual bool deleteCameraAndDispenseRelationData(const QString& _originalTaskName) = 0;

		/*******************************************************************/
		/* 功    能：删除视觉库生成的较早数据(按时间遍历删除)
		/* 输入参数：
		/* 输出参数：无
		/* 返 回 值：bool 程序是否执行成功
		/*******************************************************************/
		virtual bool deleteOutDateData() = 0;

		/*******************************************************************/
		/* 功    能：删除视觉库内存里的数据，再根据当前任务名加载当前的任务所需的视觉任务数据
		/* 备	 注：根据任务名带|分，m_taskGroup和m_taskFile一起组合加载
		/* 输入参数：_param.m_paramName  根据任务名(带|)删除
		/* 输出参数：无
		/* 返 回 值：bool 程序是否执行成功
		/*******************************************************************/
		virtual bool deleteCacheData(const MS_TaskOperationParam& _param) = 0;
	};

	class VISIONLIBRARY_API MI_WaferLocate : public QObject, public MI_VisionBase
	{
		Q_OBJECT

	public:
		/*******************************************************************/
		/* 功    能：执行视觉任务（同步）
		/* 输入参数：_inParam 参数
		/* 输出参数：无
		/* 返 回 值：如果成功，返回true ,否则返回false
		/*******************************************************************/
		virtual bool execute(const MS_ExcuteParam& _inParam) = 0;

		/*******************************************************************/
		/* 功    能：执行视觉任务（异步）
		/* 输入参数：_inParam 参数
		/* 输出参数：无
		/* 返 回 值：如果执行成功，返回true ,否则返回false
		/*******************************************************************/
		virtual bool executeAsyn(const MS_ExcuteParam& _inParam) = 0;

		/*******************************************************************/
		/* 功    能：获取当前对象执行后的结果数据
		/* 输入参数：无
		/* 输出参数：获得的结果数据
		/* 返 回 值：成功 or 失败
		/*******************************************************************/
		virtual bool getResult(QJsonObjectVec& _result)
		{
			return false;
		}

		/* 功    能：设置相机光源参数
		/* 输入参数：无
		/* 输出参数：获得的结果数据
		/* 返 回 值：成功 or 失败
		/*******************************************************************/
		virtual void setCameraLightParam() = 0;

	signals:
		//异步流程中，获取原始图像
		void SIG_VisionGetOriginalImage(MS_ImageInfoVec _imageInfoVec);

		//异步流程中，获取结果
		void SIG_VisionExecuteFinish(QJsonObjectVec _resultVec, MS_ImageInfoVec _imageInfoVec);
	};

	class MI_WaferGuide : public MI_VisionBase
	{
	public:
		~MI_WaferGuide()
		{
		}

		/*******************************************************************/
		/* 功    能：重置对准数据
		/* 输入参数：
		/* 输出参数：
		/* 返 回 值：
		/*******************************************************************/
		virtual void reset() = 0;

		/*******************************************************************/
		/* 功    能：确认Mapping坐标系方向上坐标是递增还是递减
		/* 输入参数：MS_WaferInputParameter输入参数
		/* 输出参数：
		/* 返 回 值：
		/*******************************************************************/
		virtual void setParameter(const MS_WaferInputParameter& _inparm) = 0;

		/*******************************************************************/
		/* 功    能：参考die对准确认接口
		/* 输入参数：参考die下标，参考die的map行坐标,与mapping对准的平台坐标
		/* 输出参数：
		/* 返 回 值：
		/*******************************************************************/
		virtual void confirmRefDie(const MS_ComfirmRefDieParm& _refDieParm) = 0;

		/*******************************************************************/
		/* 功    能：起始die对准确认接口
		/* 输入参数：MS_ComfirmStartDieParm
		/* 输出参数：
		/* 返 回 值：
		/*******************************************************************/
		virtual void confirmFirstDie(const MS_ComfirmStartDieParm& _startDieParm) = 0;

		/*******************************************************************/
		/* 功    能：根据对准信息，计算目标Die的平台坐标
		/* 输入参数：目标Die的map行坐标；目标Die的map列坐标
		/* 输出参数：目标Die的平台坐标
		/* 返 回 值：成功返回true，否则返回false
		/*******************************************************************/
		virtual bool getDieTabPos(MS_VisionAxisParam& _dieTabPos, const MS_GetDiePositionParmByMap& _parm) = 0;

		/*******************************************************************/
		/* 功    能：根据目标Die的平台坐标，计算目标Die的map坐标
		/* 输入参数：目标Die的平台坐标
		/* 输出参数：目标Die的map行坐标；目标Die的map列坐标；
		/* 返 回 值：成功返回true，否则返回false
		/*******************************************************************/
		virtual bool getDieMapCoor(MS_WaferMapCoor& _dieMapCoor, const MS_VisionAxisParam& _dieTabPos) = 0;
	};

	class VISIONLIBRARY_API MI_VisionCalibrateBase : public QObject, public MI_VisionBase
	{
		Q_OBJECT
	public:
		virtual ~MI_VisionCalibrateBase()
		{
		}

		virtual bool executeCalib(const MS_SetImagesParameter& _param) = 0;
		/*******************************************************************/
		/* 功    能：设置标定结束
		/* 输入参数：无
		/* 输出参数：无
		/* 返 回 值：如果成功，返回true ,否则返回false
		/*******************************************************************/
		virtual bool setCalibFinishedFlag() = 0;
		/*******************************************************************/
		/* 功    能：获取当前对象执行后的结果数据
		/* 输入参数：无
		/* 输出参数：无
		/* 返 回 值：获得的结果数据
		/*******************************************************************/
		virtual std::shared_ptr<MR_Result> getResult() = 0;
	signals:
		void SIG_SetDeviceParam(bool);
		//功能：标定相关计算执行完成后，发送该信号，然后软件获取相关结果；
		void SIG_VisionCalibExecuteFinish(bool);
	};

	class MI_VisionCalibrateDerived : public MI_VisionCalibrateBase
	{
		Q_OBJECT
	public:
		virtual ~MI_VisionCalibrateDerived()
		{
		}
		/*******************************************************************/
		/* 功    能：设定采集图像 视觉硬件相关参数（相机参数、光源参数）
		/* 输入参数：所需设定目标相机编号
		/* 输出参数：无
		/* 返 回 值：
		/*******************************************************************/
		virtual bool setDeviceParam(const std::vector<int>& _camNo) = 0;

		/*******************************************************************/
		/* 功    能：设定标定相关参数
		/* 输入参数：所需设定参数
		/* 输出参数：无
		/* 返 回 值：
		/*******************************************************************/
		virtual bool setCalibParam(const MS_SetCalibParameter& _calibParam) = 0;
	};

	class VISIONLIBRARY_API MI_VisionCommonFun
	{
	public:
		/*******************************************************************/
		/* 功    能：彩色QImage转灰度QImage
		/* 输入参数：彩色QImage
		/* 输出参数：无
		/* 返 回 值：灰度QImage
		/*******************************************************************/
		static bool convertImage2Gray(QImage& _outImage, const QImage& _inImage);

		/*******************************************************************/
		/* 功    能：QImage图像转MS_Image_Param图像
		/* 输入参数：QImage图像
		/* 输出参数：MS_Image_Param图像
		/* 返 回 值：成功 or 失败
		/*******************************************************************/
		static bool convertImage2MSImage(MS_Image_Param& _outImage, const QImage& _inImage);

		/*******************************************************************/
		/* 功    能：MS_Image_Param图像转QImage图像
		/* 输入参数：MS_Image_Param图像
		/* 输出参数：QImage图像
		/* 返 回 值：成功 or 失败
		/*******************************************************************/
		static bool convertImage2QImage(QImage& _outImage, const MS_Image_Param& _inImage);

		/*******************************************************************/
		/* 功    能：设置运行模式
		/* 输入参数：MS_OperationMode 运行模式数据
		/* 输出参数：无
		/* 返 回 值：无
		/*******************************************************************/
		static void setOperationMode(const MS_OperationMode& _operationMode);
	};

	/*******************************************************************/
	/* 功    能：初始化视觉库
	/* 输入参数：无
	/* 输出参数：错误代码向量
	/* 返 回 值：成功 or 失败
	/* 注：视觉库必须先初始化，然后才能使用
	/*******************************************************************/
	VISIONLIBRARY_API bool initVisionLib(const MS_VisionInitParam& _visionParm, std::vector<MN_VisionError::MS_VisionErrorInfo>& _errorInfoVec);

	/*******************************************************************/
	/* 功    能：获取某个视觉模块
	/* 输入参数：_inParam 视觉参数，如相机编号、工位号、任命名称
	/* 输出参数：无
	/* 返 回 值：执行类的指针（通用接口，执行任务流程）
	/*******************************************************************/
	VISIONLIBRARY_API MI_VisionGeneral* getVisionGeneral(const MS_VisionParamGeneral& _inParam, MN_VisionError::MS_VisionErrorInfo* _errorInfo = nullptr);

	/*******************************************************************/
	/* 功    能：获取某个视觉模块
	/* 输入参数：_inParam 视觉参数，如相机编号、工位号、标定类型
	/* 输出参数：无
	/* 返 回 值：标定类的指针
	/*******************************************************************/
	VISIONLIBRARY_API MI_VisionCalibrateDerived* getVisionCalib(const MS_CalibrateModuleParam& _inParam, MN_VisionError::MS_VisionErrorInfo* _errorInfo = nullptr);

	/*******************************************************************/
	/* 功    能：获取视觉晶圆定位模块指针
	/* 输入参数：无
	/* 输出参数：无
	/* 返 回 值：视觉晶圆定位模块指针
	/*******************************************************************/
	VISIONLIBRARY_API MI_WaferLocate* getWaferLocate(const MS_VisionParamGeneral& _inParam, MN_VisionError::MS_VisionErrorInfo* _errorInfo = nullptr);

	/*******************************************************************/
	/* 功    能：获取视觉晶圆引导模块指针
	/* 输入参数：无
	/* 输出参数：无
	/* 返 回 值：视觉晶圆引导模块指针
	/*******************************************************************/
	VISIONLIBRARY_API MI_WaferGuide* getWaferGuide(const MS_GetWaferGuideParm& _pram);

	/*******************************************************************/
	/* 功    能：获取变换模块
	/* 输入参数：无
	/* 输出参数：无
	/* 返 回 值：变换类的指针
	/*******************************************************************/
	VISIONLIBRARY_API MI_Transformation* getVisionTransformation();

	/*******************************************************************/
	/* 功    能：获取任务管理模块
	/* 输入参数：无
	/* 输出参数：无
	/* 返 回 值：任务管理类的指针
	/*******************************************************************/
	VISIONLIBRARY_API MI_TaskOperation* getVisionTaskOperation();

}