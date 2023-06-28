/* regions.h
 * Contains definition for the region object
*/
// Author - Aaranyak Ghosh

#ifndef REGIONS_H
#define REGIONS_H
#include "utils.h"
/* The region system
 *  -> Each track will include a linked list of regions.
 *  -> These regions are audio data of a specified length
 *  -> The linked list will be in order of start position
 *  -> Each region will contain a length of audio data, which may be different from the length of the region itself
 *  -> The track data in the view_context will contain the position of the currently playing region, and will slowly traverse the linked list as the playhead moves forward
 *  -> A region can be moved behind the previous one, or ahead the one it's before, but the list will have to be reordered this happens
 */
typedef struct Region Region; /* Forward declaration */
typedef struct Region {
    /* For moving */
    Region *prev; /* Pointer to previous region (in linked list) */
    Region *next; /* Pointer to next reguion (in linked list) */
    /* Length & Position */
    int audio_length; /* Length of the actual audio data */
    int position; /* Position of the region in the track */
    int region_length; /* Actual length of region */
    int audio_start; /* Where to start playing the audio data */
    /* Actual data */
    short *left; /* Left and */
    short *right; /* Right channels for stereo region */
} Region;
#endif
