#include "ShapeMatchingUi.h"

VISSERVICE_NAMESPACE_BEGIN

ShapeMatchingUi::ShapeMatchingUi(const std::string& taskName, QWidget *parent)
	: ModuleUiBase(taskName, parent)
{
	ui.setupUi(this);
}

ShapeMatchingUi::~ShapeMatchingUi()
{

}

std::string ShapeMatchingUi::GetModuleName()
{
	return "ShapeMatching";
}

REGISTER_MODULE_UI("ShapeMatching", ShapeMatchingUi);

VISSERVICE_NAMESPACE_END