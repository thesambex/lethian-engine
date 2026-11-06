#pragma once

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui
{
	class NewProjectDialog;
}
QT_END_NAMESPACE

class NewProjectDialog : public QDialog
{
	Q_OBJECT

public:
	explicit NewProjectDialog(QWidget *parent = nullptr);
	~NewProjectDialog();

private slots:
	void OnCreateProjectClicked();

private:
	Ui::NewProjectDialog *ui = nullptr;
};
