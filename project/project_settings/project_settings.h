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
 * Other settings
 */
// Author - Aaranyak Ghosh
#include "time_signature.h"
/* ProjectSettings object */
typedef struct ProjectSettings {
    TimeSignature time_signature;
    int length;
} ProjectSettings;
