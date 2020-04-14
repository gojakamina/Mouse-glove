#include <QtWidgets>
#include "instrwindow.h"

// Constructor for main widget
InstrWindow::InstrWindow() 
{

   createWindow();

}


void InstrWindow::createWindow() {
   QGridLayout *instrLayout = new QGridLayout;

   // intruction picture
   instrPic = new QLabel;
   QPixmap pixmap("Mouse-glove.png");
   instrPic->setPixmap(pixmap);
   instrPic->setMask(pixmap.mask());
   instrPic->setAlignment(Qt::AlignCenter);

   // instruction text
   instrTxt = new QLabel;
   instrTxt->setText(
   tr(" \n The picture above shows the glove you are wearing. It consists of three electrodes on your index finger and one electrode  \n"
   " on your thumb. On the back of your hand, you can see the main board we have created and in your palm there is a vibrator. \n \n"
   "To move the mouse cursor, simply use the movement of your hand. Make sure to keep your hand as if you were to hold a \n "
   "stick that is pointing upwards. In other words, the main board should be parallel to any wall in the room. \n \n"
   "If you would like to make a regular left click, use your thumb to let the GND electrode touch the left electrode on your index finger, which is the electrode \n"
   "closest to your nail. If you would like to make a right click, make sure to connect the GND electrode with the right electrode. In case that the mouse starts  \n"
   "behaving in an undesired way, there is a reset button to press. Connect the thumb electrode to the electrode from you index finger that is closest to your palm. \n"
   "When restarting the application, the vibrator buzzes to give you feedback to let you know that the Mouse-glove is resetting. \n"
   ));
   instrTxt->setAlignment(Qt::AlignCenter);
   okButton = new QPushButton(tr("Ok")); 
   
   // for colouring button
   QPalette p = okButton->palette();
   p.setColor(QPalette::Button, QColor(255,250,250,255));
   okButton->setAutoFillBackground(true);
   okButton->setPalette(p);
   okButton->update();

   // adding all widgets to layout
   instrLayout->addWidget(instrPic, 0, 0); // placement on row 0, column 0
   instrLayout->addWidget(instrTxt, 1, 0); // placement on row 1, column 0
   instrLayout->addWidget(okButton, 2, 0); // placement on row 2, column 0
   
   // action when buttons is pressed
   connect(okButton, &QPushButton::clicked, this, &InstrWindow::close);
   
   // for colouring window
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
