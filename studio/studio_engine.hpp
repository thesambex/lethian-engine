#pragma once

#include <lethian/framework/engine_framework.hpp>

class StudioEngine : public Leth::EngineFramework
{
protected:
	void OnStart() override;
	void OnShutdown() override;
};
