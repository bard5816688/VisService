#include "TupleInternal.h"
#include "BasicReturnInternal.h"

VISALGORITHM_NAMESPACE_BEGIN

class HTupleStrategy::Impl
{
public:
	HalconCpp::HTuple hTuple_; 
};

HTupleStrategy HTupleStrategy::FromVector(const std::vector<TupleElement>& values)
{
	HTupleStrategy tuple;
	for (auto ele : values)
	{
		tuple.Append(ele);
	}
	return tuple;
}

HTupleStrategy::HTupleStrategy()
	: impl_(new Impl)
{

}

HTupleStrategy::HTupleStrategy(const TupleElement& element)
{
	std::visit([=](const auto& value)
		{
			using T = std::decay_t<decltype(value)>;
			if constexpr (std::is_same_v<T, std::monostate>)
			{
			}
			else if constexpr (std::is_same_v<T, std::string>)
			{
				impl_->hTuple_ = HalconCpp::HTuple(value.c_str());
			}
			else
			{
				impl_->hTuple_ = HalconCpp::HTuple(value);
			}
		}, element);
}

HTupleStrategy::~HTupleStrategy()
{
	delete impl_;
}

HTupleStrategy::HTupleStrategy(const HTupleStrategy& other)
{
	impl_ = new Impl(*other.impl_);
}

HTupleStrategy& HTupleStrategy::operator=(const HTupleStrategy& other)
{
	if (this != &other)
	{
		delete impl_;
		impl_ = new Impl(*other.impl_);
	}
	return *this;
}

HTupleStrategy::HTupleStrategy(HTupleStrategy&& other) noexcept
{
	impl_ = other.impl_;
	other.impl_ = nullptr;
}

HTupleStrategy& HTupleStrategy::operator=(HTupleStrategy&& other) noexcept
{
	if (this != &other)
	{
		delete impl_;
		impl_ = other.impl_;
		other.impl_ = nullptr;
	}
	return *this;
}

HTupleStrategy::Impl* HTupleStrategy::GetImpl() const
{
	return impl_;
}

HTupleStrategy& HTupleStrategy::Append(const HTupleStrategy& tuple)
{

	impl_->hTuple_ = impl_->hTuple_.Append(tuple.impl_->hTuple_);
	return *this;
}

Result<TupleElementType> HTupleStrategy::Type(size_t idx)
{
	if (idx >= impl_->hTuple_.Length())
	{
		return VISALGORITHM__RETURN_UNEXPECTE("Result<TupleElement> Impl::At(size_t idx)", "HTupleStrategy index out of bounds", ErrorCode::StdExcepetion);
	}
	return VISALGORITHM_WRAP_TRY_CATCH(impl_->hTuple_[idx].Type()).transform([](HalconCpp::HTupleElementType type)
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

Result<TupleElement> HTupleStrategy::At(size_t idx) const
{
	if (idx >= impl_->hTuple_.Length())
	{
		return VISALGORITHM__RETURN_UNEXPECTE("Result<TupleElement> Impl::At(size_t idx)", "HTupleStrategy index out of bounds", ErrorCode::StdExcepetion);
	}
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(elementType, impl_->hTuple_[idx].Type());
	switch (elementType.value())
	{
	case HalconCpp::eElementTypeLong:
	{
		VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(i, impl_->hTuple_[idx].I());
		return i;
	}
	case HalconCpp::eElementTypeDouble:
	{
		VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(d, impl_->hTuple_[idx].D());
		return d;
	}
	case HalconCpp::eElementTypeString:
	{
		VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(s, impl_->hTuple_[idx].S().Text());
		return s;
	}
	case HalconCpp::eElementTypeHandle:
	case HalconCpp::eElementTypeMixed:
	case HalconCpp::eElementTypeUndef:
	default:
		return std::monostate();
	}
}

template<typename TupleStrategy>
HalconCpp::HTuple TupleHalconUtils<TupleStrategy>::GetHTuple(const TupleStrategy& tuple)
{
	return tuple.GetImpl()->hTuple_;
}

template<typename TupleStrategy>
TupleStrategy TupleHalconUtils<TupleStrategy>::FromHTuple(const HalconCpp::HTuple& hTuple)
{
	HTupleStrategy tuple;
	tuple.GetImpl()->hTuple_ = hTuple;
	return tuple;
}

template<typename TupleStrategy>
Result<TupleStrategy> TupleHalconUtils<TupleStrategy>::ResultFromHTuple(const Result<HalconCpp::HTuple>& res)
{
	return res.transform(TupleHalconUtils<TupleStrategy>::FromHTuple);
}

template class TupleHalconUtils<HTupleStrategy>;

VISALGORITHM_NAMESPACE_END
