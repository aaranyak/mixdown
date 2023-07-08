/* toggle_icon_button.c
 * This is a small icon button widget, that can be toggled on and off.
 * The widget has to be connected to a gtkadjustment, that it will change, and respond to changes
*/
// Author - Aaranyak Ghosh
#include <gtk/gtk.h>
#include "../../tracks_view/view_context/view_context.h"
#include "../../theme/theme.h"

void on_toggle(GtkToggleButton *button, GtkAdjustment *adjustment) {
    /* Called when the toggle icon button toggles itself */
    char current_value = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button));
    if (current_value != gtk_adjustment_get_value(adjustment)) { /* If the state of the button is not the same as the state of the adjustment */
        gtk_adjustment_set_value(adjustment, current_value); /* Update the value */
    }
}

void update_button(GtkAdjustment *adjustment, GtkToggleButton **button) {
    /* Updates the value of the button when the adjustment changes */
    char current_value = gtk_adjustment_get_value(adjustment); /* Get value of adjustment */
    if (current_value != gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button))) {
        gtk_toggle_button_set_active(GTK_TOGGLE_BUTTON(button), current_value); /* Update the button */
    }
}

GtkWidget *toggle_icon_button(GtkAdjustment *adjustment, char *icon_name) {
    /* Creates a button that changes and responds to changes from a gtk adjustment */
    
    // Declare Widgets
    GtkWidget *icon;
    GtkWidget *button;
    
    // Create Widgets
    icon = gtk_image_new_from_icon_name(icon_name, GTK_ICON_SIZE_SMALL_TOOLBAR); /* Create new icon */
    button = gtk_toggle_button_new(); /* Create a toggle button */

    // Style Widgets
    gtk_button_set_image(GTK_BUTTON(button), icon); /* Add the icon to the button */
    // Connect Signals
    g_signal_connect(button, "toggled", G_CALLBACK(on_toggle), adjustment); /* Link button to the on toggle callback, so that the button will change the value */
    g_signal_connect(adjustment, "value-changed", G_CALLBACK(update_button), GTK_TOGGLE_BUTTON(button)); /* Link adjustment to update button callback, so the adjustment will change the button */
    return button;
}
