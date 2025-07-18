#pragma once
#include "BasicDefs.h"
#include <QVariant>
#include "QtPropertyBrowser/QtVariantProperty.h"
#include "QtPropertyBrowser/QtTreePropertyBrowser.h"

VISSERVICE_NAMESPACE_BEGIN

template <typename T>
class ParamEditor : public QObject {
public:
    ParamEditor(T* target)
		: params_(target)
		, manager_(new QtVariantPropertyManager())
        , factory_(new QtVariantEditorFactory())
        , browser_(new QtTreePropertyBrowser())
    {
        m_browser->setFactoryForManager(manager_, factory_);
        build();
    }

    virtual void build()
    {

    }

    QtTreePropertyBrowser* browser() const 
    { 
        return m_browser; 
    }

protected:
    T* params_;
    QtVariantPropertyManager* manager_;
    QtVariantEditorFactory* factory_;
    QtTreePropertyBrowser* browser_;
};


VISSERVICE_NAMESPACE_END