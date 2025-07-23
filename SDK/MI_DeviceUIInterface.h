#pragma once
#include <QWidget>
#include "MS_DataDefine.h"
#include "ML_Global.h"

class MU_LightCameraSetting;
class MU_VisionSystemParameterCfg;
class MU_VisualSiteConfigSelector;

namespace MN_VisionDevice
{
    class DEVICE_LIBRARY_API MI_DeviceUIBase: public QWidget
    {
        Q_OBJECT

    public:
        MI_DeviceUIBase(QWidget* _pParentDlg = Q_NULLPTR) {}
        virtual ~MI_DeviceUIBase() {}

        virtual QWidget* getWidget()
        {
            return nullptr;
        }

        virtual bool showDeviceDlg(QWidget* _pParentDlg = Q_NULLPTR)
        {
            return false;
        }

        virtual bool save()
        {
            return false;
        }
    };

    //视觉系统配置界面
    class  DEVICE_LIBRARY_API MI_VisionSystemParamterCfgUi
        : public MI_DeviceUIBase
    {
        Q_OBJECT

    public:
        MI_VisionSystemParamterCfgUi(QWidget* _pParentDlg = Q_NULLPTR);
        virtual ~MI_VisionSystemParamterCfgUi();

        QWidget* getWidget() override;
        bool showDeviceDlg(QWidget* _pParentDlg = Q_NULLPTR) override;
        bool save() override;
        void setWorkStationInfo(const std::map<int, MS_StationInformation>& _mpAllStstionInfo);
    private:
        MU_VisionSystemParameterCfg* m_pVisionSystemParamCfgUi = nullptr;
    };

    //视觉配置选择界面
    class  DEVICE_LIBRARY_API MI_VisualSiteConfigSelectorUi
        : public MI_DeviceUIBase
    {
        Q_OBJECT

    public:
        MI_VisualSiteConfigSelectorUi(QWidget* _pParentDlg = Q_NULLPTR);
        virtual ~MI_VisualSiteConfigSelectorUi();

        QWidget* getWidget() override;
        bool showDeviceDlg(QWidget* _pParentDlg = Q_NULLPTR) override;
        bool save() override;
    private:
        MU_VisualSiteConfigSelector* m_pVisualSiteConfigSelectorUi = nullptr;
    };

    //光源参数设置界面
    class  DEVICE_LIBRARY_API MI_DeviceLightSettingUI
        : public MI_DeviceUIBase
    {
        Q_OBJECT

    public:
        MI_DeviceLightSettingUI(QWidget* _pParentDlg = Q_NULLPTR);
        virtual ~MI_DeviceLightSettingUI();

        QWidget* getWidget() override;
        bool showDeviceDlg(QWidget* _pParentDlg = Q_NULLPTR) override;
        bool save() override;
    };

    //光源系统设置界面
    class DEVICE_LIBRARY_API  MI_DeviceLightSystemUI
        : public MI_DeviceUIBase
    {
        Q_OBJECT

    public:
        MI_DeviceLightSystemUI(QWidget* _pParentDlg = Q_NULLPTR);
        virtual ~MI_DeviceLightSystemUI();

        QWidget* getWidget() override;
        bool showDeviceDlg(QWidget* _pParentDlg = Q_NULLPTR) override;
        bool save() override;
    };

    //相机和光源参数设置界面
    class  DEVICE_LIBRARY_API MI_DeviceCameraAndLightSetUI
        : public MI_DeviceUIBase
    {
        Q_OBJECT

    public:
        MI_DeviceCameraAndLightSetUI(QWidget* _pParentDlg = Q_NULLPTR);
        virtual ~MI_DeviceCameraAndLightSetUI();

        QWidget* getWidget() override;
        bool showDeviceDlg(MN_VisionDevice::ME_CameraNo _cameraNo, bool _isSystem = false, QWidget* _pParentDlg = Q_NULLPTR);
        bool save() override;

    private:
        std::shared_ptr<MU_LightCameraSetting> m_lightCameraSetting{nullptr};
    };
}

