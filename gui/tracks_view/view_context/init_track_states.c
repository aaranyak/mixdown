/* init_track_state.c
 * Contains function to create the track state objects in the view_context.
*/
// Author - Aaranyak
#include "view_context.h"
#include <stdlib.h>
#include <gtk/gtk.h>

void link_adj_to_float(GtkAdjustment *value, float *link) {
    /* Link a float to an adjustment, so it changes with the adjustment */
    *link = (float)gtk_adjustment_get_value(value); /* Update the value of the linked field */
}

TrackState *add_track_state(ViewContext *view_context, TrackState *prev, Track *track) {
    /* Creates a trackstate object and adds it to the viewcontext */
    TrackState *track_state = (TrackState*)malloc(sizeof(TrackState)); /* Create trackstate object */
    track_state->prev = prev; /* Previous item */
    if (prev) prev->next = track_state; /* Add it to linked list */
    track_state->next = 0;
    track_state->track = track; /* Link to original track */
    // Set properties.
    track_state->volume = gtk_adjustment_new(track->volume, 0.0, 1.0, 0, 1, 0); /* Create the volume adjustment, that holds the volume and handles updates */
    track_state->pan = gtk_adjustment_new(track->pan, 0.0, 1.0, 0, 1, 0); /* Create the pan adjustmen, that holds the pan and handles updates */
    // Booleans
    /* You know what? just deal with that later */
    track_state->mute = gtk_adjustment_new(track->mute, 0, 1, 1, 0, 0); /* Can either be 0 or 1, and is for holding a universal value */
    
    // Connect properties
    g_signal_connect(track_state->volume, "value-changed", G_CALLBACK(link_adj_to_float), &(track->volume)); /* Link the track state volume to the pointer to the actual track volume */
    g_signal_connect(track_state->pan, "value-changed", G_CALLBACK(link_adj_to_float), &(track->pan)); /* Link the track state pan to the pointer to the actual track pan */

    return track_state;
}

void init_track_states(ViewContext *view_context) {
    /* Create all state managers for tracks in a project */
    Project *project = view_context->project;
    if (project->tracks) {     
        view_context->tracks = add_track_state(view_context, 0, project->tracks); /* Manually create the first track */
        // Loop through all the tracks in the list
        Track *current_track = project->tracks->next;
        TrackState *previous_track = view_context->tracks;
        while (current_track) {
            previous_track = add_track_state(view_context, previous_track, current_track); /* Add a new track context */
            current_track = current_track->next; /* Move on the the next track */
        }
    }
}

void free_track_states(ViewContext *view_context) {
    /* Frees track state memory */
    TrackState *item = view_context->tracks; /* Current item in list */
    while (item) { /* If the list is not empty */
        TrackState *next_item = item->next;
        free(item);
        item = next_item;
    }
}

