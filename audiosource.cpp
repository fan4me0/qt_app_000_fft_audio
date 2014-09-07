#include <iterator>
#include <fstream>
#include <sstream>
#include <iostream>

#include "RtAudio.h"
#include "audiosource.h"
#include "parameters.h"
#include "datafft.h"
#include <vector>
extern class DataFft * m_main_signal;

unsigned int dbg_callback_counter = 0;
std::vector<std::vector<double>> audio_log(1000);
static bool log_buff = false;

int audio_buffer_full( void *outputBuffer, void *inputBuffer, unsigned int nBufferFrames,
                                double streamTime, RtAudioStreamStatus status, void *data )
{
    // Since the number of input and output channels is equal, we can do
    // a simple buffer copy operation here.
    dbg_callback_counter++;
    if ( status ) std::cout << "Stream over/underflow detected." << std::endl;

    unsigned long *bytes = (unsigned long *) data;
    std::cerr << dbg_callback_counter << "  -----  " << nBufferFrames << std::endl;
    //memcpy( outputBuffer, inputBuffer, *bytes );
    m_main_signal->dbg_fill_fft_in_audio( inputBuffer, 8000);

    static int log_iter = 0;
    if( (log_buff == true) && (log_iter < 1000) )
    {
        for(int iter = 0; iter < 512; iter++)
        {
            audio_log[log_iter].push_back(((double*)inputBuffer)[iter]);
        }
        log_iter++;
    }

    static bool store_data = false;
    if( (store_data == true) || (log_iter == 1000) )
    {
        std::ofstream out_curve;
        out_curve.open("b_spline_samples.txt",std::ios::out);
        std::stringstream   ssline;
        ssline.setf(std::ios::fixed,std::ios::floatfield);
        ssline.precision(6);

        for(int iter = 0; iter < 1000; iter++)
        {
            for(auto & index: audio_log[iter])
            {
                //std::cout << index << std::endl;
                ssline << index;
                out_curve << ssline.str() << "\t";
                ssline.str("") ;
            }
            out_curve << std::endl;
        }
        out_curve.close();
        store_data = false;
    }

    return 0;
}

audioSource::audioSource(unsigned int sampl_freq) : m_sampling_freq(sampl_freq)
{
    if ( m_audio_device.getDeviceCount() < 1 )
    {
        std::cout << "\nNo audio devices found!\n";
        exit( 0 );
    }

    m_aud_dev_in_params.nChannels = AUDIO_DEV_CHANNEL_NBR;
    m_audio_buffer_frames = AUDIO_DEV_BUFFER_FRAMES_NBR;

    // iDevice = 0;  -> Device Name = Default Device - duplex mode
    // iDevice = 5;  -> Device Name = Mic in at rear panel (Pink) (Realtek High Definition Audio)
    //                  !!! This majk has to be than set as default in the system 'control panel->sound->recording'
    // iDevice = 8;  -> Device Name = Microphone (3- USB Audio CODEC ) - external 'Alesis' mixpult
    unsigned int iDevice = 0, oDevice = 0;
    if ( iDevice == 0 )
        m_aud_dev_in_params.deviceId = m_audio_device.getDefaultInputDevice();
    else
        m_aud_dev_in_params.deviceId = iDevice - 1;

    m_aud_dev_in_params.firstChannel = AUDIO_DEV_IN_FISRT_CHANNEL_OFFSET;

    if ( oDevice == 0 )
        m_aud_dev_out_params.deviceId = m_audio_device.getDefaultOutputDevice();
    else
        m_aud_dev_out_params.deviceId = oDevice - 1;

    m_aud_dev_out_params.nChannels = AUDIO_DEV_CHANNEL_NBR;
    m_aud_dev_out_params.firstChannel = AUDIO_DEV_OUT_FISRT_CHANNEL_OFFSET;

    try {
        // !!! if want to use input and output and one of them is aquired from duplex device, second one has to be as well
        // first variant for input only mode
        m_audio_device.openStream( NULL, &m_aud_dev_in_params, FORMAT, m_sampling_freq,
                                   &m_audio_buffer_frames, &audio_buffer_full, (void *)&m_audio_buffer_bytes, &m_options );
        // second variant is a must for duplex mode
        // m_audio_device.openStream( &m_aud_dev_out_params, &m_aud_dev_in_params, FORMAT, m_sampling_freq,
        //                            &m_audio_buffer_frames, &audioSource::audio_buffer_full, (void *)&m_audio_buffer_bytes, &m_options );
    }
    catch ( RtAudioError& e ) {
        std::cout << '\n' << e.getMessage() << '\n' << std::endl;
        exit( 1 );
    }
    m_audio_buffer_bytes = m_audio_buffer_frames * m_aud_dev_in_params.nChannels * sizeof( MY_TYPE );

    // start audio stream
    try {
        m_audio_device.startStream();
    }
    catch ( RtAudioError& e ) {
        std::cout << '\n' << e.getMessage() << '\n' << std::endl;
    }
}

audioSource::~audioSource()
{
      // appl. crash if stream stopped- why?
//    if ( m_audio_device.isStreamRunning() )
//      m_audio_device.stopStream();
}

