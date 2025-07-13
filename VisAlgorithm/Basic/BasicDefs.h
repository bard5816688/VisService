#pragma once

#define VISALGORITHM_NAMESPACE_BEGIN                                          \
namespace VisAlgorithm {                                                      \

#define  VISALGORITHM_NAMESPACE_END                                           \
}

#ifndef VISALGORITHM_EXPORTS
#define VisAlgorithmApi __declspec(dllimport)
#else
#define VisAlgorithmApi __declspec(dllexport)
#endif
