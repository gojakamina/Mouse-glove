#ifndef WINDOW_H
#define WINDOW_H

#include <QWidget>

class QPushButton;
class QGridLayout;
class QTextEdit;

// This is the declaration of our Window class
// The definition/implementation is in window.cpp
class Window : public QWidget
{
	Q_OBJECT

public:
	explicit Window(QWidget *parent = 0); //Constructor

	~Window(); // Destructor

	// void timerEvent( QTimerEvent * );

private:
	QPushButton *button_1; // button
	QGridLayout *gridLayout; // grid layout
	QTextEdit *instTxt; // instruction text

};

#endif // WINDOW_H
