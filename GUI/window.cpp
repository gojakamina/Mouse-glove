#include <QtWidgets>
#include "window.h"

// Constructor for main widget
Window::Window(QWidget *parent) :
    QWidget(parent)
{
	// create start button
	button_1 = new QPushButton(tr("Start"));

	// text about instructions
	instTxt = new QTextEdit();
	instTxt->setText("Text on how to use the mouse-glove here. This can be edited in window.cpp");

	// grid layout
	QGridLayout *gridLayout = new QGridLayout();

	gridLayout->addWidget(instTxt,0,0); // placement on row 0, column 0
	gridLayout->addWidget(button_1,1,0); // placement on row 1, column 0

}

/**
	void Window::timerEvent( QTimerEvent *)
{
        This method is for timer events. not implemented yet
}
*/

// Destructor
Window::~Window()
{
	delete button_1;
	delete instTxt;
}
