#include <lethian/core/logger.hpp>

#include "engine_framework.hpp"

namespace Leth
{
	EngineFramework::~EngineFramework()
	{
	}

	bool EngineFramework::Create()
	{
		Logger::Initialize();

		Start();

		return true;
	}

	void EngineFramework::Run()
	{
	}

	void EngineFramework::Stop()
	{
	}

	void EngineFramework::Start()
	{
		LETH_CORE_INFO("Engine start initialization.");

		OnStart();

		LETH_CORE_INFO("Engine finished initialization.");
	}

	int EngineFramework::Shutdown()
	{
		LETH_CORE_INFO("Engine start shut down.");

		OnShutdown();

		LETH_CORE_INFO("Engine start end shut down.");

		return 0;
	}

} // namespace Leth
