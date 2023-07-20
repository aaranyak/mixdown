/* MixDown - A free DAW for Linux systems */
/*  Copyright (C) 2023 Aaranyak Ghosh
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

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
    free_project(&current_project);
    return status;
}
