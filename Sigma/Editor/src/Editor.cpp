#include <QApplication>
#include <QWidget>

int main(int argc, char** argv)
{
	QApplication application(argc, argv);
	QWidget main_window;
	main_window.show();

	return application.exec();
}