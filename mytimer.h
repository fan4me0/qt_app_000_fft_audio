#ifndef MYTIMER_H
#define MYTIMER_H

#include <QTimer>
#include "mainWin.h"

//From Qt documentation ("C++-GUI-Programming-with-Qt-4-1st-ed.pdf) :
//    The Q_OBJECT macro at the beginning of the class definition is necessary for all
//    classes that define signals or slots.
//     - So, does class myTimer need Q_OBJECT macro?

class myTimer : public QObject {
    Q_OBJECT

public:
    myTimer(QObject *parent = 0);

private:
    QTimer timer;
    MainWindow * workerMainPointer;

protected:
    void timerEvent(QTimerEvent *event);
};

#endif // MYTIMER_H
