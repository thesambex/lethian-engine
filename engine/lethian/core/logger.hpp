#pragma once

#include <memory>
#include <spdlog/spdlog.h>

#include "core_api.hpp"

namespace Leth
{
	class LETH_CORE_API Logger
	{
	public:
		static void Initialize();

		inline static std::shared_ptr<spdlog::logger> &GetCoreLogger()
		{
			return s_CoreLogger;
		}

		inline static std::shared_ptr<spdlog::logger> &GetClientLogger()
		{
			return s_ClientLogger;
		}

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
} // namespace Leth

#define LETH_CORE_TRACE(...) ::Leth::Logger::GetCoreLogger()->trace(__VA_ARGS__)
#define LETH_CORE_INFO(...) ::Leth::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define LETH_CORE_WARN(...) ::Leth::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define LETH_CORE_ERROR(...) ::Leth::Logger::GetCoreLogger()->error(__VA_ARGS__)
#define LETH_CORE_CRITICAL(...) ::Leth::Logger::GetCoreLogger()->critical(__VA_ARGS__)

#define LETH_LOG_TRACE(...) ::Leth::Logger::GetClientLogger()->trace(__VA_ARGS__)
#define LETH_LOG_INFO(...) ::Leth::Logger::GetClientLogger()->info(__VA_ARGS__)
#define LETH_LOG_WARN(...) ::Leth::Logger::GetClientLogger()->warn(__VA_ARGS__)
#define LETH_LOG_ERROR(...) ::Leth::Logger::GetClientLogger()->error(__VA_ARGS__)
#define LETH_LOG_CRITICAL(...) ::Leth::Logger::GetClientLogger()->critical(__VA_ARGS__)
