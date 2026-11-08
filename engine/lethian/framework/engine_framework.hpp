#pragma once

#include <memory>

#include "framework_api.hpp"

namespace Leth
{
	class LETH_FRAMEWORK_API EngineFramework
	{
	public:
		virtual ~EngineFramework() = 0;

		bool Create();
		void Run();
		void Stop();

		void Start();
		int Shutdown();

	protected:
		virtual void OnStart() = 0;
		virtual void OnShutdown() = 0;

	private:
		bool m_IsRunning = false;
	};
} // namespace Leth
