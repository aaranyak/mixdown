/* MixDown - A free DAW for Linux systems */
// Author - Aaranyak Ghosh
#include <gtk/gtk.h>
#include "project/project.h"
#include "gui/gui.h"
Project current_project;
static void start(GtkApplication *app, gpointer uset_data)
{
    /* Function called when app starts */
    init_project(&current_project);
    open_project_window(app, &current_project); /* Open the new project */
}

int main(int argc, char **argv)
{
    /* Create and run MixDown app */
    GtkApplication *app; /* This is the app object that will be used for creating windows */
    int status; /* Return status: error/success */
    app = gtk_application_new("io.github.aaranyak.mixdown", G_APPLICATION_FLAGS_NONE); /* Create new GTK Application with id "io.github.aaranyak.mixdown" */
    g_signal_connect(app, "activate", G_CALLBACK (start), NULL); /* Set app start callback to the start function */
    status = g_application_run(G_APPLICATION (app), argc, argv); /* Run app */
    g_object_unref(app); /* Free memory when app is closed */
    return status;
}
