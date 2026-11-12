#include <QFileDialog>
#include <QMessageBox>
#include <QTreeView>
#include <QFileSystemModel>
#include <QFileInfo>
#include <QFile>

#include <lethian/core/core.hpp>
#include <lethian/engine/resources/asset.hpp>

#include "../widgets/file_list_widget.hpp"
#include "../project/studio_project.hpp"
#include "../engine/asset_manager.hpp"
#include "../studio_application.hpp"

#include "new_project_dialog.hpp"
#include "ui_main_window.h"
#include "main_window.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);

	m_FileSystemModel = new QFileSystemModel();

	m_FileListWidget = new FileListWidget();
	ui->hlContentBrowser->addWidget(m_FileListWidget);

	connect(ui->action_New_project, &QAction::triggered, this, &MainWindow::OnActionNewProjectTriggered);
	connect(ui->action_Open_project, &QAction::triggered, this, &MainWindow::OnActionOpenProjectTriggered);

	connect(ui->tvContentBrowserFileTree, &QTreeView::clicked, this, &MainWindow::OnFileTreeClicked);
	connect(m_FileListWidget, &FileListWidget::FileDropped, this, &MainWindow::OnFileDrop);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::OnActionNewProjectTriggered()
{
	NewProjectDialog dlg(this);
	dlg.exec();

	// TODO: Auto load project
}

void MainWindow::OnFileTreeClicked(const QModelIndex &index)
{
	const QFileInfo info = m_FileSystemModel->fileInfo(index);
	if (m_FileSystemModel->isDir(index))
	{
		ui->tvContentBrowserFileTree->isExpanded(index) ? ui->tvContentBrowserFileTree->collapse(index)
														: ui->tvContentBrowserFileTree->expand(index);

		m_FileListWidget->SetDirectory(info.absoluteFilePath());
	}
	else
	{
		m_FileListWidget->SetDirectory(info.absolutePath());
	}
}

void MainWindow::OnFileDrop(const QString &sourcePath, const QString &targetDirectory)
{
	const QFileInfo sourceInfo(sourcePath);
	const QString targetPath = QDir(targetDirectory).filePath(sourceInfo.fileName());

	if (QFileInfo::exists(targetPath))
		return;

	if (const int result = AssetManager::FileToAsset(sourcePath, targetPath); result != 0)
	{
		switch (result)
		{
		case -1:
			QMessageBox::warning(this, tr("Asset manager"), tr("Failed to create asset"));
			break;

		case 2:
			QMessageBox::warning(this, tr("Asset manager"), tr("Failed to open file"));
			break;

		case 3:
			QMessageBox::warning(this, tr("Asset manager"), tr("File is empty"));
			break;

		case 1:
			QMessageBox::warning(this, tr("Asset manager"), tr("File not supported"));
			break;

		default:
			break;
		}

		return;
	}

	m_FileListWidget->Refresh();
}

void MainWindow::OnActionOpenProjectTriggered()
{
	const QString projectDir =
		QFileDialog::getOpenFileName(this, tr("Open project"), "C://", tr("Lethian Files (*.lethian)"));

	// TODO: Handle erros
	StudioProject::Get().Load(projectDir.toStdString());

	// Load project into engine context
	const auto projectInfo = StudioProject::Get().GetInfo();

	auto &engineInfo = Leth::EngineContext::GetAppInfo();
	engineInfo.majorVersion = projectInfo.versionMajor;
	engineInfo.minorVersion = projectInfo.versionMinor;
	engineInfo.versionPatch = projectInfo.versionPatch;
	engineInfo.name = Leth::String(projectInfo.name.c_str());

	// Ensure project structure
	EnsureProject(StudioProject::Get().GetProjectRoot());
}

void MainWindow::EnsureProject(const QDir &projectRoot)
{
	// Create project directories
	projectRoot.mkdir("assets");
	projectRoot.mkdir("shaders");

	// Load into filetree
	const QString rootPath = projectRoot.absolutePath();

	m_FileSystemModel->setRootPath(rootPath);
	m_FileSystemModel->setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);

	ui->tvContentBrowserFileTree->setModel(m_FileSystemModel);
	ui->tvContentBrowserFileTree->setRootIndex(m_FileSystemModel->index(rootPath));

	m_FileListWidget->SetDirectory(rootPath);

	StudioApplication *app = dynamic_cast<StudioApplication *>(qApp);
	app->GetEngine()->Create();
}
