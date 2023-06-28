/* tracks.h
 * Contains definition of struct Track
 */
// Author - Aaranyak Ghosh

#ifndef TRACKS_H /* Header Guard */
#define TRACKS_H

#include "utils.h"
#include "regions.h"
/* A note on tracks 
 * Tracks in a project are stored in a linked list, every track pointing to the next in line.
 *  -> This method is used, rather than a pointer array, since reordering of tracks in this format is simpler
 *  -> This will be used currently, because in no forseen circumstance will we need to immedeatly lookup a track by it's position in the list.
 *  -> The "Track *tracks;" property will be a pointer to the first track in the linked list.
 *  -> The "Track *master;" will be a pointer to the master track, which will provide audio output.
*/
/* Is freeing memory during clean up really nessecary? Research on this. */

/* The region system
 *  -> Each track will include a linked list of regions.
 *  -> These regions are audio data of a specified length
 *  -> The linked list will be in order of start position
 *  -> Each region will contain a length of audio data, which may be different from the length of the region itself
 *  -> The track data in the view_context will contain the position of the currently playing region, and will slowly traverse the linked list as the playhead moves forward
 *  -> A region can be moved behind the previous one, or ahead the one it's before, but the list will have to be reordered this happens
 */
typedef struct Track Track; /* Forward declaration */
typedef struct Track {
    // Essentials
    char name[128]; /* Track name is not a pointer, to save memory cleanup */
    Track *prev; /* Pointer to previous track in list (Null if beginning of list) */
    Track *next; /* Pointer to next track (Null if end) */
    TrackType type; /* audio/midi/mix track (midi will probably not be implemented in this version) */
    Region *regions; /* Linked list of regions */
    // Track Settings
    float volume;
    float pan;
    // Booleans:
    char mute;
    char solo;
    char record;
    // Add other stuff here:
} Track;
#include "track_utils.h"
#endif
