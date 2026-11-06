#include <QApplication>

#include "presentation/main_window.hpp"

int main(int argc, char* argv[])
{
	QApplication app(argc, argv);

	MainWindow w;
	w.showMaximized();

	return QApplication::exec();
}
