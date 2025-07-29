#pragma once
#include <QVariant>
#include "QtPropertyBrowser/QtVariantProperty.h"
#include "QtPropertyBrowser/QtTreePropertyBrowser.h"

template <typename T>
class ParamEditor : public QObject {
public:
    ParamEditor(T* target)
		: params_(target)
		, manager_(new QtVariantPropertyManager())
        , factory_(new QtVariantEditorFactory())
        , browser_(new QtTreePropertyBrowser())
    {
        browser_->setFactoryForManager(manager_, factory_);
        build();
    }

    virtual void build()
    {

    }

    QtTreePropertyBrowser* browser() const 
    { 
        return browser_;
    }

protected:
    T* params_;
    QtVariantPropertyManager* manager_;
    QtVariantEditorFactory* factory_;
    QtTreePropertyBrowser* browser_;
};