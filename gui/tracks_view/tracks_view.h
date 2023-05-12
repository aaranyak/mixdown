/* gui/tracks_view/tracks_view.h
 *Header file for tracks_view.c
*/
// Author - Aaranyak Ghosh
#ifndef TRACKSVIEW_H
#define TRACKSVIEW_H
#include <gtk/gtk.h>
#include <string.h>
#include "../../project/project.h"
GtkWidget *tracks_view(Project *current_project);
/* This will return the main view when a project is opened
 * The view will contain:
 *   - The tracks editor in the center
 *   - The sidebar will contain the track names and volume controls
 *   - The top bar will have play/pause buttons, and some basic settings
 */
#endif