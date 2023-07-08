/* Contains ViewContext object
 * Stores the state of the tracks view */
// Author - Aaranyak Ghosh

#ifndef VIEWCONTEXT_H /* Header Guard */
#define VIEWCONTEXT_H
#include "../../../project/project.h"
#include "track_state.h"
/* Simple enum for playback state */
typedef enum view_state {PLAY, PAUSE, RECORD} view_state;

/* View context state struct */
typedef struct ViewContext {
    Project *project; /* Pointer to project */
    view_state state; /* Playing/paused/recording */
    TrackState* tracks; /* Linked list of track states */
    unsigned int playhead; /* Playhead position (in samples) */
    unsigned int cursor; /* Cursor position (Ditto) */
    GtkAdjustment *scale; /* This is the value of how zoomed in the view is. (samples per pixel) */
    GtkAdjustment *scroll; /* in samples, not pixels */
} ViewContext;
#endif
