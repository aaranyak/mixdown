/* create_new_track.c
 * Contains the function to create a new track on the tracks editor
*/
// Author - Aaranyak Ghosh

#include <gtk/gtk.h>
#include "../../view_context/view_context.h"
#include "../../../theme/theme.h"
#include "../../../../project/project.h"
#include "../track_editor.h"
#include "../region_editor.h"

TrackState *create_new_track(ViewContext *view_context, char name[], TrackType type) {
    /* Creates the Track, TrackState, and the gui for a new track */
    // Declare variables
    Track *track; /* The track object */
    TrackState *track_state; /* The track state */
    GtkWidget *track_cell; /* Track cell widget */
    GtkWidget *editor_row; /* Region editor row widget */
    GtkWidget *separator; /* Separates two tracks (if necessary) */
    // Default values
    float volume = 0.75f; /* Default volume */
    float pan = 0.5f; /* Default track pan */
    int odd_even = get_num_track_states(view_context->tracks) & 1; /* Check if odd track or even track */
    // Create Track object
    track = add_track(view_context->project, name, type, volume, pan); /* Create the track object in the project */
    // Create TrackState
    TrackState *last_track_state = get_last_track_state(view_context->tracks); /* Get the last track state */
    track_state = add_track_state(view_context, last_track_state, track); /* Create the track state manager, and add it to the view context */
    if (!last_track_state) view_context->tracks = track_state; /* If this is the first track, start the chain */
    
    // Create GUI Components
    track_cell = create_track_cell(view_context, track_state); /* Create the track cell widget */
    editor_row = create_editor_row(view_context, track_state, odd_even); /* Create the track editor row */
    separator = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL); /* Create the separator */ 
    // Pack Widgets
    if (track_state->prev) gtk_box_pack_start(GTK_BOX(view_context->track_editor), separator, 0, 0, 0); /* If this is a track in the middle, pack in the separator before the track */
    gtk_box_pack_start(GTK_BOX(view_context->track_editor), track_cell, 0, 0, 0); /* Pack the track cell into the tracks editor */
    gtk_box_pack_start(GTK_BOX(view_context->region_editor), editor_row, 0, 0, 0); /* Pack the editor row into the region editor */
    // Connect Widgets
    track_state->track_cell = track_cell; /* Connect the track cell widget to the state manager (needed for removing the track) */
    // Update Widgets
    gtk_widget_show_all(view_context->track_editor); /* Redraw the tracks cells panel to update it */
    gtk_widget_show_all(view_context->region_editor); /* Redraw the region editor to update it */
    return track_state;
}
