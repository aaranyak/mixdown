/* Header file for track_utils.c */
#ifndef TRACK_UTILFUNCS_H /* Header Guard */
#define TRACK_UTILFUNCS_H
#include "../project.h"
Track *get_last_track(Track *linked_list);
Track *add_track(Project *project,
                 char name[128],
                 TrackType type,
                 float volume,
                 float pan);
void delete_track(Project *project, Track *track);
void free_tracks(Project *project);
#endif
