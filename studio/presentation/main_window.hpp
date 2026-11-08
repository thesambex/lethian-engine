#pragma once

#include <QMainWindow>
#include <QTreeView>
#include <QDir>

QT_BEGIN_NAMESPACE
namespace Ui
{
	class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private slots:
	void OnActionNewProjectTriggered();
	void OnActionOpenProjectTriggered();

	void OnFileTreeClicked(const QModelIndex &index);
	void OnFileDrop(const QString &sourcePath, const QString &targetDirectory);

private:
	void EnsureProject(const QDir &projectRoot);

private:
	Ui::MainWindow *ui = nullptr;

	class QFileSystemModel *m_FileSystemModel = nullptr;

	class FileListWidget *m_FileListWidget = nullptr;
};
