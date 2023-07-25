/* Header file for toggle_icon_button.c, track_context_menu.c and create_track_popup.c */

#ifndef TRKEDITCOMPS_H /* Header Guard */
#define TRKEDITCOMPS_H
void track_rclick_signal_connect(GtkWidget **track_cell, ViewContext *view_context, TrackState *track_state);
GtkWidget *toggle_icon_button(GtkAdjustment *adjustment, char *icon_name);
GtkWidget *create_add_track_button(ViewContext *view_context);
#endif

