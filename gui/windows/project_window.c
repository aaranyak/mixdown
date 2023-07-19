/* gui/windows/project_window.c
 * Contains functions for creating main window at startup
*/
// Author - Aaranyak Ghosh
#include <gtk/gtk.h>
#include <string.h>
#include "../tracks_view/tracks_view.h"
#include "../../project/project.h"
#include "../../resources.h"

void open_project_window(GtkApplication *app, Project *current_project)
{
    /* open_project_window(GtkApplication *app, Project *current_project)
     * Opens MixDown Project Window 
     */
    GtkWidget *window;
    char title[10 + strlen(current_project->name)]; /* Create string for title With the appropriate length */
    memset(title, 0, (10 + strlen(current_project->name)) * sizeof(char)); /* Clear string array */
    strcat(title, "MixDown - "); /* Title - "MixDown - <filename>  */
    strcat(title, current_project->name); /* Add filename to title */
    window = gtk_application_window_new(app); /* Create the window object */
    gtk_window_set_title(GTK_WINDOW (window), title); /* Set window title */
    gtk_window_set_default_size(GTK_WINDOW (window), 1400, 800); /* Set window size to 800x500 px */
    gtk_window_set_default_icon(gdk_pixbuf_new_from_inline(-1, app_icon, 0, 0)); /* Add the icon image from a resource */
    GtkWidget *content = tracks_view(current_project); /* Initialize the window content with the tracks view */
    gtk_container_add(GTK_CONTAINER (window), content); /* Add the content to the window */
    gtk_widget_show_all(window); /* Display Window */
}
