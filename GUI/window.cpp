
#include <QtWidgets>
#include "window.h"

// Constructor for main widget
Window::Window() 
{

   createTextBox();
   createButtons();
   
   QGridLayout *mainLayout = new QGridLayout;

   mainLayout->addWidget(instrTxt, 0, 0); // placement on row 0, column 0
   mainLayout->addWidget(buttons, 1, 0); // placement on row 1, column 0

   setLayout(mainLayout);
   setWindowTitle(tr("Mouse-glove"));

}

	 
void Window::createTextBox() {
   instrTxt = new QLabel();
   instrTxt->setText(tr("Introduction text."));
   
}


void Window::createButtons() {
   buttons  = new QGroupBox();
   QHBoxLayout *layout = new QHBoxLayout;

   instrButton = new QPushButton(tr("Instructions"));
   startButton = new QPushButton(tr("Start"));

   layout->addWidget(instrButton);
   layout->addWidget(startButton);
   
   connect(instrButton, &QPushButton::clicked, this, &Window::openWindow);
   // connect(startButton, &QPushButton::clicked, this, &Window::startExec);
   
   buttons->setLayout(layout);

}


void Window::openWindow() {
   instrWindow.show();
}


void Window::startExec() {
   // write code here to link it to the main of the project.
   // uncomment line 41 once you're done.
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
	delete instrTxt;
	delete instrButton;
	delete startButton;
	delete buttons;
}
