/* gui/windows/project_window.h
 * Header file for creating window at startup
*/
// Author - Aaranyak Ghosh
#ifndef PROJECTWINDOW_H /* Header guard */
#define PROJECTWINDOW_H
#include <gtk/gtk.h>
#include <string.h>
#include "../tracks_view/tracks_view.h"
#include "../../project/project.h"

void open_project_window(GtkApplication *app, Project *current_project); /* Opens Mixdown Project Window */
#endif