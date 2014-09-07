#include "mytimer.h"
#include "mainWin.h"

myTimer::myTimer(QObject *parent) : QObject(parent)
{
    if (parent == 0)
        throw std::domain_error("Parameter parent must be initialized.");
    workerMainPointer = static_cast<MainWindow*>(parent);
}

void myTimer::timerEvent(QTimerEvent *event)
{
    workerMainPointer->replot_curve();
}
