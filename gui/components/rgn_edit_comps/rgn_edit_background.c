/* rgn_edit_background.c
 * This file contains the function to generate the background of the region editor
 * The background shows bar ticks and beat ticks
 * The ticks scroll as the editor scrolls
 * Uses gtkdrawingarea
*/
// Author - Aaranyak Ghosh
#include <gtk/gtk.h>
#include "../../tracks_view/view_context/view_context.h"
#include "../../theme/theme.h"
#include <math.h>
void redraw_on_update(GtkAdjustment *adjustment, GtkDrawingArea *drawing_area) {
    /* Redaraws the drawingarea on adjustment update */
    gtk_widget_queue_draw(GTK_WIDGET(drawing_area)); /* Queue update */
}

void draw_background(GtkDrawingArea *background, /* The drawing area widget */
                     cairo_t *canvas,
                     ViewContext *view_context)
{
    // Declarations
    GtkStyleContext *style_context; /* Used for rendering background */
    int beat_count;
    int current_beat_pos;
    // Calculate positions & limits
    int start = gtk_adjustment_get_value(view_context->scroll); /* Get start position of view (in samples) */
    int end; /* The end position of the view (in samples) */
    int scale = gtk_adjustment_get_value(view_context->scale); /* samples per pixel */
    end = gtk_widget_get_allocated_width(GTK_WIDGET(background)) * scale; /* Calculate end position of background (in samples) */
    // Test the following line of code properly.
    int beat_length = (60.0f / view_context->project->project_settings.tempo) * view_context->project->project_settings.audio_settings.sample_rate; /* Conversion beat length (in bpm) to hz, times sample rate to get in samples */
    current_beat_pos = start % beat_length; /* Position of first beat */
    if (current_beat_pos) current_beat_pos = beat_length - current_beat_pos; /* If not falling on beat, move on to next */
    // Calculate the current beat count in bar
    if (current_beat_pos) beat_count = (start / beat_length + 1) % view_context->project->project_settings.time_signature.per_bar;
    else beat_count = (start / beat_length) % view_context->project->project_settings.time_signature.per_bar;
    // Do the actual drawing of beats
    
    // Render Background
    style_context = gtk_widget_get_style_context(GTK_WIDGET(background)); /* Get the style context */
    gtk_render_background(
            style_context, /* Probably for retriving the background colour */
            canvas, /* The canvas to draw onto */
            0, 0, /* Position of the background */
            /* Size of the background */
            end / scale, /* Convert length from samples to pixels */
            110 /* Fixed height of cells (110px) */
            ); /* Render the background colour onto the canvas */

    
    // Render ticks
    while (current_beat_pos < end) { /* Loop through all beats */
        // Render beat tick probably 1px for beats and 2px for bars.
        if (beat_count) cairo_set_source_rgb(canvas, 0.5, 0.5, 0.5); /* Tick colour is soft white (for beat ticks) */
        else cairo_set_source_rgb(canvas, 1, 1, 1); /* Tick colour is white (for bar ticks) */
        cairo_rectangle(canvas, /* Draw rectangle on canvas */
                        current_beat_pos / scale, /* X position */
                        0, /* Y position */
                        1, 110 /* Width, Height */
                        ); /* Draw rectangle for the tick */
        cairo_fill(canvas);
        // Move to next beat
        beat_count++; /* Increment beat count */
        if (beat_count > 3) beat_count = 0; /* Set back if required */
        current_beat_pos += beat_length; /* Next beat */
    }
}

GtkWidget *region_editor_background(ViewContext *view_context, char odd_even /* Odd rows have different colour than even rows */) {
    /* Returns a scrolling background with bar ticks and beat ticks */
    // Declare widgets
    GtkWidget *background; /* This ought to be a drawing area */
    // Create Widgets
    background = gtk_drawing_area_new(); /* Create drawingarea widget */
   
    // Style Widgets
    if (odd_even) bg_colour_2(&background, GTK_STATE_FLAG_NORMAL); /* Different colours for odd/even tracks */ 
    // Connect signals
    g_signal_connect(background, "draw", G_CALLBACK(draw_background), view_context); /* Connect the draw function, which will draw the backgroun on update */
    
    // Update background signals
    g_signal_connect(view_context->scroll, "value-changed", G_CALLBACK(redraw_on_update), background); /* Redraw background when scroll changes */
    g_signal_connect(view_context->scale, "value-changed", G_CALLBACK(redraw_on_update), background); /* Redraw background when zooming */
    return background;
}
