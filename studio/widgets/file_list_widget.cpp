#include <QDragEnterEvent>
#include <QDragMoveEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QFileInfo>
#include <QFileIconProvider>
#include <QDir>

#include "file_list_widget.hpp"

FileListWidget::FileListWidget(QWidget *parent) : QListWidget(parent)
{
	setViewMode(QListView::IconMode);
	setFlow(QListView::LeftToRight);
	setWrapping(true);
	setResizeMode(QListView::Adjust);
	setMovement(QListView::Static);

	setIconSize(QSize(48, 48));
	setGridSize(QSize(90, 80));

	setDragDropMode(QAbstractItemView::DropOnly);
	setAcceptDrops(true);
	viewport()->setAcceptDrops(true);
}

void FileListWidget::SetDirectory(const QString &directory)
{
	m_CurrentDirectory = directory;
	Refresh();
}

void FileListWidget::Refresh()
{
	clear();

	if (m_CurrentDirectory.isEmpty())
		return;

	const QDir dir(m_CurrentDirectory);
	const QFileInfoList entries = dir.entryInfoList(QDir::Files | QDir::NoDotAndDotDot, QDir::Name | QDir::IgnoreCase);

	QFileIconProvider iconProvider;
	for (const QFileInfo &info : entries)
	{
		QListWidgetItem *item = new QListWidgetItem(iconProvider.icon(info), info.fileName(), this);
		item->setData(Qt::UserRole, info.absoluteFilePath());
		item->setToolTip(info.absoluteFilePath());
	}
}

void FileListWidget::dragEnterEvent(QDragEnterEvent *event)
{
	if (!m_CurrentDirectory.isEmpty() && event->mimeData()->hasUrls())
		event->acceptProposedAction();
	else
		event->ignore();
}

void FileListWidget::dragMoveEvent(QDragMoveEvent *event)
{
	if (!m_CurrentDirectory.isEmpty() && event->mimeData()->hasUrls())
		event->acceptProposedAction();
	else
		event->ignore();
}

void FileListWidget::dropEvent(QDropEvent *event)
{
	const QMimeData *mimeData = event->mimeData();

	if (m_CurrentDirectory.isEmpty() || !mimeData->hasUrls())
	{
		event->ignore();
		return;
	}

	for (const QUrl &url : mimeData->urls())
	{
		const QString localPath = url.toLocalFile();
		if (localPath.isEmpty() || !QFileInfo(localPath).isFile())
			continue;

		emit FileDropped(localPath, m_CurrentDirectory);
	}

	event->acceptProposedAction();
}
