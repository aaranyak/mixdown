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

int main(int argc, char *argv[]) {
    /* Test play audio */
    snd_pcm_t *pcm; /* Audio device handle */
    int audio_length;
    int frequency;
    float volume;
    printf("Enter audio length: ");
    scanf("%d", &audio_length);
    printf("Enter sound frequency: ");
    scanf("%d", &frequency);
    printf("Enter sound volume: ");
    scanf("%f", &volume);
    snd_pcm_open(&pcm, "default", SND_PCM_STREAM_PLAYBACK, 0); /*Open audio device */
    snd_pcm_hw_params_t *hw_params; /* Hardware params object */
    snd_pcm_hw_params_alloca(&hw_params); /* Allocate hwparams */
    snd_pcm_hw_params_any(pcm, hw_params); /* Set hwparams to default values */
    snd_pcm_hw_params_set_access(pcm, hw_params, SND_PCM_ACCESS_RW_INTERLEAVED); /* Research on this later */
    snd_pcm_hw_params_set_format(pcm, hw_params, SND_PCM_FORMAT_S16_LE); /* Unsigned 16 bit audio */
    snd_pcm_hw_params_set_channels(pcm, hw_params, 1); /* Mono audio */
    snd_pcm_hw_params_set_rate(pcm, hw_params, 48000, 0); /* 48000 hz sample rate */
    snd_pcm_hw_params_set_periods(pcm, hw_params, 10, 0); /* Research on this later */
    snd_pcm_hw_params_set_period_time(pcm, hw_params, 100000, 0); // 0.1 seconds
    snd_pcm_hw_params(pcm, hw_params); /* Set hwparams */
    short samples[48000 * audio_length]; /* Samples = 3 seconds */
    for (int i = 0; i < 48000 * audio_length; i++) {
        short sample = (i % frequency) * (65535 / frequency);
        samples[i] = sample * volume;
        //printf("%d\n", sample);
    }
    snd_pcm_writei(pcm, samples, 48000 * audio_length); /* Write audio */
    snd_pcm_drain(pcm); /* Play audio */
    snd_pcm_close(pcm); /* Close device */
    return 0;
}
