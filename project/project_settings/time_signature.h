/* project/project_settings/time_signature.h
 * Contains the struct for time signature. */
// Author - Aaranyak Ghosh


/* TimeSignature object *
 * if beat = 4, and per_bar = 4, time signature = 4/4
 * If beat = 8, and per_bar = 6, time signature = 6/8
*/
typedef struct TimeSignature {
    int beat;
    int per_bar;
} TimeSignature ;

TimeSignature time_signature(int per_bar, int beat) {
    /* Create a time signature object */
    TimeSignature time;
    time.beat = beat;
    time.per_bar = per_bar;
    return time;
}

