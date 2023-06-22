/* audio_settings.h
 * Advanced audio settings, Accessible from project settings window.
 * Includes:
 *  -> Sample Rate
 *  -> Computation Unit Length
 *  -> Period Size
 *  -> Gpu/Cpu
*/
// Author = Aaranyak Ghosh
#ifndef AUDIOSETTINGS_H /* Header Guard */
#define AUDIOSETTINGS_H
/* AudioSettings Object */
typedef struct AudioSettings {
    int sample_rate; /* In Hz */
    int comp_unit; /* Chunk of audio to be computed at a time (No. of samples) */
    int period_count; /* Number of times audio is sent to hardware (Research on this later) */
    int use_gpu; /* Boolean value, if not 0, the mixing will be done parellaly using the gpu. (Works better with larger computation units) */
} AudioSettings;
#endif
