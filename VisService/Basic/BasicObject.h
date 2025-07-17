#pragma once
#include <QWidget>
#include "../Basic/BasicReturn.h"

VISSERVICE_NAMESPACE_BEGIN

template<typename T, typename Result>
concept IsExecutableObj = RuleOfFive<T> && requires(
	T t,
	const T & ct
	)
{
	{ t.performTeaching() }-> std::same_as<Return<QWidget*>>;
	{ t.performTask() }-> std::same_as<Return<Result>>;
};


template<typename Drived, typename Result>
	requires IsExecutableObj<Drived, Result>
class Executable
{
public:
	Return<QWidget*> performTeaching()
	{
		Drived* drived = static_cast<Drived*>(this);
		VIS_RETURN_IF_NULLPTR_WITH_MSG(drived, "Null pointer error, T type is not a derived class, T type must be a derived class of Executable!");
		return drived->performTeaching();
	}
	Return<Result> performTask()
	{
		Drived* drived = static_cast<Drived*>(this);
		VIS_RETURN_IF_NULLPTR_WITH_MSG(drived, "Null pointer error, T type is not a derived class, T type must be a derived class of Executable!");
		return drived->performTask();
	}

};

VISSERVICE_NAMESPACE_END