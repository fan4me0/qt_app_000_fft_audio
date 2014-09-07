#ifndef DATAFFT_H
#define DATAFFT_H

#include <vector>
#include <complex>
#include <fftw3.h>
#include <QVector>
#include "parameters.h"
#include <QPointF>

class DataFft
{
public:
    DataFft(unsigned int fft_size = DATA_FFT_FFT_SIZE);
    void compute_magnitude(void);
    void compute_fft(void);
    void give_magnitude_copy(QVector<QPointF> & qvec_magn);
    void dbg_fill_fft_in_sine(double freq);
    void dbg_fill_fft_in_audio(void *inputBuffer, unsigned long bytes);
    void set_fft_gain(double gain);
    unsigned int get_fft_size(void) const;

private:
    void create_plan(void);

    std::vector<std::complex<double>>   m_fft_in;
    std::vector<std::complex<double>>   m_fft_out;
    std::vector<double>     m_fft_magnitude;
    unsigned int    m_fft_size;
    fftw_plan       m_fft_plan;
    double          m_fft_gain;
};

#endif // DATAFFT_H
