/* Header file for control_buttons.c and tempo_setter.c */

#ifndef CTRPANELCOMPS_H /* Header Guard */
#define CTRPANELCOMPS_H
GtkWidget *create_control_buttons(ViewContext *view_context); /* Returns all control buttons */
GtkWidget *create_tempo_setter(ViewContext *view_context);
#endif
