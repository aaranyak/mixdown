/* gui/tracks_view/tracks_view.c
 * Contains functions for creating main window at startup
*/
// Author - Aaranyak Ghosh
#include <gtk/gtk.h>
#include <string.h>
#include "../../project/project.h"
GtkWidget *tracks_view(Project *current_project) {
    /* This will return the main view when a project is opened
     * The view will contain:
     *   - The tracks editor in the center
     *   - The sidebar will contain the track names and volume controls
     *   - The top bar will have play/pause buttons, and some basic settings
     */
    GtkWidget *view_container; /* Contains the entire tracks view */
    GtkWidget *placeholder;
    view_container = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0); /* Create Side Panes */
    
    return view_container;
}
