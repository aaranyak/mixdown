/* project/project.h
 * Contains definitions for project data types
*/
// Author - Aaranyak


#ifndef PROJECT_H /* Header Guard */
#define PROJECT_H

#include "project_settings/project_settings.h"

/* Basic definition of project object */
typedef struct Project {
    char *name; /* Filename */
    char *path; /* Filepath (without name) */
    int is_saved; /* If project is has a saved file */
    ProjectSettings project_settings;
} Project;
#endif