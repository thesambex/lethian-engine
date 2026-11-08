#include "studio_application.hpp"
#include "presentation/main_window.hpp"

int main(int argc, char *argv[])
{
	StudioApplication app(argc, argv);

	MainWindow w;
	w.showMaximized();

	return QApplication::exec();
}
