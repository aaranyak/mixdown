/* tempo_setter.c
 *  -> Tempo Setter (for setting the bpm of the track)
*/
#include <gtk/gtk.h>
#include "../../tracks_view/view_context/view_context.h"
#include "../../theme/theme.h"

int tempo_setter_label(GtkSpinButton *input_widget, int* no_data) {
    /* Callback function to update the label of the tempo setter */
    int value = (int)gtk_adjustment_get_value(gtk_spin_button_get_adjustment(input_widget) /* Get adjustment object from SpinButton widget */) /* Get value of adjustment object */; /* Get value of button */
    char text[7]; /* Button label string */
    sprintf(text, "%d bpm", value); /* Format of text - "<value> bpm" */
    gtk_entry_set_text(GTK_ENTRY(input_widget), text); /* Set the text of the button */
    return 0;
}

int tempo_setter_update(GtkSpinButton *input_widget, int* tempo) {
    /* Callback function to update tempo when input value is changed 
     * int* tempo - Pointer to the value to be changed 
     */
    int value = (int)gtk_adjustment_get_value(gtk_spin_button_get_adjustment(input_widget) /* Get adjustment object from SpinButton widget */) /* Get value of adjustment object */; /* Get value of button */
    *tempo = value; /* Set the value of the tempo to the input's value */
    tempo_setter_label(input_widget, 0); /* Set tempo text */    
    return 0;
}    
GtkWidget *create_tempo_setter(ViewContext *view_context) {
    /* Returns a widget for setting the tempo */
    GtkWidget *number_input; /* This will be a spin button for setting the bpm */
    GtkWidget *sizing_box; /* Align the widget vertically */
    GtkAdjustment *adjustment; /* Number limits (idk why this is called adjustment) */
    
    int *tempo_loc; /* Pointer to the tempo variable */
    // Create widgets
    adjustment = gtk_adjustment_new(120.0, 15.0, 480.0, 1.0, 8.0, 0.0); /* Some limits for value */
    number_input = gtk_spin_button_new(adjustment, 1.0, 0); /* Create a basic integer spin button */
    sizing_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0); /* For aligning the widget to the center */
    
    // Connect Signals
    tempo_loc = &(view_context->project->project_settings.tempo); /* Get the pointer to the tempo */
    g_signal_connect(number_input, "value-changed", G_CALLBACK(tempo_setter_update), tempo_loc); /* Whenever the value of the input changes, the function "tempo_setter_update" is called */
    g_signal_connect(number_input, "output", G_CALLBACK(tempo_setter_label), NULL); /* This function formats the text of the spin button */   
    
    // Pack Widgets
    gtk_widget_set_size_request(number_input, 150, 0); /* Minimum horizontal size = 100px */
    gtk_box_pack_start(GTK_BOX(sizing_box), number_input, 1 /* Align vertically */, 0, 0); /* Pack the widget in the sizing box */

    return sizing_box;
}
