/* track_utils.c
 * contains function to add a track to the track list.
*/
// Author - Aaranyak Ghosh
#include <stdlib.h>
#include "tracks.h"
#include "../project.h"
#include <string.h>
Track *get_last_track(Track *linked_list) {
    /* Get the last item of a linked list of tracks. (return null pointer if empty ) */
    Track *item = linked_list; /* Current item in list */
    while (item) { /* If the list is not empty */
        if (!item->next) { /* If reached end of list */
            break; /* Go out of list */
        }
        item = item->next; /* Move to next item in list */
    }
    return item;
}
Track *add_track(Project *project,
                 char name[128],
                 TrackType type,
                 float volume,
                 float pan) 
{
    /* Adds a new track to the project.
     *  -> char name[] - Name of the track (cannot exceed 127 characters)
     *  -> float volume - Volume of track (between 1 and 0
     *  -> float pan - Track pan (between 0 and 1)
    */

    Track *last_item = get_last_track(project->tracks); /* Get last track in the list, so that insertion can be done */
    
    // Create track
    Track *track = (Track*)malloc(sizeof(Track)); /* Allocate memory for the track in the heap */
    
    // Set track parameters
    strcpy(track->name, name); /* Copy name into track */
    track->volume = volume;
    track->pan = pan;
    track->type = type;
    
    // Set Other params to default values
    track->prev = last_item; /* Previous item to this track will be the last track in list */
    track->next = 0; /* Since this is the last list, next will be null pointer */
    track->mute = 0;
    track->solo = 0;
    track->record = 0;
    track->regions = 0; /* Track is created empty (no regions) */
    
    // For mix tracks only
    if (type == MIX_TRACK) {
        track->num_tracks = 0; /* Set number of tracks to mix to 0 */
        track->mix_tracks = 0; /* No tracks added to mix yet */
    }
    // Insert track in list
    if (last_item) { /* If list is not empty */
        last_item->next = track; /* Insert track after last item */
    } else {
        project->tracks = track; /* Otherwise, put it at start */
    }
    return track;
}

void delete_track(Project *project, Track *track) {
    /* Deletes a track from a project, and frees the track's memory */
    // Update the previoous track in the chain
    if (track->prev) {
        track->prev->next = track->next; /* Clear the link from the previous track in the chain, and sets it to then next */
    } else {
        project->tracks = track->next; /* If ths is the first track, the project's first track link is pushed up */
    }
    // Update the next track in the chain
    if (track->next) track->next->prev = track->prev; /* Sets the previous track of the next track in the chain to this track's previous, thereby removing the track entirely from the chain */
    // Free memory
    free(track); /* Let's try this and see if it works */
}

void free_tracks(Project *project) {
    /* Frees track memory */
    Track *item = project->tracks; /* Current item in list */
    while (item) { /* If the list is not empty */
        Track *next_item = item->next;
        if (item->type == MIX_TRACK) if (item->num_tracks) free(item->mix_tracks); /* Free the mix list if it is not empty and if track is mix track */
        free(item);
        item = next_item;
    }
}
