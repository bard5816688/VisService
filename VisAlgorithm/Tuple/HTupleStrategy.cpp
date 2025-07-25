#include "../Tuple/TupleInternal.h"
#include "../Basic/BasicReturnInternal.h"

#ifdef USE_HALCON

VISALGORITHM_NAMESPACE_BEGIN

class HTupleStrategy::Impl
{
public:

	HalconCpp::HTuple& GetHobj()
	{
		return hTuple_;
	}

	static HTupleStrategy FromHTuple(const HalconCpp::HTuple& hTuple)
	{
		HTupleStrategy tuple;
		tuple.GetImpl()->GetHobj() = hTuple;
		return tuple;
	}

	static Result<HTupleStrategy> ResultFromHTuple(const Result<HalconCpp::HTuple>& res)
	{
		return res.transform(HTupleStrategy::Impl::FromHTuple);
	}

private:
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
	: impl_(new Impl)
{
	std::visit([=](const auto& value) {
		using T = std::decay_t<decltype(value)>;
		if constexpr (std::is_same_v<T, std::monostate>)
		{
		}
		else if constexpr (std::is_same_v<T, std::string>)
		{
			impl_->GetHobj() = HalconCpp::HTuple(value.c_str());
		}
		else
		{
			impl_->GetHobj() = HalconCpp::HTuple(value);
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

HTupleStrategy& HTupleStrategy::Append(const HTupleStrategy& tuple)
{

	impl_->GetHobj() = impl_->GetHobj().Append(tuple.impl_->GetHobj());
	return *this;
}

Result<TupleElementType> HTupleStrategy::Type(size_t idx)
{
	if (idx >= impl_->GetHobj().Length())
	{
		return VISALGORITHM__RETURN_UNEXPECTE("Result<TupleElement> Impl::At(size_t idx)", "HTupleStrategy index out of bounds", ErrorCode::StdExcepetion);
	}
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(type, impl_->GetHobj()[idx].Type());
	switch (type.value())
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

Result<TupleElement> HTupleStrategy::At(size_t idx) const
{
	if (idx >= impl_->GetHobj().Length())
	{
		return VISALGORITHM__RETURN_UNEXPECTE("Result<TupleElement> Impl::At(size_t idx)", "HTupleStrategy index out of bounds", ErrorCode::StdExcepetion);
	}
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(elementType, impl_->GetHobj()[idx].Type());
	switch (elementType.value())
	{
	case HalconCpp::eElementTypeLong:
	{
		VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(i, impl_->GetHobj()[idx].I());
		return i;
	}
	case HalconCpp::eElementTypeDouble:
	{
		VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(d, impl_->GetHobj()[idx].D());
		return d;
	}
	case HalconCpp::eElementTypeString:
	{
		VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(s, impl_->GetHobj()[idx].S().Text());
		return s;
	}
	case HalconCpp::eElementTypeHandle:
	case HalconCpp::eElementTypeMixed:
	case HalconCpp::eElementTypeUndef:
	default:
		return std::monostate();
	}
}

Result<int64_t> HTupleStrategy::Length() const
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(length, impl_->GetHobj().Length());
	return length;
}

Result<HTupleStrategy> HTupleStrategy::TupleSelect(const HTupleStrategy& index) const
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(select, impl_->GetHobj().TupleSelect(index.impl_->GetHobj()));
	return HTupleStrategy::Impl::ResultFromHTuple(select);
}

Result<HTupleStrategy> HTupleStrategy::TupleConcat(const HTupleStrategy& t2) const
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(concat, impl_->GetHobj().TupleConcat(t2.impl_->GetHobj()));
	return HTupleStrategy::Impl::ResultFromHTuple(concat);
}

Result<HTupleStrategy> HTupleStrategy::TupleGenSequence(const HTupleStrategy& start, const HTupleStrategy& end, const HTupleStrategy& step) const
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(genseq, impl_->GetHobj().TupleGenSequence(start.impl_->GetHobj(), end.impl_->GetHobj(), step.impl_->GetHobj()));
	return HTupleStrategy::Impl::ResultFromHTuple(genseq);
}

Result<HTupleStrategy> HTupleStrategy::TupleGenConst(const HTupleStrategy& length, const HTupleStrategy& Const) const
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(gencon, impl_->GetHobj().TupleGenConst(length.impl_->GetHobj(),Const.impl_->GetHobj()));
	return HTupleStrategy::Impl::ResultFromHTuple(gencon);
}

Result<HTupleStrategy> HTupleStrategy::TupleAdd(const HTupleStrategy& s2) const
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(add, impl_->GetHobj().TupleAdd(s2.impl_->GetHobj()));
	return HTupleStrategy::Impl::ResultFromHTuple(add);
}

Result<HTupleStrategy> HTupleStrategy::TupleSub(const HTupleStrategy& d2) const
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(sub, impl_->GetHobj().TupleSub(d2.impl_->GetHobj()));
	return HTupleStrategy::Impl::ResultFromHTuple(sub);
}

Result<HTupleStrategy> HTupleStrategy::TupleMult(const HTupleStrategy& p2) const
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(mult, impl_->GetHobj().TupleMult(p2.impl_->GetHobj()));
	return HTupleStrategy::Impl::ResultFromHTuple(mult);
}

Result<HTupleStrategy> HTupleStrategy::TupleInsert(const HTupleStrategy& index, HTupleStrategy& invert) const
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(insert, impl_->GetHobj().TupleInsert(index.impl_->GetHobj(), invert.impl_->GetHobj()));
	return HTupleStrategy::Impl::ResultFromHTuple(insert);
}

Result<HTupleStrategy> HTupleStrategy::TupleRemove(const HTupleStrategy& index) const
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(remove, impl_->GetHobj().TupleRemove(index.impl_->GetHobj()));
	return HTupleStrategy::Impl::ResultFromHTuple(remove);
}

Result<HTupleStrategy> HTupleStrategy::TupleReplace(const HTupleStrategy& index, const HTupleStrategy& replacetuple) const
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(replace, impl_->GetHobj().TupleReplace(index.impl_->GetHobj(), replacetuple.impl_->GetHobj()));
	return HTupleStrategy::Impl::ResultFromHTuple(replace);
}

Result<HTupleStrategy> HTupleStrategy::TupleDiv(const HTupleStrategy& q2) const
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(div, impl_->GetHobj().TupleDiv(q2.impl_->GetHobj()));
	return HTupleStrategy::Impl::ResultFromHTuple(div);
}

Result<HTupleStrategy> HTupleStrategy::TuplePow(const HTupleStrategy& t2) const
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(pow, impl_->GetHobj().TuplePow(t2.impl_->GetHobj()));
	return HTupleStrategy::Impl::ResultFromHTuple(pow);
}

Result<HTupleStrategy> HTupleStrategy::TupleAbs() const
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(abs, impl_->GetHobj().TupleAbs());
	return HTupleStrategy::Impl::ResultFromHTuple(abs);
}

Result<HTupleStrategy> HTupleStrategy::TupleSqrt() const
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(sqrt, impl_->GetHobj().TupleSqrt());
	return HTupleStrategy::Impl::ResultFromHTuple(sqrt);
}

Result<HTupleStrategy> HTupleStrategy::TupleRound() const
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(round, impl_->GetHobj().TupleRound());
	return HTupleStrategy::Impl::ResultFromHTuple(round);
}

Result<HTupleStrategy> HTupleStrategy::TupleMean() const
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(mean, impl_->GetHobj().TupleMean());
	return HTupleStrategy::Impl::ResultFromHTuple(mean);
}

Result<HTupleStrategy> HTupleStrategy::TupleSum() const
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(sum, impl_->GetHobj().TupleSum());
	return HTupleStrategy::Impl::ResultFromHTuple(sum);
}

Result<HTupleStrategy> HTupleStrategy::TupleMax() const
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(Max, impl_->GetHobj().TupleMax());
	return HTupleStrategy::Impl::ResultFromHTuple(Max);
}

Result<HTupleStrategy> HTupleStrategy::TupleMin() const
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(Min, impl_->GetHobj().TupleMin());
	return HTupleStrategy::Impl::ResultFromHTuple(Min);
}

Result<HTupleStrategy> HTupleStrategy::TupleGreater(const HTupleStrategy& t2) const
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(greater, impl_->GetHobj().TupleGreater(t2.impl_->GetHobj()));
	return HTupleStrategy::Impl::ResultFromHTuple(greater);
}

Result<HTupleStrategy> HTupleStrategy::TupleLess(const HTupleStrategy& t2) const
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(less, impl_->GetHobj().TupleLess(t2.impl_->GetHobj()));
	return HTupleStrategy::Impl::ResultFromHTuple(less);
}

Result<HTupleStrategy> HTupleStrategy::TupleEqual(const HTupleStrategy& t2) const
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(equal, impl_->GetHobj().TupleEqual(t2.impl_->GetHobj()));
	return HTupleStrategy::Impl::ResultFromHTuple(equal);
}

Result<HTupleStrategy> HTupleStrategy::TupleAnd(const HTupleStrategy& t2) const
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(and1, impl_->GetHobj().TupleAnd(t2.impl_->GetHobj()));
	return HTupleStrategy::Impl::ResultFromHTuple(and1);
}

Result<HTupleStrategy> HTupleStrategy::TupleOr(const HTupleStrategy& t2) const
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(or1, impl_->GetHobj().TupleOr(t2.impl_->GetHobj()));
	return HTupleStrategy::Impl::ResultFromHTuple(or1);
}

Result<HTupleStrategy> HTupleStrategy::TupleNot() const
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(not1, impl_->GetHobj().TupleNot());
	return HTupleStrategy::Impl::ResultFromHTuple(not1);
}

Result<HTupleStrategy> HTupleStrategy::TupleString(const HTupleStrategy& format) const
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(str, impl_->GetHobj().TupleString(format.impl_->GetHobj()));
	return HTupleStrategy::Impl::ResultFromHTuple(str);
}

Result<HTupleStrategy> HTupleStrategy::TupleNumber() const
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(number, impl_->GetHobj().TupleNumber());
	return HTupleStrategy::Impl::ResultFromHTuple(number);
}

Result<HTupleStrategy> HTupleStrategy::TupleSplit(const HTupleStrategy& separator) const
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(split, impl_->GetHobj().TupleSplit(separator.impl_->GetHobj()));
	return HTupleStrategy::Impl::ResultFromHTuple(split);
}

Result<HTupleStrategy> HTupleStrategy::TupleJoin(const HTupleStrategy& separators) const
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(join, impl_->GetHobj().TupleJoin(separators.impl_->GetHobj()));
	return HTupleStrategy::Impl::ResultFromHTuple(join);
}

Result<HTupleStrategy> HTupleStrategy::TupleInt() const
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(int1, impl_->GetHobj().TupleInt());
	return HTupleStrategy::Impl::ResultFromHTuple(int1);
}

Result<HTupleStrategy> HTupleStrategy::TupleReal() const
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(real, impl_->GetHobj().TupleReal());
	return HTupleStrategy::Impl::ResultFromHTuple(real);
}

Result<HTupleStrategy> HTupleStrategy::ReadTuple(const HTupleStrategy& filename) const
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(realt, impl_->GetHobj().ReadTuple(filename.impl_->GetHobj()));
	return HTupleStrategy::Impl::ResultFromHTuple(realt);
}

ResultVoid HTupleStrategy::WriteTuple(const HTupleStrategy& filename) const
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(writet, impl_->GetHobj().WriteTuple(filename.impl_->GetHobj()));
	return writet;
}

Result<HTupleStrategy> HTupleStrategy::TupleUnion(const HTupleStrategy& set2) const
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(union1, impl_->GetHobj().TupleUnion(set2.impl_->GetHobj()));
	return HTupleStrategy::Impl::ResultFromHTuple(union1);
}

Result<HTupleStrategy> HTupleStrategy::TupleIntersection(const HTupleStrategy& set2) const
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(intersection, impl_->GetHobj().TupleIntersection(set2.impl_->GetHobj()));
	return HTupleStrategy::Impl::ResultFromHTuple(intersection);
}

Result<HTupleStrategy> HTupleStrategy::TupleDifference(const HTupleStrategy& set2) const
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(difference, impl_->GetHobj().TupleDifference(set2.impl_->GetHobj()));
	return HTupleStrategy::Impl::ResultFromHTuple(difference);
}

Result<HTupleStrategy> HTupleStrategy::TupleSort() const
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(sort, impl_->GetHobj().TupleSort());
	return HTupleStrategy::Impl::ResultFromHTuple(sort);
}

Result<HTupleStrategy> HTupleStrategy::TupleSortIndex() const
{
	VISALGORITHM_TRY_OR_RETURN_UNEXPECTED(sortindex, impl_->GetHobj().TupleSortIndex());
	return HTupleStrategy::Impl::ResultFromHTuple(sortindex);
}

HTupleStrategy::Impl* HTupleStrategy::GetImpl() const
{
	return impl_;
}

HalconCpp::HTuple TupleInternalUtils::GetHTuple(const Tuple& tuple)
{
	return tuple.GetImpl()->GetHobj();
}

HalconCpp::HTuple* TupleInternalUtils::GetHTuplePtr(Tuple* tuple)
{
	return &(tuple->GetImpl()->GetHobj());
}

Tuple TupleInternalUtils::FromHTuple(const HalconCpp::HTuple& hTuple)
{
	Tuple tuple;
	tuple.GetImpl()->GetHobj() = hTuple;
	return tuple;
}

Result<Tuple> TupleInternalUtils::ResultFromHTuple(const Result<HalconCpp::HTuple>& res)
{
	return res.transform(TupleInternalUtils::FromHTuple);
}

VISALGORITHM_NAMESPACE_END

#endif // USE_HALCON