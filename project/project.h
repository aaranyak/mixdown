/* project/project.h
 * Contains definitions for project data types
*/
// Author - Aaranyak


#ifndef PROJECT_H /* Header Guard */
#define PROJECT_H

#include "project_settings/project_settings.h"
/* A note on tracks 
 * Tracks in a project are stored in a linked list, every track pointing to the next in line.
 *  -> The "typedef struct Track"; is located in project/tracks/tracks.h
 *  -> This method is used, rather than a pointer array, since reordering of tracks in this format is simpler
 *  -> This will be used currently, because in no forseen circumstance will we need to immedeatly lookup a track by it's position in the list.
 *  -> The "Track *tracks;" property will be a pointer to the first track in the linked list.
 *  -> The "Track *master;" will be a pointer to the master track, which will provide audio output.
*/
/* Is freeing memory during clean up really nessecary? Research on this. */

/* Basic definition of project object */
typedef struct Track Track;
typedef struct Project {
    char *name; /* Filename */
    char *path; /* Filepath (with name) */
    ProjectSettings project_settings; /* Includes all project settings */
    Track *tracks; /* Pointer to first track in linked list of tracks */
    Track *master; /* Master track (Output source) */
} Project;

/* All non-related includes here (meaning not referenced in this header) */
#include "init_project.h"
#endif
