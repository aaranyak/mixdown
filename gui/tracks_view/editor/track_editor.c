/* track_editor.c
 * This file contains functions to load the list of tracks on the side
 * Each track editor contains:
 *  -> Volume
 *  -> Pan
 *  -> Mute
 *  -> Solo
 *  -> Record
*/
#include <gtk/gtk.h>
#include "../view_context/view_context.h"
#include "../../../project/project.h"

GtkWidget *create_track_cell(ViewContext *view_context, TrackState *track_state) {
    /* Returns the track cell widget which hass all the controls */
    return gtk_label_new(track_state->track->name);
}

void *load_track_editor(ViewContext *view_context, GtkWidget **track_editor) {
    /* Work on this till 6:30 then remember to go cycling for atleast 1:30 hours */
    /* This will load all the track data from the project and display them as track editing cells.
     * The GtkWidget **track_editor will be the parent widget of the tracks.
     *
     * The properties of the track controllers are in the track state, so if the controls are displayed in multiple places, the value will be universal
     * The values are updated automatically.
    */
    
    TrackState *track_state = view_context->tracks; /* Current track in linked list */
    while (track_state) { /* Loop through all tracks */
        // Declare widgets
        GtkWidget *track_cell; /* The track controls cell */
        // Create Widgets
        track_cell = create_track_cell(view_context, track_state); /* Load the track cell gui */
        // Pack Widgets
        gtk_box_pack_start(GTK_BOX(*track_editor), track_cell, 0, 0, 0); /* Pack the track cell into the editor */
        // Move on to next track
        track_state = track_state->next;
    }
}
