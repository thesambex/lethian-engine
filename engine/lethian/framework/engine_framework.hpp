#pragma once

#include <memory>

#include "framework_api.hpp"

namespace Leth
{
	class LETH_FRAMEWORK_API AEngineFramework
	{
	public:
		AEngineFramework();
		virtual ~AEngineFramework() = 0;

		bool Initialize();
		bool Create();
		int Shutdown();

		void DoUpdate();
		void Update();
		void Run();
		void Stop();
		void Resume();
		void Start();

	protected:
		virtual void OnStart() = 0;
		virtual void OnShutdown() = 0;
		virtual void OnUpdate() = 0;

	protected:
		class ADisplay *display = nullptr;

	private:
		bool m_IsRunning = false;
	};
} // namespace Leth
