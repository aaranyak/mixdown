/* editor.c */
#include <gtk/gtk.h>
#include "../../../project/project.h"
#include "../view_context/view_context.h"
#include "track_editor.h"
#include "region_editor.h"
#include "../../components/components.h"
// Author - Aaranyak Ghosh

GtkWidget *tracks_editor(ViewContext *view_context) {
    /* Returns the widget for the track editor */
    // Declare Widgets
    GtkWidget *editor_scroller;
    GtkWidget *editor;
    GtkWidget *track_editor;
    GtkWidget *region_editor;
    // Some simple inner widgets
    GtkWidget *add_track_button;

    // Create Widgets
    editor_scroller = gtk_scrolled_window_new(0,0); /* The view should scroll vertically */
    editor = gtk_paned_new(GTK_ORIENTATION_HORIZONTAL); /* Create side-pane view for tracks */
    track_editor = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0); /* Left side frame */
    region_editor = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0); /* Right side frame */
    
    add_track_button = create_add_track_button(view_context); /* The button to add a new track */ 

    // Format widgets
    load_track_editor(view_context, &track_editor); /* Load tracks into track editor */
    load_region_editor(view_context, &region_editor); /* Load region editor rows into the editor */
    gtk_widget_set_size_request(track_editor, 300, -1); /* Set minimum size of the left side widget */
    
    // Connect Signals
    view_context->track_editor = track_editor; /* Connect the track editor widget to the view context */    
    view_context->region_editor = region_editor; /* Connect the region editor widget to the view context */ 
    // Pack Widgets
    gtk_box_pack_end(GTK_BOX (track_editor), add_track_button, 0, 0, 20 /* 20px padding */); /* Pack the add track button below all tracks */   
    gtk_paned_pack1(GTK_PANED (editor), track_editor, 0, 0);
    gtk_paned_pack2(GTK_PANED (editor), region_editor, 1 /* Will expand */, 0);
    gtk_container_add(GTK_CONTAINER (editor_scroller), editor); /* Add the editor to the scroller */
    return editor_scroller;
}
