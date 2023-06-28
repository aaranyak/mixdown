/* Header file for track_utils.c */
#ifndef TRACK_UTILS_H /* Header Guard */
#define TRACK_UTILS_H
#include <stdio.h>
printf("Check\n");
Track *get_last_track(Track *linked_list) {
Track *add_track(Project *project,
                 char name[128],
                 TrackType type,
                 float volume,
                 float pan);
void free_tracks(Project *project);
#endif
