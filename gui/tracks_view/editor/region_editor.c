/* Contains the function to create the track editor (In the tracks view) */
// Author - Aaranyak Ghosh
#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>
#include "track_editor.h"
#include "../view_context/view_context.h" /* This contains the state manager widget */
#include "../../components/components.h" /* Contains small but useful gui components */
#include "../../../project/project.h" /* Contains project and track definitions */
#include "../../theme/theme.h" /* background and foreground colours */

gboolean scroll_regions(GtkOverlay *editor_row, GdkEventScroll *event, ViewContext *view_context) {
    /* Handles scrolling on the region editor. (Will handle side-scroll and zoom) */
    // Handle side-scrolling
    if (event->state & GDK_SHIFT_MASK) {
        /* Shift+Scroll - side scrolling */
        int scroll_length = view_context->project->project_settings.audio_settings.comp_unit; /* Scroll length (in normal situations) */
        if (event->state & GDK_CONTROL_MASK) scroll_length *= 4; /* if control is also pressed, scroll faster */
        if (event->direction) {
            /* Scroll forward */
            int scroll = gtk_adjustment_get_value(view_context->scroll); /* Get current scroll value */
            scroll += scroll_length; /* Scroll forward by the comp-unit size */
            gtk_adjustment_set_value(view_context->scroll, scroll); /* Set the scroll */
        }
        else {
            /* Scroll backward */
            int scroll = gtk_adjustment_get_value(view_context->scroll); /* Get current scroll value */
            scroll -= scroll_length; /* Scroll backward by the comp-unit size */
            gtk_adjustment_set_value(view_context->scroll, scroll); /* Set the scroll */
        }
        return 1;
    }

    // Handle Zooming
    else if (event->state & GDK_CONTROL_MASK) {
        /* Control+Scroll - Zooming */
        int zoom_amount = view_context->project->project_settings.audio_settings.comp_unit / 24; /* Zoom Amount (in normal situations) */
        if (event->direction) {
            /* Zoom out */
            int zoom = gtk_adjustment_get_value(view_context->scale); /* Get current zoom value */
            zoom += zoom_amount;
            gtk_adjustment_set_value(view_context->scale, zoom); /* Set the zoom */
        }
        else {
            /* Zoom out */
            int zoom = gtk_adjustment_get_value(view_context->scale); /* Get current zoom value */
            zoom -= zoom_amount;
            gtk_adjustment_set_value(view_context->scale, zoom); /* Set the zoom */
        }
        return 1;
    }
    return 0;
}

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

GtkWidget *create_editor_row(ViewContext *view_context, TrackState *track_state, char odd_even) {
    /* Loads the editor row for a single track 
     * This will be a scrollable (scroll I will implement, not gtk) view, where you will be able to
     *  -> Edit regions
     *  -> Move regions
     *  -> Cut regions
     *  -> Resize regions
     * Etc.
     Mix tracks, on the other hand will display a row of track cells, which are it's tracks to mix.
    */
    
    // Declare Widgets
    
    GtkWidget *editor_row; /* The container for the editor. This will be an overlay widget (to stack widgets on top of each other) */
    GtkWidget *editor_background; /* Bar ticks and beat ticks */
    GtkWidget *mix_editor_row; /* If this is a mix track, handle it this way */
    GtkWidget *mix_scroller; /* For mix tracks, this will scroll the mix track behind stuff, etc. */
    GtkWidget *regions; /* Figure this out later */
    // Simple Calculations
    GtkAdjustment *scroller_adjustment = gtk_adjustment_new(0, 0, 0, 1, 1, 0); /* Honestly, these values don't matter */

    // Create Widgets
    editor_row = gtk_overlay_new(); /* An overlay, for stacking widgets on top of each other */
    editor_background = region_editor_background(view_context, odd_even); /* For now, instead of handling the overlay, just use the background */
    
    // Logic for if the track is a mix track.
    if (track_state->track->type == MIX_TRACK) {
        /* If the track is a mix track, the editor row will display track cells, corresponding to it's tracks to mix */
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
        gtk_layout_put(GTK_LAYOUT(mix_scroller), mix_editor_row,0,0); /* Add the mix editor row to the scrollable clippable view */
        gtk_widget_set_size_request(mix_scroller, -1, 110); /* Size the scroller */
    }

    // Format widgets
    gtk_widget_set_size_request(editor_row, -1, 110); /* Size the widget */
    
    // Connect Signals
    if (track_state->track->type != MIX_TRACK) {
        gtk_widget_add_events(editor_background, GDK_SCROLL_MASK); /* Add the scroll event listener (I guess) */
        g_signal_connect(editor_background, "scroll-event", G_CALLBACK(scroll_regions), view_context); /* Connect the scroll handler to the editor row */
    } else {
        // Connect the scroll update signal
        struct mix_scroller_data *data = (struct mix_scroller_data*)malloc(sizeof(struct mix_scroller_data)); /* Allocate memory for the data */
        /* I hate using dynamic memory unless absolutely necessary */
        data->mix_scroller = GTK_LAYOUT(mix_scroller); data->view_context = view_context; data->cells = mix_editor_row;
        // The next line of code connects a signal with data, and then frees data memory afterwards (Recommended on stack overflow) */
        g_signal_connect_data(view_context->scroll, "value_changed", G_CALLBACK(update_mix_scroller), data, (GClosureNotify)free, 0); /* When scroll adjustment updates, scroll the mix scroller */
    }
    // Pack Widgets
    gtk_container_add(GTK_CONTAINER(editor_row), editor_background); /* Add the background as the first child of the overlay */
    if (track_state->track->type == MIX_TRACK) gtk_overlay_add_overlay(GTK_OVERLAY(editor_row), mix_scroller); /* If this is a mix track, add the mix cells to the editor row on top of the background */

    return editor_row;

}
void *load_region_editor(ViewContext *view_context, GtkWidget **region_editor) {
    /* This will load all the region data from the view context, and display them in rows.
    */
    GtkWidget *current_separator; /* Separator between tracks */
    TrackState *track_state = view_context->tracks; /* Current track in linked list */
    char colour_odd_even = 0; /* Wether the track is an odd track or an even track */
    while (track_state) { /* Loop through all tracks */
        // Declare widgets
        GtkWidget *editor_row; /* Region editor row */
        // Create Widgets
        editor_row = create_editor_row(view_context, track_state, colour_odd_even); /* Create the editor row, containing regions */
        // Pack Widgets
        gtk_box_pack_start(GTK_BOX(*region_editor), editor_row, 0, 0, 0); /* Pack in the editor row */
        // Move on to next track
        colour_odd_even = !colour_odd_even; /* Reverse the odd/even colours for the next track */
        track_state = track_state->next;
    }
}

