#define ALSA_PCM_NEW_HW_PARAMS_API /* Use the newer ALSA api */

#include <alsa/asoundlib.h>

int open_audio_device(snd_pcm_t *handle, /* Pcm device handle, remember to run "snd_pcm_close(handle)" at the end of program */
                      char *device_name, /* Use "default" for opening the default audio device */
                      int play_audio) /* Set to 1 if used for playing audio, otherwise set 0 */
{
    /* Opens a ALSA pcm audio device */
    snd_pcm_stream_t stream; /* Playback stream or capture stream */
    int status; /* If negative, then error status. If 0, then success */
    if (play_audio) stream = SND_PCM_STREAM_PLAYBACK; /* Set stream to playback stream */
    else stream = SND_PCM_STREAM_CAPTURE; /* Set stream to capture */
    status = snd_pcm_open(&handle, device_name, stream, 0); /* Open the pcm device */
    if (status < 0) { /* If error occurs */
        fprintf(stderr, "Error while opening pcm device \"%s\": %s.\n", device_name, snd_strerror(status)); /* Print error message */
    }
    return status;
}

int main(int argc, char *argv[]) {
    /* Currently, do nothing */
    snd_pcm_t *handle;
    if (argc) {
        int status = open_audio_device(handle, argv[1], 1);
    }
    return status;
}
