#pragma once

#include <memory>

#include "framework_api.hpp"

namespace Leth
{
	class LETH_FRAMEWORK_API CEngineFramework
	{
	public:
		virtual ~CEngineFramework() = 0;

		bool Initialize();
		bool Create();
		int Shutdown();

		void Run();
		void Stop();
		void Start();

	protected:
		virtual void OnStart() = 0;
		virtual void OnShutdown() = 0;

	private:
		bool m_IsRunning = false;
	};
} // namespace Leth
