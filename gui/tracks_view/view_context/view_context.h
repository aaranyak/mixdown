/* Contains ViewContext object
 * Stores the state of the tracks view */
// Author - Aaranyak Ghosh

#ifndef VIEWCONTEXT_H /* Header Guard */
#define VIEWCONTEXT_H
#include "../../../project/project.h"

/* Simple enum for playback state */
typedef enum view_state {PLAY, PAUSE, RECORD} view_state;

/* View context state struct */
typedef struct ViewContext {
    Project *project; /* Pointer to project */
    view_state state; /* Playing/paused/recording */
} ViewContext;
#endif
