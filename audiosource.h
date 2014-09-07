#ifndef AUDIOSOURCE_H
#define AUDIOSOURCE_H

#include "RtAudio.h"
#include "parameters.h"

class audioSource
{
public:
    audioSource(unsigned int sampl_freq = AUDIO_DEV_SAMPLING_FREQ);
    virtual ~audioSource();
private :
    RtAudio         m_audio_device;
    RtAudio::StreamParameters   m_aud_dev_in_params;
    RtAudio::StreamParameters   m_aud_dev_out_params;
    RtAudio::StreamOptions      m_options;
    unsigned int    m_audio_buffer_frames;      // number of elements of size e.g. double
    unsigned int    m_audio_buffer_bytes;       // number of bytes in buffer i.e. 'm_audio_buffer_frames * sizeof(double)'
    unsigned int    m_sampling_freq;
};

#endif // AUDIOSOURCE_H
