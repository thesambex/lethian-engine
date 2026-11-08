#include <lethian/core/logger.hpp>
#include "studio_application.hpp"

StudioApplication::StudioApplication(int argc, char *argv[])
	: QApplication(argc, argv), m_Engine(QSharedPointer<StudioEngine>::create())
{
	Leth::Logger::Initialize();
}

StudioApplication::~StudioApplication()
{
	m_Engine->Shutdown();
}
