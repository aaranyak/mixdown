CC = gcc
NAME = mixdown
CFLAGS = -pthread -I/usr/include/gtk-3.0 -I/usr/include/at-spi2-atk/2.0 -I/usr/include/at-spi-2.0 -I/usr/include/dbus-1.0 -I/usr/lib/x86_64-linux-gnu/dbus-1.0/include -I/usr/include/gtk-3.0 -I/usr/include/gio-unix-2.0 -I/usr/include/cairo -I/usr/include/pango-1.0 -I/usr/include/fribidi -I/usr/include/harfbuzz -I/usr/include/atk-1.0 -I/usr/include/cairo -I/usr/include/pixman-1 -I/usr/include/uuid -I/usr/include/freetype2 -I/usr/include/libpng16 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/libmount -I/usr/include/blkid -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include
LDFLAGS = -lm -lgtk-3 -lgdk-3 -lpangocairo-1.0 -lpango-1.0 -lharfbuzz -latk-1.0 -lcairo-gobject -lcairo -lgdk_pixbuf-2.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0 -lasound
#Gui Source
S_GUI_COMPONENTS_CONTROLPANEL = gui/components/control_panel/control_buttons.c gui/components/control_panel/tempo_setter.c
S_GUI_COMPONENTS_TRACKEDITOR = gui/components/trk_edit_comps/toggle_icon_button.c
S_GUI_COMPONENTS_REGIONEDITOR = gui/components/rgn_edit_comps/rgn_edit_background.c
S_GUI_COMPONENTS = $(S_GUI_COMPONENTS_CONTROLPANEL) $(S_GUI_COMPONENTS_TRACKEDITOR) $(S_GUI_COMPONENTS_REGIONEDITOR)
S_GUI_WINDOWS = gui/windows/project_window.c # All app window source files
#Gui tracks view source
S_GUI_TRACKSVIEW_VIEWCONTEXT = gui/tracks_view/view_context/initialize_context.c gui/tracks_view/view_context/init_track_states.c # All tracks_view state control files
S_GUI_TRACKSVIEW_EDITOR = gui/tracks_view/editor/editor.c gui/tracks_view/editor/track_editor.c gui/tracks_view/editor/region_editor.c# Source files for the track editor 
S_GUI_TRACKSVIEW = gui/tracks_view/tracks_view.c gui/tracks_view/control_panel.c $(S_GUI_TRACKSVIEW_VIEWCONTEXT) $(S_GUI_TRACKSVIEW_EDITOR) #source files for tracks view
S_GUI_THEME = gui/theme/colours.c gui/theme/fonts.c # Source files for theme
S_GUI = $(S_GUI_THEME) $(S_GUI_COMPONENTS) $(S_GUI_TRACKSVIEW) $(S_GUI_WINDOWS) # Gui source files

#Project Source
S_PROJECT_TRACKS = project/tracks/track_utils.c
S_PROJECT = project/init_project.c $(S_PROJECT_TRACKS)

SOURCES = main.c $(S_GUI) $(S_PROJECT) # All source files

all: $(SOURCES)
	$(CC) $(CFLAGS) -o $(NAME) $(SOURCES) $(LDFLAGS)
