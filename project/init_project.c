/* init_project.c
 * void init_project(Project *project); Is the function that will initialize an empty project.
 * This function will fill in the project with default values.
 * free_project(Project *project) will have to be called to free the project memory
*/
// Author: Aaranyak Ghosh
#include "project.h"
#include <stdlib.h>

void init_project(Project *project) {
    /* Initializes empty project and sets to default values */
    char *name = "untitled_1.mdp";
    project->name = name;
    project->path = 0; /* Path is currently null pointer (not saved) */
    // Project Settings:
    TimeSignature time_signature = {4, 4}; /* Default time_signature = 4/4 */
    project->project_settings.tempo = 120; /* Default tempo = 120 bpm */
    project->project_settings.time_signature = time_signature; 
    project->project_settings.length = 705600; /* 8 bars. total 120 bpm = 2 beats/second. 44100 samples/second = 22050 samples/beat. 4 beats/bar = 32 bars/song = 705600 samples/song */
    
    // Audio Settings (Advanced Settings)
    AudioSettings audio_settings; /* Temporary Object */
    audio_settings.sample_rate = 44100; /* 44,100Hz */
    audio_settings.comp_unit = 2450; /* 9 computations/beat */
    audio_settings.period_count = 1; /* Two hardware interrupts per count */
    audio_settings.use_gpu = 0; /* By default, cpu is used. Gpu not yet implemented */
    project->project_settings.audio_settings = audio_settings; /* Set audio settings */
    
    // Initialize tracks.
    Track *master = add_track(project, "Master", MIX_TRACK, 0.75  /* Volume */, 0.5 /* Pan */); /* Create a track */
    Track *track1 = add_track(project, "Drums - Amu", AUDIO_TRACK, 0.7 /* Volume */, 0.5 /* Pan */); /* Create another track */
    Track *track2 = add_track(project, "Lead Guitar - Aaranyak", AUDIO_TRACK, 0.8 /* Volume */, 0.5 /* Pan */); /* Create another track */
    Track *track3 = add_track(project, "Rythm Guitar - Aaranyak", AUDIO_TRACK, 0.6 /* Volume */, 0.5 /* Pan */); /* Create another track */
    Track *track4 = add_track(project, "Bass - Aaranyak", AUDIO_TRACK, 0.5 /* Volume */, 0.5 /* Pan */); /* Create another track */
    
    project->master = master; /* Set the first track to master */
}

void free_project(Project *project) {
    /* Freeing project memory at exit is not required (but supposedly a good practice), but will be required when opening/creating a new project */
    free_tracks(project); /* Free track memory */
} 

