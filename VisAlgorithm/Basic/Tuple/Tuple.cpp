#include "TupleInternal.h"
#include "HalconCpp.h"

VISALGORITHM_NAMESPACE_BEGIN

class TupleImpl
{
public:
	TupleImpl()
	{
	}

	TupleImpl(const TupleElement& element)
	{
		std::visit([=](const auto& value)
			{
				using T = std::decay_t<decltype(value)>;
				if constexpr (std::is_same_v<T, std::monostate>)
				{
				}
				else if constexpr (std::is_same_v<T, std::string>)
				{
					hTuple_ = HalconCpp::HTuple(value.c_str());
				}
				else
				{
					hTuple_ = HalconCpp::HTuple(value);
				}
			}, element);
	}

	TupleElement At(size_t idx)
	{
		HalconCpp::HTupleElementType elementType = hTuple_[idx].Type();
		switch (elementType)
		{
		case HalconCpp::eElementTypeLong:
			return TupleElement(hTuple_[idx].I());
		case HalconCpp::eElementTypeDouble:
			return TupleElement(hTuple_[idx].D());
		case HalconCpp::eElementTypeString:
			return TupleElement(hTuple_[idx].S().Text());
		case HalconCpp::eElementTypeHandle:
		case HalconCpp::eElementTypeMixed:
		case HalconCpp::eElementTypeUndef:
		default:
			return std::monostate();
		}
	}

	HalconCpp::HTuple hTuple_;//底层也可以替换为VisTuple(自定义/其他Dll提供的Tuple类型)   
};

Tuple::Tuple()
	: tupleImpl_(new TupleImpl)
{

}

Tuple::Tuple(const TupleElement& element)
	: tupleImpl_(new TupleImpl(element))
{

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
	tupleImpl_->hTuple_ = tupleImpl_->hTuple_.Append(tuple.ImplPtr()->hTuple_);
	return *this;
}

TupleElementType Tuple::Type(size_t idx)
{
	HalconCpp::HTupleElementType elementType = tupleImpl_->hTuple_[idx].Type();
	switch (elementType)
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

TupleImpl* Tuple::ImplPtr() const
{
	return tupleImpl_;
}

TupleElement Tuple::At(size_t index) const
{
	return tupleImpl_->At(index);
}

HalconCpp::HTuple GetHTuple(const Tuple& tuple)
{
	return tuple.ImplPtr()->hTuple_;
}

Tuple FromHTuple(const HalconCpp::HTuple& hTuple)
{
	Tuple tuple;
	tuple.ImplPtr()->hTuple_ = hTuple;
	return tuple;
}

VISALGORITHM_NAMESPACE_END