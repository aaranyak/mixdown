#ifndef THEME_H /* Header guard */
#define THEME_H
/* Colours are defined in colours.c */
void bg_colour_2(GtkWidget** widget, GtkStateFlags state);
void bg_colour_track(GtkWidget** widget, GtkStateFlags state);
void bg_colour_track_mix(GtkWidget** widget, GtkStateFlags state);
void fg_colour_rec(GtkWidget** widget, GtkStateFlags state);
void bg_colour_rec(GtkWidget** widget, GtkStateFlags state);
/* Fonts are defined in fonts.c */
void set_def_font(GtkWidget **widget);
#endif
