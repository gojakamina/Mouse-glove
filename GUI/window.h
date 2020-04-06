#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>
#include "instrwindow.h"

class QHBoxLayout;
class QGroupBox;
class QLabel;
class QPushButton;
class QGridLayout;
class InstrWindow;

/**
 * GUI window class.
 */

class Window : public QWidget
{
	Q_OBJECT

 public:

   /** The constructor. */
   Window(); //Constructor

   /** The destructor. */
  ~Window(); // Destructor

   // void timerEvent( QTimerEvent * );


 private:

   /** @brief Creates a text box. */
   void createTextBox();

   /** @brief Creates buttons. */
   void createButtons();

   /** Opens second window. */
   void openWindow();

   QLabel *instrTxt; /** Instruction text. */
   QPushButton *instrButton; /** Instruction button. */
   QPushButton *startButton; /** Start button. */
   QGroupBox *buttons; /** Button layout. */
   InstrWindow instrWindow; /** Instruction window. */
};

#endif // WINDOW_H

