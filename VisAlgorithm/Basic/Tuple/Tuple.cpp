#include "TupleInternal.h"
#include "HalconCpp.h"

VISALGORITHM_NAMESPACE_BEGIN

class TupleImpl
{
public:

    HalconCpp::HTuple GetHTuple()
    {
        return hTuple_;
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

private:
    HalconCpp::HTuple hTuple_;
    //底层也可以替换或同时使用VisTuple(自定义/其他Dll提供的Tuple类型)
};

Tuple::Tuple()
{
    tupleImpl_ = std::make_shared<TupleImpl>();
}

Tuple::Tuple(const TupleElement& value)
{

}

Tuple::~Tuple()
{
}

Tuple& Tuple::Append(const Tuple& tuple)
{

}

TupleElementType Tuple::Type(size_t idx)
{
	HalconCpp::HTupleElementType elementType = tupleImpl_->GetHTuple()[idx].Type();
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

}

TupleImplPtr Tuple::ImplPtr() const
{
    return TupleImplPtr();
}

HalconCpp::HTuple GetHTuple(const Tuple& tuple)
{
    return tuple.ImplPtr()->GetHTuple();
}

Tuple FromHTuple(const HalconCpp::HTuple& hTuple)
{

}

VISALGORITHM_NAMESPACE_END