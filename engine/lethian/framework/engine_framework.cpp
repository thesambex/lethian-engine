#include <lethian/core/logger.hpp>

#include "engine_framework.hpp"

namespace Leth
{
	CEngineFramework::~CEngineFramework()
	{
	}

	bool CEngineFramework::Initialize()
	{
		Logger::Initialize();

		return Create();
	}

	bool CEngineFramework::Create()
	{
		Start();

		return true;
	}

	void CEngineFramework::Run()
	{
	}

	void CEngineFramework::Stop()
	{
	}

	void CEngineFramework::Start()
	{
		LETH_CORE_INFO("Engine start initialization.");

		OnStart();

		LETH_CORE_INFO("Engine finished initialization.");
	}

	int CEngineFramework::Shutdown()
	{
		LETH_CORE_INFO("Engine start shut down.");

		OnShutdown();

		LETH_CORE_INFO("Engine start end shut down.");

		return 0;
	}

} // namespace Leth
