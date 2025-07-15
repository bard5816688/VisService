#pragma once

#include "BasicReturn.h"
#include "Tuple.h"
#include "Region.h"

VISALGORITHM_NAMESPACE_BEGIN

using ClearProc = void(__cdecl*)(void*);

template<typename T>
concept IsImageStrategy = RuleOfFive<T> && requires(
	T t,
	const T& ct,
	const char* constCharPtr,
	void* voidPtr,
	ClearProc clearProc,
	int64_t i64,
	int64_t* i64Ptr
	)
{
	{ ct.GetImpl() };
	{ t.GenImageConst(constCharPtr, i64, i64) }-> std::same_as<ResultVoid>;
	{ t.GenImage1(constCharPtr, i64, i64, voidPtr) }-> std::same_as<ResultVoid>;
	{ t.GenImage1Extern(constCharPtr, i64, i64, voidPtr, clearProc) }-> std::same_as<ResultVoid>;
	{ ct.GetImageSize(i64Ptr, i64Ptr) }-> std::same_as<ResultVoid>;
	{ ct.CountChannels() }-> std::same_as<Result<Tuple>>;
};

VISALGORITHM_NAMESPACE_END