#pragma once

#include <lethian/framework/engine_framework.hpp>

class StudioEngine : public Leth::CEngineFramework
{
protected:
	void OnStart() override;
	void OnShutdown() override;
};
