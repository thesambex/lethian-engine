#pragma once

#include <QApplication>
#include <QSharedPointer>

#include "studio_engine.hpp"

class StudioApplication : public QApplication
{
public:
	explicit StudioApplication(int argc, char *argv[]);
	~StudioApplication();

	inline StudioEngine *GetEngine()
	{
		return m_Engine.get();
	}

private:
	QSharedPointer<StudioEngine> m_Engine;
};
