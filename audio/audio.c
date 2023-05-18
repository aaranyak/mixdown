#define ALSA_PCM_NEW_HW_PARAMS_API /* Use the newer ALSA api */

#include <alsa/asoundlib.h>

int open_audio_device(snd_pcm_t **handle, /* Pcm device handle, remember to run "snd_pcm_close(handle)" at the end of program */
                      char *device_name, /* Use "default" for opening the default audio device */
                      int play_audio) /* Set to 1 if used for playing audio, otherwise set 0 */
{
    /* Opens a ALSA pcm audio device */
    int status; /* Error Status */
    snd_pcm_stream_t stream_type = SND_PCM_STREAM_CAPTURE; /* Record/Play audio */
    if (play_audio) stream_type = SND_PCM_STREAM_PLAYBACK; /* If stream type is play, set it */
    status = snd_pcm_open(handle, device_name, stream_type, 0);
    if (status < 0) { /* If error occured while opening device */
        fprintf(stderr, "Error while opening audio device %s: %s\n", device_name,snd_strerror(status));
    }
    return status;
}

int set_hardware_params(snd_pcm_t *handle, /* Handle to audio device */
                        snd_pcm_hw_params_t *hardware_params, /* Hardware params object */
                        int resample_rate /* The resample rate of the track */ )
{
    /* Set the hardware parameters of an audio device */
    int status = 0; /* Error status */
    status = snd_pcm_hw_params_any(handle, hardware_params); /* Set hardware_params to default values*/
    if (status < 0) { /* If error occurs */
        fprintf(stderr, "Error while setting hardware params object: %s\n", snd_strerror(status)); /* Print error message */
        return status; /* Return error status */
    }
    return status;
}
int main(int argc, char *argv[]) {
    /* Currently, do nothing */ 
    snd_pcm_t *handle;
    snd_pcm_hw_params_t *hardware_params;
    int status;
    status = open_audio_device(&handle, "default", 1);
    snd_pcm_hw_params_alloca(&hardware_params);
    status = set_hardware_params(handle, hardware_params, 0);
    return 1;
}
