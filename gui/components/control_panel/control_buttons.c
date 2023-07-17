/* control_buttons.c
 * Contains the functions for
 *  -> Back Button
 *  -> Record Button
 *  -> Play Button
*/
// Author - Aaranyak Ghosh
#include <gtk/gtk.h>
#include "../../tracks_view/view_context/view_context.h"
#include "../../theme/theme.h"
#include "../../tracks_view/editor/editor_actions/editor_actions.h" // Debugging

void test_add_track(GtkButton *play_button, ViewContext *view_context) {
    /* Testing adding a new track */
    TrackType type;
    if (rand() & 1) type = MIX_TRACK;
    else type = AUDIO_TRACK;
    create_new_track(view_context, "Eshy is a guinea pig", type);
}

GtkWidget *back_button(ViewContext *view_context) {
    /* Returns back button widget */
    GtkWidget *back_button;
    GtkWidget *back_box; /* Container for sizing button */

    back_button = gtk_button_new_from_icon_name("media-skip-backward", GTK_ICON_SIZE_BUTTON); /* Create back button */
    gtk_widget_set_size_request(back_button, 40, 40); /* Set size of button to 40x40px */
    back_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0); /* Create button container (for sizing button) */
    gtk_box_pack_start(GTK_BOX(back_box), back_button, 1, 0, 0); /* Add button to the container */

    return back_box;
}

GtkWidget *play_button(ViewContext *view_context) {
    /* Returns play button widget */
    GtkWidget *play_button;
    GtkWidget *play_box; /* Container for sizing button */

    play_button = gtk_button_new_from_icon_name("media-playback-start", GTK_ICON_SIZE_BUTTON); /* Create play button */
    gtk_widget_set_size_request(play_button, 40, 40); /* Set size of button to 40x40px */
    play_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0); /* Create button container (for sizing button) */
    gtk_box_pack_start(GTK_BOX(play_box), play_button, 1 /* Expand = True (button centered vertcially) */, 0, 0); /* Add the button to the button container */
    
    // Debugging
    g_signal_connect(play_button, "clicked", G_CALLBACK(test_add_track), view_context); /* Testing adding new tracks */
    return play_box;
}

GtkWidget *record_button(ViewContext *view_context) {
    /* Returns record button widget */
    GtkWidget *record_button;
    GtkWidget *record_box;

    record_button = gtk_button_new_from_icon_name("media-record", GTK_ICON_SIZE_BUTTON); /* Create record button */
    gtk_widget_set_size_request(record_button, 40, 40); /* Set size of button to 40x40px */
    record_box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0); /* Create button container (for sizing button) */
    gtk_box_pack_start(GTK_BOX(record_box), record_button, 1, 0, 0); /* Add the button to the container */
    fg_colour_rec(&record_button, GTK_STATE_FLAG_NORMAL); /* Change colour of record icon to red */

    return record_box;
}

GtkWidget *create_control_buttons(ViewContext *view_context) {
    /* Returns control buttons
     * Including:
     *  -> Back Button
     *  -> Play Button
     *  -> Record Button
    */
    GtkWidget *control_box; /* Container for all buttons */

    control_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10); /* Create container for all buttons */
    gtk_box_pack_start(GTK_BOX(control_box), back_button(view_context), 0, 0, 0); /* Add back button to buttons container */
    gtk_box_pack_start(GTK_BOX(control_box), play_button(view_context), 0, 0, 0); /* Add play button to buttons container */
    gtk_box_pack_start(GTK_BOX(control_box), record_button(view_context), 0, 0, 0); /* Add record button to buttons container */

    return control_box;
}

