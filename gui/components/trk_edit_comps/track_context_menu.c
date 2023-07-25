/* track_context_menu.c
 * Has function to create the popup menu when track is right clicked
 * Contains functionalities to 
 *  -> Delete track
 *  -> etc.
*/
#include <gtk/gtk.h>
#include <string.h>
#include "../../tracks_view/view_context/view_context.h"
#include "../../theme/theme.h"
#include "../../../project/project.h"
#include "../../tracks_view/editor/editor_actions/editor_actions.h"

struct tcm_event_data { /* Data to send to the event to create context menu */
    ViewContext *view_context;
    TrackState *track_state;
};

gboolean launch_popup_signal(GtkWidget *track_cell, GdkEventButton *event, struct tcm_event_data data) {
    /* On right click, launch context menu */
    printf("Naa na na boo boo, I was just tricking you!\n"); /* Debugging */
    return 0;
}

void track_rclick_signal_connect(GtkWidget **track_cell, ViewContext *view_context, TrackState *track_state) {
    /* Connects the right_click handler to the track widget */
    gtk_widget_add_events(*track_cell, GDK_BUTTON_PRESS_MASK); /* Add the event listener */ 
    struct tcm_event_data *signal_data = (struct tcm_event_data*)malloc(sizeof(struct tcm_event_data)); /* Signal data struct */
    signal_data->view_context = view_context; signal_data->track_state = track_state; /* Set the data before connecting the signal */
    g_signal_connect_data(*track_cell, "button-release-event", G_CALLBACK (launch_popup_signal), signal_data, (GClosureNotify)free, 0); /* Connect the callback to the signal such that after data is used, it is freed */
}

void create_track_context_menu(ViewContext *view_context, TrackState *track_state, GdkEvent *event) {
    /* Creates the popup menu when track is right clicked
     * Contains functionalities to 
     *  -> Delete track
     *  -> etc.
    */

    // Declare
    GtkWidget *context_menu;
    /* Menu buttons */
    GtkWidget *delete_track_button;

    // Create
    context_menu = gtk_menu_new(); /* Create the menu that'll be launched on popup */
    /* Buttons */
    delete_track_button = gtk_menu_item_new_with_label("Poonchy Toonchy Guinea Pig"); /* For now, just testing */

    // Format
    gtk_menu_set_title(GTK_MENU (context_menu), track_state->track->name); /* Set the title of the menu */

    // Connect
    
    // Pack
    gtk_menu_attach(GTK_MENU (context_menu), delete_track_button, 0, 0, 1, 1); /* Add the button to the context menu */

    // Do
    gtk_menu_popup_at_pointer(GTK_MENU (context_menu), event); /* Open the menu */
}
