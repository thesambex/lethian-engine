#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <vector>

#include "../project/studio_project.hpp"

#include "ui_new_project_dialog.h"
#include "new_project_dialog.hpp"

NewProjectDialog::NewProjectDialog(QWidget *parent) : QDialog(parent), ui(new Ui::NewProjectDialog)
{
	ui->setupUi(this);

	connect(ui->pbCreateProject, &QPushButton::clicked, this, &NewProjectDialog::OnCreateProjectClicked);
}

NewProjectDialog::~NewProjectDialog()
{
	delete ui;
}

void NewProjectDialog::OnCreateProjectClicked()
{
	if (ui->leProjectName->text().isEmpty())
	{
		QMessageBox::warning(this, tr("Project creation"), tr("Project name is empty"));
		return;
	}

	if (ui->leMajor->text().isEmpty() || ui->leMinor->text().isEmpty() || ui->lePatch->text().isEmpty())
	{
		QMessageBox::warning(this, tr("Project creation"), tr("Version is empty"));
		return;
	}

	if (!ui->cbxWindows->isChecked() && !ui->cbxAndroid->isChecked())
	{
		QMessageBox::warning(this, tr("Project creation"), tr("Provide a platform"));
		return;
	}

	const QString fileName =
		QFileDialog::getSaveFileName(this, tr("Save project"), "C://", tr("Lethian Files (*.lethian)"));

	if (fileName.isEmpty())
	{
		return;
	}

	QFile file(fileName);
	if (file.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		QTextStream outputStream(&file);

		std::vector<std::string> targetPlatforms;

		if (ui->cbxWindows->isChecked())
		{
			targetPlatforms.push_back("Windows");
		}

		if (ui->cbxAndroid->isChecked())
		{
			targetPlatforms.push_back("Android");
		}

		StudioProject::Info projectInfo{.versionMajor = ui->leMajor->text().toInt(),
										.versionMinor = ui->leMinor->text().toInt(),
										.versionPatch = ui->lePatch->text().toInt(),
										.name = ui->leProjectName->text().toStdString(),
										.targetPlatforms = targetPlatforms};

		const QString data = QString::fromStdString(StudioProject::Get().Create(projectInfo));
		if (data.isEmpty())
		{
			QMessageBox::warning(this, tr("Project creation"), tr("Project data is empty"));
			return;
		}

		outputStream << data;

		file.close();
	}

	this->close();
}
