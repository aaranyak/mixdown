/* Contains the function to create the track editor (In the tracks view) */
// Author - Aaranyak Ghosh
#include <gtk/gtk.h>
#include "../../../project/project.h"
#include "../view_context/view_context.h"
#include "track_editor.h"
// Author - Aaranyak Ghosh

GtkWidget *tracks_editor(ViewContext *view_context) {
    /* Returns the widget for the track editor */
    // Declare Widgets
    GtkWidget *editor;
    GtkWidget *track_editor;
    GtkWidget *region_editor;
    
    // Create Widgets
    editor = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL); /* Create side-pane view for tracks */
    track_editor = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0); /* Left side frame */
    region_editor = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0); /* Right side frame */
    
    // Format widgets
    load_track_editor(view_context, &track_editor); /* Load tracks into track editor */
    gtk_widget_set_size_request(track_editor, 300, -1); /* Set minimum size of the left side widget */
    
    // Pack Widgets
    gtk_paned_pack1(GTK_PANED (editor), track_editor, 0, 0);
    gtk_paned_pack2(GTK_PANED (editor), region_editor, 1 /* Will expand */, 0);
    return editor;
}
