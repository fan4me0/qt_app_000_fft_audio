#ifndef MAINWIN_H
#define MAINWIN_H

#include <QtWidgets/QApplication>
#include <QMenu>
#include <QAction>
#include <QMainWindow>
#include <QPushButton>
#include <qwt_plot.h>
#include <qwt_slider.h>
#include <QVector>
#include <fftw3.h>
#include <qwt_plot_curve.h>
#include "sliders.h"
#include "RtAudio.h"
#include "datafft.h"

class MainWindow: public  QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget * =NULL);
    ~MainWindow();

    void on_slider_changed(double new_freq);

private slots:
    void replot_curve(void);
    void on_changer_clicked();

private:
    void timerEvent(QTimerEvent * timerId );    // override of QObject 'virtual protected'
    void createMenus(void);
    void createActions(void);
    QAction *newAction;
    QMenuBar   *m_MenuBar;
    QMenu   *m_fileMenu;
    QPushButton     *changer;
    Slider          *m_slider_freq;
    Slider          *m_slider_scroll;
    QwtPlot         *m_main_plot;
    QwtPlotCurve    *m_main_curve;
    unsigned int    m_plot_size;
    QVector<QPointF> m_qpoint_magnitude;
};

#endif // MAINWIN_H
