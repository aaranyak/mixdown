/* project/project.h
 * Contains definitions for project data types
*/
// Author - Aaranyak

/* Basic definition of project object */
#include "project_settings/project_settings.h"
typedef struct Project {
    char *name; /* Filename */
    char *path; /* Filepath (without name) */
    int is_saved; /* If project is has a saved file */
    ProjectSettings project_settings;
} Project;

