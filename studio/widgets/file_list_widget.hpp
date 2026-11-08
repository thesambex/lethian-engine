#pragma once

#include <QListWidget>
#include <QString>

class FileListWidget : public QListWidget
{
	Q_OBJECT

public:
	FileListWidget(QWidget *parent = nullptr);

	void SetDirectory(const QString &directory);
	void Refresh();

	const QString &GetDirectory() const { return m_CurrentDirectory; }

signals:
	void FileDropped(const QString &sourcePath, const QString &targetDirectory);

protected:
	void dragEnterEvent(class QDragEnterEvent *event) override;
	void dragMoveEvent(class QDragMoveEvent *event) override;
	void dropEvent(class QDropEvent *event) override;

private:
	QString m_CurrentDirectory;
};
