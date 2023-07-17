/* header file for track_editor.c */
#ifndef REGION_EDITOR_H /* Header Guard */
#define REGION_EDITOR_H
void *load_region_editor(ViewContext *view_context, GtkWidget **region_editor);
GtkWidget *create_editor_row(ViewContext *view_context, TrackState *track_state, char odd_even);
#endif

