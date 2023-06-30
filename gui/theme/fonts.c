#include <gtk/gtk.h>
// Author: Aaranyak Ghosh
/* This file contains all fonts for this theme */

// Default font (ubuntu)
void set_def_font(GtkWidget **widget) {
    // Sets the font of the widget to the default font (Ubuntu)
    PangoFontDescription *font;
    font = pango_font_description_from_string("Ubuntu"); /* create the font description */
    gtk_widget_override_font(*widget, font); /* Set the font of the widget */
}
