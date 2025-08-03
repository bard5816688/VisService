#include "PipeLineUi.h"
#include "../Module/ModuleObject.h"

VISSERVICE_NAMESPACE_BEGIN

PipeLineUi::PipeLineUi(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

PipeLineUi::~PipeLineUi()
{}

ReturnVoid PipeLineUi::RegisterModule(ModuleUiBase* nodePtr, const std::string& moduleName)
{
	VIS_RETURN_IF_NULLPTR_WITH_MSG(nodePtr, ModuleErrorCode::TaskFlow, "ModuleUiBase* can not nullptr!");
	QTreeWidgetItem* newItem = new QTreeWidgetItem;
	newItem->setText(0, QString::fromStdString(moduleName));
	ui.treeWidget_moduleTree->addTopLevelItem(newItem);                
	int newModuleUiIdx = ui.stackedWidget_moduleUi->addWidget(nodePtr);
	connect(ui.treeWidget_moduleTree, &QTreeWidget::itemClicked, [=](QTreeWidgetItem* item, int column)
		{
			if (newItem == item)
			{
				ui.stackedWidget_moduleUi->setCurrentIndex(newModuleUiIdx);
			}
		});
}

VISSERVICE_NAMESPACE_END