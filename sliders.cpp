#include <qapplication.h>
#include <qlabel.h>
#include <qlayout.h>
#include <qwt_slider.h>
#include <qwt_scale_engine.h>
#include <qwt_scale_map.h>
#include "sliders.h"
#include "mainWin.h"

//class Layout: public QBoxLayout
//{
//public:
//    Layout( Qt::Orientation o, QWidget *parent = NULL ):
//        QBoxLayout( QBoxLayout::LeftToRight, parent )
//    {
//        if ( o == Qt::Vertical )
//            setDirection( QBoxLayout::TopToBottom );

//        setSpacing( 20 );
//        setMargin( 0 );
//    }
//};

Slider::Slider( QWidget *parent, int sliderType, double startValue ):
    QWidget( parent )
{
    d_slider = createSlider( this, sliderType );
    QFlags<Qt::AlignmentFlag> alignment( Qt::AlignHCenter | Qt::AlignTop );
//    switch( d_slider->scalePosition() )
//    {
//        case QwtSlider::NoScale:
//            if ( d_slider->orientation() == Qt::Horizontal )
//                alignment = Qt::AlignHCenter | Qt::AlignTop;
//            else
//                alignment = Qt::AlignVCenter | Qt::AlignLeft;
//            break;
//        case QwtSlider::LeftScale:
//            alignment = Qt::AlignVCenter | Qt::AlignRight;
//            break;
//        case QwtSlider::RightScale:
//            alignment = Qt::AlignVCenter | Qt::AlignLeft;
//            break;
//        case QwtSlider::TopScale:
//            alignment = Qt::AlignHCenter | Qt::AlignBottom;
//            break;
//        case QwtSlider::BottomScale:
//            alignment = Qt::AlignHCenter | Qt::AlignTop;
//            break;
//    }

    d_label = new QLabel( "0", this );
    //d_label->setAlignment( alignment );
    d_label->setFixedWidth( d_label->fontMetrics().width( "10000.9" ) );

    connect( d_slider, SIGNAL( valueChanged( double ) ), SLOT( setNum( double ) ) );

    QBoxLayout *layout;
    if ( d_slider->orientation() == Qt::Horizontal )
        layout = new QHBoxLayout( this );
    else
        layout = new QVBoxLayout( this );

    layout->addWidget( d_slider );
    layout->addWidget( d_label );
    //set slider offset, if any
    d_slider->setValue(startValue);
    setNum(startValue);
}

QwtSlider *Slider::createSlider( QWidget *parent, int sliderType ) const
{
    QwtSlider *slider = NULL;

    switch( sliderType )
    {
        case 0:
        {
            slider = new QwtSlider( Qt::Horizontal , parent );
            slider->setScalePosition( QwtSlider::TrailingScale );
            slider->setTrough(true);
            slider->setHandleSize( QSize(30, 16) );
            slider->setScale( 0.0, 5000.0 );
            slider->setTotalSteps( 500000 );
            break;
        }
//        case 1:
//        {
//            slider = new QwtSlider( parent, Qt::Horizontal,
//                QwtSlider::NoScale, QwtSlider::Trough | QwtSlider::Groove );
//            slider->setRange( 0.0, 1.0, 0.01, 5 );
//            break;
//        }
        case 2:
        {
            slider = new QwtSlider( Qt::Horizontal, parent );
            slider->setScalePosition( QwtSlider::LeadingScale );
            slider->setTrough(true);
            slider->setHandleSize( QSize(12,25) );
            slider->setScale( 0.0, 5000.0 );
            slider->setTotalSteps( 10000 );
            break;
        }
//        case 3:
//        {
//            slider = new QwtSlider( parent, Qt::Vertical,
//                QwtSlider::LeftScale, QwtSlider::Groove );
//            slider->setRange( 0.0, 100.0, 1.0, 5 );
//            slider->setScaleMaxMinor( 5 );
//            break;
//        }
//        case 4:
//        {
//            slider = new QwtSlider( parent, Qt::Vertical,
//                QwtSlider::NoScale, QwtSlider::Trough );
//            slider->setRange( 0.0, 100.0, 1.0, 10 );
//            break;
//        }
//        case 5:
//        {
//            slider = new QwtSlider( parent, Qt::Vertical,
//                QwtSlider::RightScale, QwtSlider::Trough | QwtSlider::Groove );
//            slider->setScaleEngine( new QwtLog10ScaleEngine );
//            slider->setHandleSize( 20, 32 );
//            slider->setBorderWidth( 1 );
//            slider->setRange( 0.0, 4.0, 0.01 );
//            slider->setScale( 1.0, 1.0e4 );
//            slider->setScaleMaxMinor( 10 );
//            break;
//        }
    }

    if ( slider )
    {
        QString name( "Slider %1" );
        slider->setObjectName( name.arg( sliderType ) );
    }

    return slider;
}

void Slider::setNum( double v )
{
    d_parent->on_slider_changed(v);     // Q_A: how is it possible that d_parent is not set but still 'on_slider_changed'
                                        // is called correctly

    QString text;
    text.setNum( v, 'f', 2 );

    d_label->setText( text );
}

void Slider::setParent(MainWindow * parent)
{
    //d_parent = parent;
}
