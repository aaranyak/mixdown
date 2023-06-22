/* control_panel.c
 * Contains function for generating the control panel.
 * Control panel contains:
 *  -> Play/Pause/Record buttons
 *  -> Tempo setting
 *  -> Metronome
 *  -> Etc.
*/
// Author - Aaranyak Ghosh
#include <gtk/gtk.h>
#include <string.h>
#include "../../project/project.h"
#include "view_context/view_context.h"
#include "../theme/theme.h"
#include "../components/components.h"
GtkWidget *control_panel(ViewContext *view_context) {
    /* Function for generating the top control panel widget
     * Control panel will be located at the top of the tracks view
     * Control panel contains:
     *  -> Play/Pause/Record buttons
     *  -> Tempo setting
     *  -> Metronome
     *  -> Etc.
     * Parameters:
     *  -> ViewContext *view_context: Pointer to the current state of the tracks view
     */
    
    // Declare Widgets
    GtkWidget *panel; /* Container for the entire control panel */
    GtkWidget *control_buttons; /* play/pause/record buttons */
    GtkWidget *tempo_setter; /* For setting the bpm of the track */

    // Generate Panel
    panel = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0); /* Create the container for the control panel */
    gtk_widget_set_size_request(panel, 0, 80); /* Height of the panel: 200px */
    bg_colour_2(&panel, GTK_STATE_FLAG_NORMAL); /* Set the background colour of the panel to secondary background */
    
    // Generate components
    control_buttons = create_control_buttons(view_context); /* Create buttons */
    tempo_setter = create_tempo_setter(view_context); /* Will create a number input field */
    // Pack widgets
    gtk_box_pack_start(GTK_BOX(panel), control_buttons, 1 /* All widgets should evenly use space */, 0, 0); /* Pack control buttons */
    gtk_box_pack_start(GTK_BOX(panel), tempo_setter, 1 /* All widgets should evenly use space */, 0, 0); /* Pack tempo setter */

    return panel;
}
