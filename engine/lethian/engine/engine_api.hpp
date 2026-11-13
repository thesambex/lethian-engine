#pragma once

#ifdef ENABLE_DLL
#ifdef _WIN32
#ifdef LETH_ENGINE_EXPORTS
#define LETH_ENGINE_API __declspec(dllexport)
#else
#define LETH_ENGINE_API __declspec(dllimport)
#endif
#else
#define LETH_ENGINE_API __attribute__((visibility("default")))
#endif
#else
#define LETH_ENGINE_API
#endif
