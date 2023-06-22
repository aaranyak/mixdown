/* project/project_settings/project_settings.h
 * Contains the project settings struct, which includes
 * Time signature
 * Project length
 * Other settings
 */
// Author - Aaranyak Ghosh
/* project/project_settings/project_settings.h
 * Contains the project settings struct, which includes
 * Time signature
 * Project length
 * Tempo
 */
// Author - Aaranyak Ghosh
#ifndef PROJECTSETTINGS_H /* Header Guard */
#define PROJECTSETTINGS_H
#include "time_signature.h"
#include "audio_settings.h"
/* ProjectSettings object */
typedef struct ProjectSettings {
    AudioSettings audio_settings; /* In audio_settings.h */
    TimeSignature time_signature; /* in time_signature.h */
    int tempo; /* In BPM */
    int length; /* No. of samples */
} ProjectSettings;
#endif
