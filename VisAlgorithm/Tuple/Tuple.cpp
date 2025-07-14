#include "TupleInternal.h"
#include "BasicReturnInternal.h"

VISALGORITHM_NAMESPACE_BEGIN

class TupleImpl
{
public:
	TupleImpl()
	{
	}

	HalconCpp::HTuple hTuple_;//底层也可以替换为VisTuple(自定义/其他Dll提供的Tuple类型)   
};

Tuple::Tuple()
	: tupleImpl_(new TupleImpl)
{

}

Tuple::Tuple(const TupleElement& element)
{
	std::visit([=](const auto& value)
		{
			using T = std::decay_t<decltype(value)>;
			if constexpr (std::is_same_v<T, std::monostate>)
			{
			}
			else if constexpr (std::is_same_v<T, std::string>)
			{
				tupleImpl_->hTuple_ = HalconCpp::HTuple(value.c_str());
			}
			else
			{
				tupleImpl_->hTuple_ = HalconCpp::HTuple(value);
			}
		}, element);
}

Tuple::~Tuple()
{
	delete tupleImpl_;
}

Tuple::Tuple(const Tuple& other)
{
	tupleImpl_ = new TupleImpl(*other.tupleImpl_);
}

Tuple& Tuple::operator=(const Tuple& other)
{
	if (this != &other) 
	{
		delete tupleImpl_;
		tupleImpl_ = new TupleImpl(*other.tupleImpl_);
	}
	return *this;
}

Tuple::Tuple(Tuple&& other) noexcept
{
	tupleImpl_ = other.tupleImpl_;
	other.tupleImpl_ = nullptr;
}

Tuple& Tuple::operator=(Tuple&& other) noexcept
{
	if (this != &other) 
	{
		delete tupleImpl_;
		tupleImpl_ = other.tupleImpl_;
		other.tupleImpl_ = nullptr;
	}
	return *this;
}

Tuple& Tuple::Append(const Tuple& tuple)
{

	tupleImpl_->hTuple_ = tupleImpl_->hTuple_.Append(tuple.tupleImpl_->hTuple_);
	return *this;
}

Result<TupleElementType> Tuple::Type(size_t idx)
{
	if (idx >= tupleImpl_->hTuple_.Length())
	{
		return VISALGORITHM__RETURN_UNEXPECTE("Result<TupleElement> TupleImpl::At(size_t idx)", "Tuple index out of bounds", ErrorCode::StdExcepetion);
	}
	return VISALGORITHM_WRAP_TRY_CATCH(tupleImpl_->hTuple_[idx].Type()).transform([](HalconCpp::HTupleElementType type)
		{
			switch (type)
			{
			case HalconCpp::eElementTypeLong:
				return TupleElementType::Int;
			case HalconCpp::eElementTypeDouble:
				return TupleElementType::Double;
			case HalconCpp::eElementTypeString:
				return TupleElementType::String;
			case HalconCpp::eElementTypeHandle:
			case HalconCpp::eElementTypeMixed:
			case HalconCpp::eElementTypeUndef:
			default:
				return TupleElementType::Null;
			}
		});
}

Result<TupleElement> Tuple::At(size_t idx) const
{
	if (idx >= tupleImpl_->hTuple_.Length())
	{
		return VISALGORITHM__RETURN_UNEXPECTE("Result<TupleElement> TupleImpl::At(size_t idx)", "Tuple index out of bounds", ErrorCode::StdExcepetion);
	}
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(elementType, tupleImpl_->hTuple_[idx].Type());
	switch (elementType.value())
	{
	case HalconCpp::eElementTypeLong:
	{
		VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(i, tupleImpl_->hTuple_[idx].I());
		return i;
	}
	case HalconCpp::eElementTypeDouble:
	{
		VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(d, tupleImpl_->hTuple_[idx].D());
		return d;
	}
	case HalconCpp::eElementTypeString:
	{
		VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(s, tupleImpl_->hTuple_[idx].S().Text());
		return s;
	}
	case HalconCpp::eElementTypeHandle:
	case HalconCpp::eElementTypeMixed:
	case HalconCpp::eElementTypeUndef:
	default:
		return std::monostate();
	}
}

Tuple Tuple::FromVector(const std::vector<TupleElement>& values)
{
	Tuple tuple;
	for (auto ele : values)
	{
		tuple.Append(ele);
	}
	return tuple;
}

HalconCpp::HTuple TupleInternal::GetHTuple(const Tuple& tuple)
{
	return tuple.tupleImpl_->hTuple_;
}

Tuple TupleInternal::FromHTuple(const HalconCpp::HTuple& hTuple)
{
	Tuple tuple;
	tuple.tupleImpl_->hTuple_ = hTuple;
	return tuple;
}

Result<Tuple> TupleInternal::ResultFromHTuple(const Result<HalconCpp::HTuple>& res)
{
	return res.transform(TupleInternal::FromHTuple);
}

VISALGORITHM_NAMESPACE_END