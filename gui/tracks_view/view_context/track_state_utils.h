/* Header file for init_track_states.c */
#ifndef TRACK_STATE_UTILS_H /* Header Guard */
#define TRACK_STATE_UTILS_H
typedef struct ViewContext ViewContext; /* Forward Decleration (just in case) */
void init_track_states(ViewContext *view_context);
TrackState *add_track_state(ViewContext *view_context, TrackState *prev, Track *track);
TrackState *get_last_track_state(TrackState *linked_list);
int get_num_track_states(TrackState *linked_list);
void free_track_states(ViewContext *view_context);
#endif
