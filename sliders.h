#ifndef MYSLIDER_H
#define MYSLIDER_H

#include <qwidget.h>
#include <qwt_slider.h>

class QLabel;
class MainWindow;

class Slider: public QWidget
{
    Q_OBJECT
public:
    Slider( QWidget *parent, int sliderType, double startValue = 0 );
    void setParent(MainWindow * parent);

private Q_SLOTS:
    void setNum( double v );

private:
    QwtSlider *createSlider( QWidget *, int sliderType ) const;

    QwtSlider *d_slider;
    QLabel *d_label;
    MainWindow *d_parent;
};

#endif  // MYSLIDER_H
