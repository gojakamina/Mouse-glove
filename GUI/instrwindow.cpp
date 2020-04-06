#include <QtWidgets>
#include "instrwindow.h"

// Constructor for main widget
InstrWindow::InstrWindow() 
{

   createWindow();

}


void InstrWindow::createWindow() {
   QGridLayout *instrLayout = new QGridLayout;
   
   instrTxt = new QLabel;
   instrTxt->setText(tr("Instructions on how to use the mouse-glove."));
   okButton = new QPushButton(tr("Ok")); 

   instrLayout->addWidget(instrTxt, 0, 0); // placement on row 0, column 0
   instrLayout->addWidget(okButton, 1, 0); // placement on row 1, column 0
   connect(okButton, &QPushButton::clicked, this, &InstrWindow::close);

   setLayout(instrLayout);
   setWindowTitle(tr("Instructions to Mouse-glove usage"));
}


InstrWindow::~InstrWindow() {
	delete instrTxt;
	delete okButton;
}
