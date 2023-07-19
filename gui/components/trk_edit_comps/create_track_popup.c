/* create_track_popup.c
 *  -> Contains functions to create to create the track creating popup
 *  -> Also contains the function to create the create track button
 *     that launches the popup
*/

// Author - Aaranyak Ghosh

#include <gtk/gtk.h>
#include <string.h>
#include "../../tracks_view/view_context/view_context.h"
#include "../../theme/theme.h"
#include "../../../project/project.h"
#include "../../tracks_view/editor/editor_actions/editor_actions.h"

void launch_create_track_popup(GtkButton *button, ViewContext *view_context) {
    /* Callback for the create new track button
     * Launches a popup with 
     *  -> Set track name
     *  -> Set track type
     *  -> Create button
     *  -> Cancel button
    */

    // Declare
    GtkWidget *popup_dialog;
    GtkWidget *window; /* Toplevel window */
    GtkWidget *content_grid;
    GtkWidget *popup_content; /* The content of the popup */
    // Inner widgets
    GtkWidget *name_entry;
    GtkWidget *name_label;
    GtkWidget *type_label;
    GtkWidget *type_input;
    // Create
    window = gtk_widget_get_toplevel(GTK_WIDGET (button)); /* Get the toplevel window */
    popup_dialog = gtk_dialog_new_with_buttons( /* Create an interactive dialog with buttons */
            "Create New Track", /* Dialog title */
            GTK_WINDOW (window), /* Toplevel window */
            GTK_DIALOG_MODAL | GTK_DIALOG_DESTROY_WITH_PARENT, /* Flags */
            /* Here come the buttons */
            "_Add Track", /* Button title */
            GTK_RESPONSE_OK, /* Response id */
            "_Cancel", /* Ditto */
            GTK_RESPONSE_CANCEL,
            NULL /* List ends with null */
            );
    
    // Create inside of popup
    popup_content = gtk_dialog_get_content_area(GTK_DIALOG (popup_dialog)); /* Where to place the content of the box */
    content_grid = gtk_grid_new(); /* Grid that includes all the entrys and labels */
    /* Name input */
    name_label = gtk_label_new("Track Name "); /* Create the label of the text input for name */
    name_entry = gtk_entry_new(); /* Create the input field for the name */
    /* Type input */
    type_label = gtk_label_new("Track Type ");
    type_input = gtk_combo_box_text_new(); /* Create the multiple choice input */
    /* Set input options */
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT (type_input), "audio", "Audio Track"); /* Add the audio track option */
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT (type_input), "mix", "Mix Track"); /* Add the audio track option */
    gtk_combo_box_text_append(GTK_COMBO_BOX_TEXT (type_input), "midi", "Midi Track (not yet implemented)"); /* Add the audio track option */

    // Format
    gtk_grid_set_row_spacing(GTK_GRID (content_grid), 4); /* Set space between rows in the grid */
    gtk_grid_set_column_spacing(GTK_GRID (content_grid), 4); /* Set space between columns in the grid */
    g_object_set(G_OBJECT(content_grid), "margin", 10, (gchar*)0 /* Null-terminated arguments */); /* Add padding of 10px */

    // Connect
    gtk_combo_box_set_active(GTK_COMBO_BOX (type_input), 0); /* Set default of type input to audio track */ 
    // Pack
    /* Pack the entries and labels into the grid */
    gtk_grid_attach(GTK_GRID (content_grid), name_label, 0, 0, 1, 1); /* Pack the name label into grid */
    gtk_grid_attach(GTK_GRID (content_grid), name_entry, 1, 0, 1, 1); /* Pack the name input into grid */
    gtk_grid_attach(GTK_GRID (content_grid), type_label, 0, 1, 1, 1); /* Pack the name label into grid */
    gtk_grid_attach(GTK_GRID (content_grid), type_input, 1, 1, 1, 1); /* Pack the name input into grid */
    
    /* pack the grid into the popup */
    gtk_container_add(GTK_CONTAINER (popup_content), content_grid); /* Add the grid into the popup */
    gtk_widget_show_all(popup_content); /* Show the widgets inside the popup */
    
    // Do
    gint response; /* The response (cancel/ok) */
    TrackType type; /* Type of track */
    int type_id; /* track type id */
    gchar *track_name; /* Track name */
    response = gtk_dialog_run(GTK_DIALOG (popup_dialog)); /* Open the dialog */
    if (response == GTK_RESPONSE_OK) {
        /* If the user presses "create" */
        /* Set track type */
        type_id = gtk_combo_box_get_active(GTK_COMBO_BOX (type_input)); /* Get the id of the track type */
        track_name = (gchar*)gtk_entry_get_text(GTK_ENTRY (name_entry)); /* Get the text of the name input */
        if (strlen(track_name) == 0 || strlen(track_name) > 40) { /* Validate text length */
            printf("\033[1;31mError: Text not valid.\n\033[1;0mPlease enter text length between 0 and 40 characters.\n"); /* Error message */
        } else { /* If text length is valid */
            switch (type_id) { /* Set track type based on input */
                case 0: /* Audio */
                    type = AUDIO_TRACK;
                    break;
                case 1: /* Mix */
                    type = MIX_TRACK;
                    break;
                case 2: /* Midi track not yet supported */
                    printf("\033[1;31mError: Not implemented.\n\033[1;0mMidi tracks not yet implemented.\n"); /* Error message */
                    gtk_widget_destroy(popup_dialog); /* Drop everything */
                    return; /* And get out of here */
            }
            create_new_track(view_context, track_name, type); /* Create the new track */
        }
    }
    // Delete
    gtk_widget_destroy(popup_dialog); /* Destroy the dialog */
}



GtkWidget *create_add_track_button(ViewContext *view_context) {
    /* Creates the button that when clicked, launches popup to add a new track */

    GtkWidget *button;
    GtkWidget *sizing_box; /* Container for sizing button */

    button = gtk_button_new_from_icon_name("list-add", GTK_ICON_SIZE_BUTTON); /* Create button */
    gtk_widget_set_size_request(button, -1, 70); /* Set size of button to 40x40px */
    g_signal_connect(button, "clicked", G_CALLBACK (launch_create_track_popup), view_context); /* Connect the button to the popup launcher */
    sizing_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0); /* Create button container (for sizing button) */
    gtk_box_pack_start(GTK_BOX(sizing_box), button, 1, 1 /* Fill area */, 10); /* Add button to the container */
    
    return sizing_box;
}

