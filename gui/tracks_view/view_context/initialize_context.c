/* Contains function for initializing tracks view state */
#include "view_context.h"
#include "stdio.h"
// Author: Aaranyak Ghosh
void init_context(ViewContext *view_context, Project *project) {
    /* Initializes ViewContext object 
     * Project *project: Pointer to current project
     */
    view_context->project = project; /* Set project of context object to current project */
    view_context->state = PAUSE; /* Set initial state to paused */
}
