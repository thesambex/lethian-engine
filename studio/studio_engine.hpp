#pragma once

#include <lethian/framework/engine_framework.hpp>

class StudioEngine : public Leth::AEngineFramework
{
protected:
	void OnStart() override;
	void OnShutdown() override;
	void OnUpdate() override;
};
