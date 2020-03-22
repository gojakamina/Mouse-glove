#include <QtWidgets>
#include "window.h"

int main(int argc, char *argv[])
{
	// Creates an instance of QApplication
	QApplication a(argc, argv);

	// This is our Window class containing our GUI and functionality
	Window window;
	window.show(); // Show main window

	// run the application and return execs() return value/code
	return a.exec();
}
