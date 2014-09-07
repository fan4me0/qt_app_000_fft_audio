#include <QtWidgets/QApplication>
#include "mainWin.h"
#include <QMainWindow>
#include <QtWidgets>
#include <QMenu>
#include <QtGui>
#include <qlayout.h>
#include <QPushButton>
#include <QGridLayout>
#include <qwt_plot.h>
#include <qwt_plot_curve.h>
#include <qwt_slider.h>
#include <qwt_plot_grid.h>
#include "sliders.h"
#include "datafft.h"

using namespace std;

const double sineStartValue = 100;

DataFft  *m_main_signal;

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent)
{
    // create menu bar and actions
    createActions();
    createMenus();

    // initialize FFTW
    m_main_signal = new DataFft();
    m_qpoint_magnitude.resize(m_main_signal->get_fft_size());
    setCentralWidget(new QWidget(this));
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setSpacing(5);
    layout->setMargin(15);

    //------------qwt plot start---------------------
    QString label;
    label.sprintf( "FFT plot" );
    QwtText text(label);
    m_main_plot = new QwtPlot(text, parent);
    m_main_plot->setCanvasBackground(QColor( Qt::darkBlue ));
    m_main_plot->setAxisScale( QwtPlot::xBottom, 0, m_main_signal->get_fft_size() / 2 );
    m_main_plot->setAxisTitle( QwtPlot::xBottom, "FFT points [-]" );
    m_main_plot->setAxisScale( QwtPlot::yLeft, -250, 2 );
    m_main_plot->setAxisTitle( QwtPlot::yLeft, "Sine magnitude [dB]" );
    m_main_plot->enableAxis(QwtPlot::yRight,true);
    m_main_plot->setAxisScale( QwtPlot::yRight, -250, 2 );
    m_main_plot->enableAxis(QwtPlot::xTop,true);
    m_main_plot->setAxisScale( QwtPlot::xTop, 0, m_main_signal->get_fft_size() / 2 );

    QwtPlotGrid *grid = new QwtPlotGrid();
    grid->setPen( QPen( Qt::green, 0.0, Qt::DotLine ) );
    grid->enableX( true );
    grid->enableXMin( true );
    grid->enableY( true );
    grid->enableYMin( false );
    grid->attach( m_main_plot );

    m_slider_freq = new Slider(this, 2, sineStartValue);
    m_main_plot->setCanvasBackground( QColor( Qt::white ) );

    m_slider_scroll = new Slider(this, 2, 2500);

    // add curve
    m_main_curve = new QwtPlotCurve("Main curve");

    // connect or copy the data to the curves
    int iter = 0;
    for(auto it = m_qpoint_magnitude.begin(); it != m_qpoint_magnitude.end(); it++ , iter++)
    {
        *it = QPointF(iter,iter);   // initialize 'x' axis
    }

    layout->addWidget(m_slider_freq);
    layout->addWidget(m_slider_scroll);
    layout->addWidget(m_main_plot);
    centralWidget()->setLayout(layout);

    m_main_curve->setSamples(m_qpoint_magnitude);
    m_main_curve->setPen(QPen(Qt::green));
    m_main_curve->attach(m_main_plot);

    // finally, refresh the plot
    m_main_plot->replot();
}

MainWindow::~MainWindow()
{

    delete m_main_signal;
}

void MainWindow::replot_curve(void)
{
    m_main_signal->compute_fft();
    m_main_signal->give_magnitude_copy(m_qpoint_magnitude);
    m_main_curve->setSamples(m_qpoint_magnitude);
    // plot curve
    m_main_plot->replot();
}

void MainWindow::on_changer_clicked()
{
    //put here code to execute over the button pressed
}

void MainWindow::on_slider_changed(double new_freq)
{
    m_main_signal->set_fft_gain(new_freq);          // use for to set fft gain
    //m_main_signal->dbg_fill_fft_in_sine(new_freq);   // use for pure sine
}

void MainWindow::timerEvent(QTimerEvent * timerId)
{
    replot_curve();
    m_main_plot->setCanvasBackground(QColor( Qt::black ));

}

void MainWindow::createActions()
{
    newAction = new QAction(tr("&New"), this);
}

void MainWindow::createMenus()
{
    m_MenuBar = new QMenuBar(this);
    m_fileMenu = new QMenu("&File");
    m_fileMenu->addAction(newAction);
    m_fileMenu->addMenu(new QMenu("menu1_SubMenu"));
    m_MenuBar->addMenu(m_fileMenu);
    setMenuBar(m_MenuBar);
}
