#include "datafft.h"
#include <fftw3.h>
#include <QVector>
#include <cmath>
#include "qwt_math.h"
//#include "windows.h"
#include <iostream>
//#include "Winbase.h"

using namespace std;

DataFft::DataFft(unsigned int fft_size) : m_fft_size(fft_size)
{
    // first buffers have to be resized, than fft plan can be created
    m_fft_magnitude.resize(fft_size);
    m_fft_in.resize(fft_size);
    m_fft_out.resize(fft_size);
    create_plan();
}

void DataFft::create_plan(void)
{
    m_fft_plan = fftw_plan_dft_1d( m_fft_size, (fftw_complex*)&m_fft_in[0], // Q_A: why this is not OK : static_cast<fftw_complex*>(&m_fft_in[0]),
                                               (fftw_complex*)&m_fft_out[0], FFTW_FORWARD, FFTW_ESTIMATE);
}

void DataFft::compute_fft(void)
{
//    LARGE_INTEGER _frequency;        // ticks per second
//    LARGE_INTEGER _time_stmp_1, _time_stmp_2;           // ticks
//    double _elapsed_time;
//    QueryPerformanceFrequency(&_frequency);
//    QueryPerformanceCounter(&_time_stmp_1);
    fftw_execute(m_fft_plan);
//    QueryPerformanceCounter(&_time_stmp_2);
//    _elapsed_time = (_time_stmp_2.QuadPart - _time_stmp_1.QuadPart) * 1000.0 / _frequency.QuadPart;
//    std::cerr << "  ------------------->>>>>  " << _elapsed_time << "  ms" << std::endl;
    compute_magnitude();
}

void DataFft::give_magnitude_copy(QVector<QPointF> & qvec_magn)
{
    for(int iter = 0; iter < qvec_magn.size(); iter++)
    {
        qvec_magn[iter].setY(static_cast<qreal>(m_fft_magnitude[iter]));
    }

    //copy_n(qvec_magn.begin(), qvec_magn.size(), m_fft_magnitude );
}


void DataFft::compute_magnitude(void)
{
    complex<double> _fft_out_element;
    double _temp;
    unsigned int iter;
    double _normalize = (1/(25*((double)(m_fft_size * m_fft_size)/100)));
    for(iter = 0; iter < m_fft_magnitude.size(); iter++)
    {
        _fft_out_element = m_fft_out[iter];                // correct 'operator complex ='
        _temp = norm(_fft_out_element) * _normalize;
        m_fft_magnitude[iter] = 20.0 * log10(_temp);        // convert to dB
    }
}


#define ARR_SIZE 1000
double myArray[ARR_SIZE];
void DataFft::dbg_fill_fft_in_audio(void *inputBuffer, unsigned long bytes)
{
    memcpy((void*) myArray, inputBuffer, bytes );

    for(int iter = 0; iter < ARR_SIZE; iter++)
    {
        m_fft_in[iter] = std::complex<double>( (myArray[iter] * m_fft_gain), 0 );
    }
}

void DataFft::set_fft_gain(double gain)
{
    m_fft_gain = gain;
}

void DataFft::dbg_fill_fft_in_sine(double freq)
{
    // simulate change of the input signal freq
    double sin_inc;
    sin_inc = (2* M_PI * freq)/m_fft_size;
    int iter = 0;
    for(auto it = m_fft_in.begin(); it != m_fft_in.end(); it++ , iter++)
    {
        it->real(qFastSin(sin_inc*iter));
    }

}

unsigned int DataFft::get_fft_size(void) const
{
    return m_fft_size;
}
