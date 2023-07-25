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

void link_adj_to_bool(GtkAdjustment *value, char *link) {
    /* Link a float to an adjustment, so it changes with the adjustment */
    *link = (char)gtk_adjustment_get_value(value); /* Update the value of the linked field */
}

TrackState *get_last_track_state(TrackState *linked_list) {
    /* Returns the list item in a linked list of track states */
    TrackState *item = linked_list; /* Current item in linked list */
    while (item) { /* If list is not empty (why not, easier than if(item) while(1)) */
        if (!item->next) { /* If reached end of list */
            break;
        }
        item = item->next; /* Move on to next item in list */
    }
    return item;
}

int get_num_track_states(TrackState *linked_list) {
    /* Returns the number of tracks in a linked list */
    TrackState *item = linked_list; /* Current item in linked list */
    int num_tracks = 0; /* Number of tracks */
    while (item) { /* Loop through elements in list */
        num_tracks++;
        item = item->next; /* Move on to next item in list */
    }
    return num_tracks;
}

TrackState *add_track_state(ViewContext *view_context, TrackState *prev, Track *track) {
    /* Creates a trackstate object and adds it to the viewcontext */
    TrackState *track_state = (TrackState*)malloc(sizeof(TrackState)); /* Create trackstate object */
    track_state->prev = prev; /* Previous item */
    if (prev) prev->next = track_state; /* Add it to linked list */
    track_state->next = 0;
    track_state->track = track; /* Link to original track */
    
    // Links to GUI components.
    track_state->region_editor = 0; /* For now, just set them to a null pointer */
    track_state->track_cell = 0; /* Ditto */

    // Set properties.
    track_state->volume = gtk_adjustment_new(track->volume, 0.0, 1.0, 0, 0.1, 0); /* Create the volume adjustment, that holds the volume and handles updates */
    track_state->pan = gtk_adjustment_new(track->pan, 0.0, 1.0, 0, 0.1, 0); /* Create the pan adjustmen, that holds the pan and handles updates */
    // Booleans
    track_state->mute = gtk_adjustment_new(track->mute, 0, 1, 1, 0, 0); /* Can either be 0 or 1, and is for holding a universal value */
    track_state->solo = gtk_adjustment_new(track->solo, 0, 1, 1, 0, 0); /* Can either be 0 or 1, and is for holding a universal value */
    track_state->record = gtk_adjustment_new(track->record, 0, 1, 1, 0, 0); /* Can either be 0 or 1, and is for holding a universal value */
     
    // Connect properties
    g_signal_connect(track_state->volume, "value-changed", G_CALLBACK(link_adj_to_float), &(track->volume)); /* Link the track state volume to the pointer to the actual track volume */
    g_signal_connect(track_state->pan, "value-changed", G_CALLBACK(link_adj_to_float), &(track->pan)); /* Link the track state pan to the pointer to the actual track pan */
    // Connect Booleans
    g_signal_connect(track_state->mute, "value-changed", G_CALLBACK(link_adj_to_bool), &(track->mute)); /* Will change the value of the original is_muted in the track in the project */
    g_signal_connect(track_state->solo, "value-changed", G_CALLBACK(link_adj_to_bool), &(track->solo)); /* Same as above */
    g_signal_connect(track_state->record, "value-changed", G_CALLBACK(link_adj_to_bool), &(track->record)); 
     
    // Connect the track state to the track
    track->state_manager = track_state;
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

void delete_track_state(ViewContext *view_context, TrackState *track_state) {
    /* Deletes a trackstate from the view context */
    // update the previous track state
    // Remove from linked list
    if (track_state->prev) track_state->prev->next = track_state->next; /* If this is not the first track, update the previous track in linked list */
    else view_context->tracks = track_state->next; /* Otherwise, update the view context */
    if (track_state->next) track_state->next->prev = track_state->prev; /* If not the last track, update the next track in list */
    free(track_state); /* Free the track state memory */
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

