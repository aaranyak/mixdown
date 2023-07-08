/* Contains function for initializing tracks view state */
#include "view_context.h"
#include "stdio.h"
#include "init_track_states.h"
#include <gtk/gtk.h>
// Author: Aaranyak Ghosh
void init_context(ViewContext *view_context, Project *project) {
    /* Initializes ViewContext object 
     * Project *project: Pointer to current project
     */
    view_context->project = project; /* Set project of context object to current project */
    view_context->state = PAUSE; /* Set initial state to paused */
    view_context->playhead = 0; /* Set playhad position to beginning */
    view_context->cursor = 0; /* Set cursor position to beginning (yes, I know it will change later) */
    init_track_states(view_context); /* Initialize all track state managers */
    view_context->scale = gtk_adjustment_new(project->project_settings.audio_settings.comp_unit / 3, 1, 22050, 1, 1, 0); /* 2450 samples per pixel */
    view_context->scroll = gtk_adjustment_new(0, 0, project->project_settings.length, 1, 2450 , 0); /* start of the project */
}
