#include <unistd.h>
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

   QPalette palette = this->palette();
   palette.setColor(QPalette::Window, QColor(255,250,250,255));
   this->setPalette(palette);

}


void Window::createTextBox() {
   
   instrTxt = new QLabel();
   instrTxt->setText(
   tr(" \n \
Welcome to the Mouse-glove application! \n \n \
We are three creators who have implemented a glove \n \
that willl act as a mouse cursor. If you need instructions \n \
on how to use it, please press the instruction button. \n \
If you want to start trying the mouse-glove, press start. \n \n \
Enjoy!"));
   instrTxt->setAlignment(Qt::AlignCenter);

}


void Window::createButtons() {
   buttons  = new QGroupBox();
   QHBoxLayout *layout = new QHBoxLayout;

   instrButton = new QPushButton(tr("Instructions"));
   startButton = new QPushButton(tr("Start"));

   layout->addWidget(instrButton);
   layout->addWidget(startButton);


   QPalette pal1 = startButton->palette();
   pal1.setColor(QPalette::Button, QColor(255,250,250,255));
   startButton->setAutoFillBackground(true);
   startButton->setPalette(pal1);
   startButton->update();


   QPalette pal2 = instrButton->palette();
   pal2.setColor(QPalette::Button, QColor(255,250,250,255));
   instrButton->setAutoFillBackground(true);
   instrButton->setPalette(pal2);
   instrButton->update();


   connect(instrButton, &QPushButton::clicked, this, &Window::openWindow);
   // connect(startButton, &QPushButton::clicked, this, &Window::startExec);
 
   buttons->setLayout(layout);

}


void Window::openWindow() {
   instrWindow.show();
}


void Window::startExec() {
   // execl("/address/main", "main", NULL);
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
