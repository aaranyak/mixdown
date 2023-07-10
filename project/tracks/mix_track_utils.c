/* track_utils.c
 * Contains the function to add a track to the mix list of a mix track.
*/
// Author - Aaranyak Ghosh
#include <stdlib.h>
#include "tracks.h"
#include "../project.h"
#include <string.h>

void add_track_to_mix(Track *mix_track, Track *track) {
    /* Adds a track (of any type) to the mix list of a mix track */
    
    if (mix_track->num_tracks) {
        /* If the mix list contains tracks */
        mix_track->num_tracks++; /* Increment the number of tracks */
        // Increase the memory required to fit the new track
        mix_track->mix_tracks = /* Put the new memory back in the old pointer */ (Track**) /* cast from void* to an array of pointers to tracks */realloc(mix_track->mix_tracks /* Must copy the old data into the new */, sizeof(Track*) * mix_track->num_tracks /* The new memory is the size of a pointer to a track multiplied by the new number of tracks */);
        mix_track->mix_tracks[mix_track->num_tracks-1] = track; /* Add the new track as the last track in the list */
    }
    else {
        /* If the mix list is empty */
        mix_track->num_tracks = 1; /* Set the number of tracks */
        mix_track->mix_tracks = (Track**)malloc(sizeof(Track*)); /* Create the mix list */
        mix_track->mix_tracks[0] = track; /* Add the pointer to the track to the mix list */
    }
}
