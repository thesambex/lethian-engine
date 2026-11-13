#include <lethian/core/logger.hpp>
#include <lethian/platform/display/windows/windows_display.hpp>

#include "engine_framework.hpp"

namespace Leth
{
	AEngineFramework::AEngineFramework()
	{
	}

	AEngineFramework::~AEngineFramework()
	{
	}

	bool AEngineFramework::Initialize()
	{
		Logger::Initialize();

		return Create();
	}

	bool AEngineFramework::Create()
	{
		Start();

		return true;
	}

	void AEngineFramework::Update()
	{
		if (m_IsRunning)
			DoUpdate();
	}

	void AEngineFramework::DoUpdate()
	{
		OnUpdate();
	}

	void AEngineFramework::Run()
	{
	}

	void AEngineFramework::Stop()
	{
		m_IsRunning = false;
	}

	void AEngineFramework::Start()
	{
		LETH_CORE_INFO("Engine start initialization.");

		OnStart();

		LETH_CORE_INFO("Engine finished initialization.");

		while (display->PoolEvents())
		{
			DoUpdate();
		}
	}

	void AEngineFramework::Resume()
	{
		m_IsRunning = true;
	}

	int AEngineFramework::Shutdown()
	{
		LETH_CORE_INFO("Engine start shut down.");

		OnShutdown();

		LETH_CORE_INFO("Engine start end shut down.");

#ifdef WIN32
		if (!display)
			return -1;

		return dynamic_cast<CWinDisplay *>(display)->GetExitCode();
#else
		return 0;
#endif // WIN32
	}

} // namespace Leth
