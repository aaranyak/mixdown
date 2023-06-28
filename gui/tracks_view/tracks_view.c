/* gui/tracks_view/tracks_view.c
 * Contains functions for creating main window at startup
*/
// Author - Aaranyak Ghosh
#include <gtk/gtk.h>
#include <string.h>
#include "../../project/project.h"
#include "view_context/view_context.h"
#include "view_context/initialize_context.h"
#include "control_panel.h"
#include "editor/editor.h"

static ViewContext view_context; /* State of the tracks view */

GtkWidget *tracks_view(Project *current_project) {
    /* This will return the main view when a project is opened
     * The view will contain:
     *   - The tracks editor in the center
     *   - The sidebar will contain the track names and volume controls
     *   - The top bar will have play/pause buttons, and some basic settings
     */
    
    // Declare widgets
    GtkWidget *view_container; /* Contains the entire tracks view */
    GtkWidget *top_control_panel; /* Top panel widget */
    GtkWidget *editor;

    // Before loading view
    init_context(&view_context, current_project); /* Init tracks view state */ 
    
    // Load tracks view

    // Create view object
    view_container = gtk_box_new(GTK_ORIENTATION_VERTICAL /* Vertical packing */, 0); /* Create the container widget for the entire view */
    gtk_widget_set_size_request(view_container, 1050, 600); /* Set minimum size to 1050px/600px; ratio 7:4 */
    
    // Create widgets
    top_control_panel = control_panel(&view_context); /* Control panel with play/pause buttons etc. */
    editor = tracks_editor(&view_context); /* Create tracks editor */

    // Pack Widgets
    gtk_box_pack_start(GTK_BOX(view_container), top_control_panel, 0, 0, 0) /* Add the top control panel */;
    gtk_box_pack_start(GTK_BOX(view_container), editor, 1, 1, 0) /* Add the editor */;
     
    return view_container;
}
