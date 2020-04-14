#ifndef INSTRWINDOW_H
#define INSTRWINDOW_H

#include <QWidget>

class QLabel;
class QPushButton;
class QGridLayout;
class QPalette;
class QPixmap;

/**
 * @brief Instruction window class.
 */
class InstrWindow : public QWidget
{
	Q_OBJECT

 public:
  
   /** The constructor. */
   InstrWindow();


   /** The destructor. */
  ~InstrWindow();


 private:

   /** @brief Creates window. */
   void createWindow();

   QLabel *instrPic; /**< Instruction picture. */
   QLabel *instrTxt; /**< Instruction text. */
   QPushButton *okButton; /**< Ok button. */

};

#endif // INSTRWINDOW_H
