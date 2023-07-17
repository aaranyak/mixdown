/* Contains TrackState object
 * Stores the state of the a track */
// Author - Aaranyak Ghosh

#ifndef TRACK_STATE_H /* Header Guard */
#define TRACK_STATE_H
#include "../../../project/project.h"
#include <gtk/gtk.h>
typedef struct TrackState TrackState;
typedef struct TrackState {
    // Essentials
    Track *track;
    TrackState *prev;
    TrackState *next;
    // Properties
    GtkAdjustment *volume;
    GtkAdjustment *pan;
    GtkAdjustment *mute;
    GtkAdjustment *solo;
    GtkAdjustment *record;
    // Associated widgets
    GtkWidget *region_editor; /* The region editor of this track */
    GtkWidget *track_cell; /* The track cell of this track */
} TrackState;
#include "track_state_utils.h"
#endif

