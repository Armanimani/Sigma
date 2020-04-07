#include <QApplication>

#include "Editor/Editor.hpp"

int main(int argc, char** argv)
{
	QApplication application(argc, argv);
	
	sigma::editor::Editor main_window{};
	main_window.show();
	
	const auto return_code = application.exec();
	return return_code;
}