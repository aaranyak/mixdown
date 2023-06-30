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
#include "../view_context/view_context.h" /* This contains the state manager widget */
#include "../../../project/project.h" /* Contains project and track definitions */
#include "../../theme/theme.h" /* background and foreground colours */
#include "string.h"
GtkWidget *create_track_cell(ViewContext *view_context, TrackState *track_state) {
    /* Returns the track cell widget which has all the controls */
    
    // Declare Widgets
    
    // Containers
    GtkWidget *cell; /* Container for everything */
    GtkWidget *top_row; /* Contains label */
    GtkWidget *bottom_row; /* Contains volume control, etc */
    
    //Items
    GtkWidget *label; /* Label Text */
    GtkWidget *volume_slider; /* Connected to the volume adjustment */
    // Well, that's about it for now, we'll do the rest later.
    
    // Create Widgets
    cell = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0); /* Add a little bit of padding */
    top_row = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0); /* Also useful for sizing label */
    bottom_row = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0); /* We'll add more widgets here once we have decided what we'll put here */
    
    char label_text[128];
    if (track_state->track->type == MIX_TRACK) sprintf(label_text, "%s (Mix)", track_state->track->name); /* If this is a mix track, add (Mix) to the label */
    else sprintf(label_text, track_state->track->name); /* Otherwise, set it to just the name */
    label = gtk_label_new(label_text); /* Label text will be the name of the track */
    volume_slider = gtk_scale_new(GTK_ORIENTATION_HORIZONTAL, track_state->volume); /* Create a volume slider. The adjustment is holds the value, that is stored in the track state */

    // Style & Size widgets
    // Sizing
    gtk_widget_set_size_request(cell, -1, 100); /* 100px tall */
    gtk_widget_set_size_request(volume_slider, -1, -1); /* Use maximum size */
    // Styling
    if (track_state->track->type == MIX_TRACK) bg_colour_track_mix(&cell, GTK_STATE_FLAG_NORMAL); /* Set the cell to mix track colour, if it is a mix track */
    else bg_colour_track(&cell, GTK_STATE_FLAG_NORMAL); /* Otherwise, set to normal track colou */
    set_def_font(&label); /* Set font of label to default theme (Ubuntu) */
    
    gtk_scale_set_digits(GTK_SCALE(volume_slider), 4); /* Rounded off to four decimal places */
    gtk_scale_set_draw_value(GTK_SCALE(volume_slider), 0); /* Do not display volume value */
    // Pack Widgets
    gtk_box_pack_start(GTK_BOX(top_row), label, 0, 0, 10 /* 10px padding */); /* Pack the label into the top row */
    gtk_box_pack_start(GTK_BOX(cell), top_row, 0, 0, 10 /* Ditto */); /* Pack the top row into the cell */
    
    gtk_box_pack_start(GTK_BOX(bottom_row), volume_slider, 1, 1 /* Use maxium size */, 20 /* 20px padding */); /* Pack the volume slider into the bottom row */
    gtk_box_pack_end(GTK_BOX(cell), bottom_row, 0, 0, 10 /* 20px padding */); /* Pack the bottom row into the cell */

    return cell;
}

void *load_track_editor(ViewContext *view_context, GtkWidget **track_editor) {
    /* Work on this till 6:30 then remember to go cycling for atleast 1:30 hours */
    /* This will load all the track data from the project and display them as track editing cells.
     * The GtkWidget **track_editor will be the parent widget of the tracks.
     *
     * The properties of the track controllers are in the track state, so if the controls are displayed in multiple places, the value will be universal
     * The values are updated automatically.
    */
    GtkWidget *current_separator; /* Separator between tracks */
    TrackState *track_state = view_context->tracks; /* Current track in linked list */
    while (track_state) { /* Loop through all tracks */
        // Declare widgets
        GtkWidget *track_cell; /* The track controls cell */
        // Create Widgets
        track_cell = create_track_cell(view_context, track_state); /* Load the track cell gui */
        current_separator = gtk_separator_new(GTK_ORIENTATION_HORIZONTAL); /* Create a separator between cells */
        // Pack Widgets
        gtk_box_pack_start(GTK_BOX(*track_editor), track_cell, 0, 0, 0); /* Pack the track cell into the editor */
        if (track_state->next) gtk_box_pack_start(GTK_BOX(*track_editor), current_separator, 0, 0, 0); /* Pack the separator into the editor */
        // Move on to next track
        track_state = track_state->next;
    }
}
