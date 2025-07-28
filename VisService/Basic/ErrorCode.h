#pragma once
#include "BasicDefs.h"
#include <map>
#include <string>

VISSERVICE_NAMESPACE_BEGIN

enum class ModuleErrorCode
{
	Normal = 200,
	Device = 200,
	Matching,
	Inspection,
	Calibration,
	TaskFlow,
	Transformer,

};
const std::map<ModuleErrorCode, std::string> g_moduleErrorCodeDescribleMap =
{
	{ ModuleErrorCode::Normal,		"视觉通用模块" },
	{ ModuleErrorCode::Device,		"视觉设备模块" },
	{ ModuleErrorCode::Matching,	"视觉定位模块" },
	{ ModuleErrorCode::Inspection,	"视觉检测模块" },
	{ ModuleErrorCode::Calibration,	"视觉标定模块" },
	{ ModuleErrorCode::TaskFlow,	"视觉任务模块" },
	{ ModuleErrorCode::Transformer, "视觉转换模块" }
};

//错误代码：6位 
//编码范围 102000~103999视觉使用
//102000  OK
//102001  系统错误
enum class ErrorCode
{
	Null = 102000,
	SystemError = 102001,
	NullPointer,
};

const std::map<ErrorCode, std::string> g_errorCodeDescribleMap =
{
	{ ErrorCode::Null,			"正常" },
	{ ErrorCode::SystemError,	"系统错误" },
};

const std::map<ErrorCode, std::string> g_errCodeSolutionMap =
{
	{ ErrorCode::Null,			"正常" },
	{ ErrorCode::SystemError,	"系统错误，联系供应商解决" },
};

struct ErrorParams
{
	ModuleErrorCode moduleErrorCode_;
	ErrorCode errorCode_;
	std::string errorMsg_;
	std::string procName_;
	ErrorParams(ModuleErrorCode m, ErrorCode e, std::string msg, std::string proc)
		: moduleErrorCode_(m), errorCode_(e), errorMsg_(std::move(msg)), procName_(std::move(proc)) 
	{
	}
	std::string ErrorDescrible()
	{
		std::string describle = g_moduleErrorCodeDescribleMap.at(moduleErrorCode_) + g_errorCodeDescribleMap.at(errorCode_);
		return describle;
	}

	std::string ErrorCodeSolution()
	{
		return g_errCodeSolutionMap.at(errorCode_);
	}
};

VISSERVICE_NAMESPACE_END