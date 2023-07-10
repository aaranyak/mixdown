/* header file for track_editor.c */
#ifndef TRACK_EDITOR_H /* Header Guard */
#define TRACK_EDITOR_H
#include "../view_context/view_context.h"
void *load_track_editor(ViewContext *view_context, GtkWidget **track_editor);
GtkWidget *create_track_cell(ViewContext *view_context, TrackState *track_state);
#endif

