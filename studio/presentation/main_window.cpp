#include <QFileDialog>

#include <lethian/core/core.hpp>

#include "../project/studio_project.hpp"

#include "new_project_dialog.hpp"
#include "ui_main_window.h"
#include "main_window.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	connect(ui->action_New_project, &QAction::triggered, this, &MainWindow::OnActionNewProjectTriggered);
	connect(ui->action_Open_project, &QAction::triggered, this, &MainWindow::OnActionOpenProjectTriggered);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::OnActionNewProjectTriggered()
{
	NewProjectDialog dlg(this);
	dlg.exec();
}

void MainWindow::OnActionOpenProjectTriggered()
{
	const QString projectDir =
		QFileDialog::getOpenFileName(this, tr("Open project"), "C://", tr("Lethian Files (*.lethian)"));

	// TODO: Handle erros
	StudioProject::Get().Load(projectDir.toStdString());
	const auto projectInfo = StudioProject::Get().GetInfo();

	auto &engineInfo = Leth::EngineContext::GetAppInfo();
	engineInfo.majorVersion = projectInfo.versionMajor;
	engineInfo.minorVersion = projectInfo.versionMinor;
	engineInfo.versionPatch = projectInfo.versionPatch;
	engineInfo.name = Leth::String(projectInfo.name.c_str());
}
