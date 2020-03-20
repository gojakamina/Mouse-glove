#ifndef WINDOW_H
#define WINDOW_H

#include <QtWidgets>
#include <QBoxLayout>

class Window : public QWidget {

Q_OBJECT

public:

	Window(); // constructor

	~Window(); // destructor

	// void timerEvent( QTimerEvent * );

private:

	// layout elements from Qt itself http://qt-project.org/doc/qt-4.8/classes.html
	QVBoxLayout  *vLayout;  // vertical layout
	QHBoxLayout  *hLayout;  // horizontal layout

};

#endif // WINDOW_H
