#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

class QHBoxLayout;
class QGroupBox;
class QTextEdit;
class QPushButton;
class QGridLayout;

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

   QTextEdit *instrTxt; /** Instruction text. */
   QPushButton *instrButton; /** Instruction button. */
   QPushButton *startButton; /** Start button. */
   QGridLayout *gridLayout; /** Grid layout. */
   QGroupBox *buttons; /** Button layout. */
};

#endif // WINDOW_H

