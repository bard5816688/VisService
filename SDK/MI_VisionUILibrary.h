#pragma once
#include <QWidget>
#include <vector>
#include "ME_ErrorInfo.h"
#include "MS_VisionLibrary.h"
#include "MS_VisionAuthorityCode.h"

namespace MN_VisionAlgorithm
{
    class MI_VisionGeneralUIPrivate;
    class MI_VisionForceLocateUIPrivate;
    class MI_VisionCalibrateUIPrivate;
    class MI_WaferLocateUIPrivate;
    class MI_WaferGuideUIPrivate;
    class MI_VisionFlowMgrUIPrivate;
    struct MS_AuthorityInfo;
    class MI_VisionConfigurationUIPrivate;

    class VISIONLIBRARY_API MI_VisionUIBase : public QObject
    {
        Q_OBJECT

    public:
        MI_VisionUIBase();
        virtual ~MI_VisionUIBase() {}

    public:
    	virtual QWidget* getWidget() { return nullptr; }
        virtual bool setPos(const std::vector<MS_VisionAxisParam>& _axisPos, const std::vector<MS_VisionAxisParam>& _camPos) { return false; }
        virtual bool setAutoFocusData(const std::vector<MS_AutoFocusData>& _autoFocusData) { return false; }
        virtual bool closeWidget() { return true; }
        virtual bool wakeCamera() { return true; }
        virtual MN_VisionError::MS_VisionErrorInfo getLastErrorInfo()
        {
            return  MN_VisionError::MS_VisionErrorInfo();
        };
         /*******************************************************************/
        /* 功    能：设置算法任务中某些算法是否执行属性
        /* 输入参数：_inParam 视觉参数，如相机编号、工位号、任务名称
        /*           _algorithmPropVec: 多个算法是否执行的参数
        /*           std::pair<ME_AlgFunctionID, bool>  代表对应ID算法功能是否需要执行，true:需要执行；false：不执行；
        /* 输出参数：无
        /* 返 回 值：true:设置成功；false：设置失败；
        /*******************************************************************/
        virtual bool setVisionAlgProp(const MS_VisionParamGeneral& _inParam, const std::vector<std::pair<ME_AlgFunctionID, bool>>& _algorithmPropVec) {return true; }
        virtual void setLoginInfo(const MS_AuthorityInfo& _authorityInfo);
        virtual void getLoginInfo(MS_AuthorityInfo& _authorityInfo);

    protected:
		MS_AuthorityInfo m_authorityInfo;
		QString m_name  = "authorityInfo";

    private:
		bool saveAuthorityInfo(const MS_AuthorityInfo& _AuthorityInfo);
		bool getAuthorityInfo(MS_AuthorityInfo& _AuthorityInfo);
        QString  qvector2Str(const QVector<int> _intData);
        QVector<int> str2QVector(const QString& _string);

    signals:
        //功能：视觉做模板前，由按钮触发该信号；
        //然后软件调用setPos，设置坐标；视觉保存相关信息，为做模板做准备；
        //注：如有多个模板，做每个模板前，都需要触发该信号；
        void SIG_VisionUiImageDetermine();
        //功能：视觉相关计算执行完成后，发送该信号，然后软件获取相关结果；
        void SIG_VisionUiExecuteFinish(bool);
        void SIG_ShowWidget(ME_ShowWidgetType _type, QPoint _point = QPoint(400, 400));
        void SIG_AutoFocus(MS_AutoFocusSingnalParam _param);
        void SIG_AutoFocusResult(MS_AutoFocusResult _autoFocusResult);
    };

    class VISIONLIBRARY_API MI_VisionGeneralUI : public MI_VisionUIBase
    {
    	Q_OBJECT

    public:
    	MI_VisionGeneralUI();
    	virtual ~MI_VisionGeneralUI();

    public:
    	bool showParamDlg(MS_VisionParamGeneral _inParam, QWidget* _pParentDlg = Q_NULLPTR);
        bool setImg(const MS_Image_Param& _inImg);
        bool getModelInfo(MS_ModelInfo& _modelInfo);            //获取模板信息
        QWidget* getAlgorithmPropWidget(const MS_VisionParamGeneral& _inParam);                      //获取算法属性窗口，设置逻辑算法的启用、不启用

        virtual bool setVisionAlgProp(const MS_VisionParamGeneral& _inParam, const std::vector<std::pair<ME_AlgFunctionID, bool>>& _algorithmPropVec) override;

        virtual QWidget* getWidget() override;
    	virtual bool setPos(const std::vector<MS_VisionAxisParam>& _axisPos, const std::vector<MS_VisionAxisParam>& _camPos) override;
        virtual bool closeWidget() override;
        virtual bool wakeCamera() override;
        virtual void setLoginInfo(const MS_AuthorityInfo& _authorityInfo) override;
        virtual MN_VisionError::MS_VisionErrorInfo getLastErrorInfo() override;

    signals:
        void SIG_StartAcquisitionOtf(double _dTriggerPosition);//开始飞拍采集信号

    private:
        std::shared_ptr<MI_VisionGeneralUIPrivate> m_private = nullptr;
    };

    //手动强制定位
    class VISIONLIBRARY_API MI_VisionForceLocateUI : public MI_VisionUIBase
    {
    	Q_OBJECT

    public:
    	MI_VisionForceLocateUI();
    	virtual ~MI_VisionForceLocateUI();
        QWidget* getWidget()override;
        bool setPos(const std::vector<MS_VisionAxisParam>& _axisPos, const std::vector<MS_VisionAxisParam>& _camPos)override;
        bool closeWidget()override;
        bool wakeCamera()override;
        MN_VisionError::MS_VisionErrorInfo getLastErrorInfo()override;
        void setLoginInfo(const MS_AuthorityInfo& _authorityInfo)override;
    public:
    	bool showParamDlg(const MS_SpecificFunctionParam& _inParam, QWidget* _pParentDlg = Q_NULLPTR);
        bool setImg(const MS_Image_Param& _inImg);
        bool setPos(const MS_VisionAxisParam& _curAxisPos, const MS_VisionAxisParam& _curCameraPos = MS_VisionAxisParam());
    	bool getImage(MS_ImageInfoVec& _images);
    	bool getOriginalImage(MS_ImageInfo& _image);
    	bool getResult(QJsonObjectVec& _locateRes); //获取手动定位结果

    private:
        std::shared_ptr<MI_VisionForceLocateUIPrivate> m_private = nullptr;
        //std::shared_ptr<MI_VisionUIBase> m_visionBase = nullptr;
    };

    //任务流程管理
    class VISIONLIBRARY_API MI_VisionFlowMgrUI : public MI_VisionUIBase
    {
    	Q_OBJECT

    public:
    	MI_VisionFlowMgrUI();
    	virtual ~MI_VisionFlowMgrUI();

    public:
    	bool showParamDlg(QWidget* _pParentDlg = Q_NULLPTR);
        virtual void setLoginInfo(const MS_AuthorityInfo& _authorityInfo) override;
    private:
        std::shared_ptr<MI_VisionFlowMgrUIPrivate> m_private = nullptr;
    };

    class VISIONLIBRARY_API MI_WaferLocateUI : public MI_VisionUIBase
    {
    	Q_OBJECT

    public:
        MI_WaferLocateUI();
        virtual ~MI_WaferLocateUI();

    public:
        bool showParamDlg(MS_VisionParamGeneral _inParam, QWidget* _pParentDlg = Q_NULLPTR);
        bool setImg(const MS_Image_Param& _inImg);
        bool getModelInfo(MS_ModelInfo& _modelInfo);            //获取模板信息
        virtual QWidget* getWidget() override;
        virtual bool setPos(const std::vector<MS_VisionAxisParam>& _axisPos, const std::vector<MS_VisionAxisParam>& _camPos) override;
        virtual bool closeWidget() override;
        virtual bool wakeCamera() override;
        virtual bool setVisionAlgProp(const MS_VisionParamGeneral& _inParam, const std::vector<std::pair<ME_AlgFunctionID, bool>>& _algorithmPropVec) override;
        virtual void setLoginInfo(const MS_AuthorityInfo& _authorityInfo) override;
        virtual MN_VisionError::MS_VisionErrorInfo getLastErrorInfo() override;

    signals:
        void SIG_MoveToPosition(MS_VisionAxisParam);

    private:
        std::shared_ptr<MI_WaferLocateUIPrivate> m_private = nullptr;
    };

    class VISIONLIBRARY_API MI_WaferGuideUI : public MI_VisionUIBase
    {
    	Q_OBJECT

    public:
        MI_WaferGuideUI();
    	virtual ~MI_WaferGuideUI();

    public:
        bool showParamDlg(const MS_WaferShowUiParm&, QWidget * _parent = Q_NULLPTR);
        bool getDieSize(MS_DieSize& _dieSize, const QString& _taskName);           //任务名带|
        bool setImg(const MS_Image_Param& _inImg);
        virtual bool setPos(const std::vector<MS_VisionAxisParam>& _axisPos, const std::vector<MS_VisionAxisParam>& _camPos) override;
        virtual bool closeWidget() override;
        virtual bool wakeCamera() override;
        virtual void setLoginInfo(const MS_AuthorityInfo& _authorityInfo) override;
        virtual MN_VisionError::MS_VisionErrorInfo getLastErrorInfo() override;

    signals:
        void SIG_WaferContourSnapPositionDetermine(int);
        void SIG_MoveToPosition(MS_VisionAxisParam);
        void SIG_WaferContourResult(MS_WaferContourResult);

    private:
        std::shared_ptr<MI_WaferGuideUIPrivate> m_private = nullptr;
    };

    class VISIONLIBRARY_API MI_VisionCalibrateUI : public MI_VisionUIBase
    {
    	Q_OBJECT

    public:
    	MI_VisionCalibrateUI();
    	virtual ~MI_VisionCalibrateUI();
    public:
    	//UI界面显示函数
    	bool showParamDlg(MS_CalibrateModuleParam _inParam, QWidget* _pParentDlg = Q_NULLPTR);   //显示UI界面
        bool setImg(const MS_Image_Param& _inImg);
        bool executeCalib(const MS_SetImagesParameter& _param);
        std::shared_ptr<MR_Result> getResult();
        virtual QWidget* getWidget() override;
        virtual bool setPos(const std::vector<MS_VisionAxisParam>& _axisPos, const std::vector<MS_VisionAxisParam>& _camPos) override;//接收轴相关位置
        virtual bool closeWidget() override;
        virtual bool wakeCamera() override;
        virtual void setLoginInfo(const MS_AuthorityInfo& _authorityInfo) override;
        virtual MN_VisionError::MS_VisionErrorInfo getLastErrorInfo() override;

    signals:
    	void SIG_MoveTo();//标定移至信号  	 	                                   
    	void SIG_startCalib(std::vector<MS_VisionAxisParam> _value); //发送开始标定信号(包括相机和轴、相机和WaferTable手眼标定、旋转中心标定、相机和轴尖对位标定)(_value为轴需要移动的位置点坐标)
    	void SIG_startCameraAndAxisRelationCalib(std::vector<MS_VisionAxisParam> _axisPos, std::vector<MS_VisionAxisParam> _camPos, MS_CameraAndAxisRelationCalibParam _calibParam); //发送相机和轴同步标定信号 
        void SIG_MoveToPosition(MS_VisionAxisParam);

    private:
        std::shared_ptr<MI_VisionCalibrateUIPrivate> m_private = nullptr;
    };

	class VISIONLIBRARY_API MI_VisionConfigurationUI :public QObject
    {
        Q_OBJECT

    public:
        MI_VisionConfigurationUI();
        virtual ~MI_VisionConfigurationUI();
        QWidget* getVisionCfgWidget();
        QWidget* getHandeyeTypeSettingWidget();

    private:
        std::shared_ptr<MI_VisionConfigurationUIPrivate> m_private = nullptr;
    };
}