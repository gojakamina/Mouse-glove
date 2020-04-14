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
   instrTxt->setText(tr("Maybe a picture could be inserted here as well as a textual explanation?"));
   okButton = new QPushButton(tr("Ok")); 
   
   QPalette p = okButton->palette();
   p.setColor(QPalette::Button, QColor(255,250,250,255));
   okButton->setAutoFillBackground(true);
   okButton->setPalette(p);
   okButton->update();

   instrLayout->addWidget(instrTxt, 0, 0); // placement on row 0, column 0
   instrLayout->addWidget(okButton, 1, 0); // placement on row 1, column 0
   connect(okButton, &QPushButton::clicked, this, &InstrWindow::close);
   
   QPalette pal = this->palette();
   pal.setColor(QPalette::Window, QColor(255,250,250,255));
   this->setPalette(pal);

   setLayout(instrLayout);
   setWindowTitle(tr("Instructions to Mouse-glove usage"));
}


InstrWindow::~InstrWindow() {
	delete instrTxt;
	delete okButton;
}
