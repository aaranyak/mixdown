/* mix_editor_row.c
 * Contains functions to create the GUI for the mix editor row.
*/
// Author - Aaranyak Ghosh

#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include "track_editor.h"
#include "../view_context/view_context.h" /* This contains the state manager widget */
#include "../../components/components.h" /* Contains small but useful gui components */
#include "../../../project/project.h" /* Contains project and track definitions */
#include "../../theme/theme.h" /* background and foreground colours */

/* This is the only way to pass multiple fields of data, I know it is a bit wierd, but it works */
struct mix_scroller_data {
    /* Also, it's recommended on stackoverflow */
    GtkLayout *mix_scroller;
    GtkWidget *cells;
    ViewContext *view_context;
};

void update_mix_scroller(GtkAdjustment *scroll, struct mix_scroller_data *data /* Contains the view context and something else */) {
    /* Update function for mix track scrollers */
    int scroll_value = gtk_adjustment_get_value(scroll); /* Get the value of the scroll in samples */
    int scale_value = gtk_adjustment_get_value(data->view_context->scale); /* Get the zoom value */
    GtkLayout *mix_editor_scroll = data->mix_scroller; /* Get the scrolling widget */
    GtkWidget *mix_editor = data->cells; /* get mix editor */
    gtk_layout_move(mix_editor_scroll, mix_editor, -(scroll_value / scale_value), 0); /* Do the actual scrolling */

}

GtkWidget *create_mix_editor_row(ViewContext *view_context, TrackState *track_state) {
    /* On the editor rows, If th track is a Mix Track, the row will display all the tracks being mixed */

    // Declare Widgets
    GtkWidget *mix_editor_row; /* If this is a mix track, handle it this way */
    GtkWidget *mix_scroller; /* For mix tracks, this will scroll the mix track behind stuff, etc. */

    GtkAdjustment *scroller_adjustment = gtk_adjustment_new(0, 0, 0, 1, 1, 0); /* Honestly, these values don't matter */
    // Create Widgets
    mix_scroller = gtk_layout_new(scroller_adjustment,0); /* Create a new scrollable view for the stuff */
    mix_editor_row = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0); /* Create the container for the tracks. */

    // Load track cells
    // Declare
    TrackState *current_track_state; /* The track state of the track to mix */
    int index = 0; /* Index of the track to mix (in the mixer row) */
    // Loop through all the tracks in the mix track state */
    while (index < track_state->track->num_tracks) { /* While the current index is less than the number of tracks */
        // Declare
        GtkWidget *current_track_cell; /* The widget of the track to mix */
        GtkWidget *separator; /* Separate between track cells */
        // Create
        current_track_state = track_state->track->mix_tracks[index]->state_manager; /* Get the track state of the current mix track */
        current_track_cell = create_track_cell(view_context, current_track_state); /* Create the editor cell for the track to mix */
        separator = gtk_separator_new(GTK_ORIENTATION_VERTICAL); /* Add a vertical separator between tracks */
        // Format
        gtk_widget_set_size_request(current_track_cell, 0, 110); /* Set the height of the cell to 110px */
        // Pack
        gtk_box_pack_start(GTK_BOX(mix_editor_row), current_track_cell, 0, 0, 0); /* Pack the track cell into the mix editor row */
        gtk_box_pack_start(GTK_BOX(mix_editor_row), separator, 0, 0, 0); /* Pack the separator */

        index++; /* Move on to next track */
    }

    // Format Widgets
    gtk_widget_set_size_request(mix_scroller, -1, 110); /* Size the scroller */

    // Connect Signals
    struct mix_scroller_data *data = (struct mix_scroller_data*)malloc(sizeof(struct mix_scroller_data)); /* Allocate memory for the data */
    /* I hate using dynamic memory unless absolutely necessary */
    data->mix_scroller = GTK_LAYOUT(mix_scroller); data->view_context = view_context; data->cells = mix_editor_row;
    // The next line of code connects a signal with data, and then frees data memory afterwards (Recommended on stack overflow) */
    g_signal_connect_data(view_context->scroll, "value_changed", G_CALLBACK(update_mix_scroller), data, (GClosureNotify)free, 0); /* When scroll adjustment updates, scroll the mix scroller */
    
    // Pack Widgets
    gtk_layout_put(GTK_LAYOUT(mix_scroller), mix_editor_row,0,0); /* Add the mix editor row to the scrollable clippable view */
    
    return mix_scroller;
}
