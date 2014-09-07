#ifndef QT_SPECTRA_PARAM_H
#define QT_SPECTRA_PARAM_H

//----------------------------------------------------------------------------------------------
// Parameters for audioSource.cpp
//----------------------------------------------------------------------------------------------

typedef double  MY_TYPE;
#define FORMAT RTAUDIO_FLOAT64

// !!! by default the data sampled in the OS buffer from signal input (e.g. microphone)
// are interleaved that is for channels = 2 samples that are fed into fft has to be
// selected either odd or even
#define AUDIO_DEV_CHANNEL_NBR               1UL

#define AUDIO_DEV_IN_FISRT_CHANNEL_OFFSET   0UL

#define AUDIO_DEV_OUT_FISRT_CHANNEL_OFFSET  0UL

#define AUDIO_DEV_BUFFER_FRAMES_NBR         512UL     // i.e. 'AUDIO_DEV_BUFFER_FRAMES_NBR' number of sample type

#define AUDIO_DEV_SAMPLING_FREQ             44100UL


//----------------------------------------------------------------------------------------------
// Parameters for dataFft.cpp
//----------------------------------------------------------------------------------------------

#define DATA_FFT_FFT_SIZE           1000 //44100

#endif // QT_SPECTRA_PARAM_H
