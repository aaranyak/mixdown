/* Header file for toggle_icon_button.c and create_track_popup.c */

#ifndef TRKEDITCOMPS_H /* Header Guard */
#define TRKEDITCOMPS_H
GtkWidget *toggle_icon_button(GtkAdjustment *adjustment, char *icon_name);
GtkWidget *create_add_track_button(ViewContext *view_context);
#endif

