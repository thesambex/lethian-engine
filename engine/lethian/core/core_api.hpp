#pragma once

#ifdef ENABLE_DLL
#ifdef _WIN32
#ifdef LETH_CORE_EXPORTS
#define LETH_CORE_API __declspec(dllexport)
#else
#define LETH_CORE_API __declspec(dllimport)
#endif
#else
#define LETH_CORE_API __attribute__((visibility("default")))
#endif
#else
#define LETH_CORE_API
#endif
