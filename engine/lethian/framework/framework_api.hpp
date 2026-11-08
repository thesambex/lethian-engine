#pragma once

#ifdef ENABLE_DLL
#ifdef _WIN32
#ifdef LETH_FRAMEWORK_EXPORTS
#define LETH_FRAMEWORK_API __declspec(dllexport)
#else
#define LETH_FRAMEWORK_API __declspec(dllimport)
#endif
#else
#define LETH_FRAMEWORK_API __attribute__((visibility("default")))
#endif
#else
#define LETH_FRAMEWORK_API
#endif
