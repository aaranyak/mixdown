/* project/project_settings/time_signature.h
 * Contains the struct for time signature. */
// Author - Aaranyak Ghosh

#ifndef TIMESIGNATURE_H /* Header Guard */
#define TIMESIGNATURE_H
/* TimeSignature object *
 * if beat = 4, and per_bar = 4, time signature = 4/4
 * If beat = 8, and per_bar = 6, time signature = 6/8
*/
typedef struct TimeSignature {
    int beat;
    int per_bar;
} TimeSignature;
#endif