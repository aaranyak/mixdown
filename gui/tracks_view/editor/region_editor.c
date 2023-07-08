/* Contains the function to create the track editor (In the tracks view) */
// Author - Aaranyak Ghosh
#include <gtk/gtk.h>
#include <string.h>
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
    }
    return 0;
}

GtkWidget *create_editor_row(ViewContext *view_context, TrackState *track_state, char odd_even) {
    /* Loads the editor row for a single track 
     * This will be a scrollable (scroll I will implement, not gtk) view, where you will be able to
     *  -> Edit regions
     *  -> Move regions
     *  -> Cut regions
     *  -> Resize regions
     * Etc.
    */
    
    // Declare Widgets
    
    GtkWidget *editor_row; /* The container for the editor. This will be an overlay widget (to stack widgets on top of each other) */
    GtkWidget *editor_background; /* Bar ticks and beat ticks */
    GtkWidget *regions; /* Figure this out later */
    // Simple Calculations
    
    // Create Widgets
    editor_row = gtk_overlay_new(); /* An overlay, for stacking widgets on top of each other */

    editor_background = region_editor_background(view_context, odd_even); /* For now, instead of handling the overlay, just use the background */
    // Format widgets
    gtk_widget_set_size_request(editor_row, -1, 110); /* Size the widget */
    
    // Connect Signals
    gtk_widget_add_events(editor_background, GDK_SCROLL_MASK); /* Add the scroll event listener (I guess) */
    g_signal_connect(editor_background, "scroll-event", G_CALLBACK(scroll_regions), view_context); /* Connect the scroll handler to the editor row */

    // Pack Widgets
    gtk_container_add(GTK_CONTAINER(editor_row), editor_background); /* Add the background as the first child of the overlay */

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

