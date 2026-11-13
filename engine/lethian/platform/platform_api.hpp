#pragma once

#ifdef ENABLE_DLL
#ifdef _WIN32
#ifdef LETH_PLATFORM_EXPORTS
#define LETH_PLATFORM_API __declspec(dllexport)
#else
#define LETH_PLATFORM_API __declspec(dllimport)
#endif
#else
#define LETH_PLATFORM_API __attribute__((visibility("default")))
#endif
#else
#define LETH_PLATFORM_API
#endif
