CC = gcc
NAME = mixdown
CFLAGS = -pthread -I/usr/include/gtk-3.0 -I/usr/include/at-spi2-atk/2.0 -I/usr/include/at-spi-2.0 -I/usr/include/dbus-1.0 -I/usr/lib/x86_64-linux-gnu/dbus-1.0/include -I/usr/include/gtk-3.0 -I/usr/include/gio-unix-2.0 -I/usr/include/cairo -I/usr/include/pango-1.0 -I/usr/include/fribidi -I/usr/include/harfbuzz -I/usr/include/atk-1.0 -I/usr/include/cairo -I/usr/include/pixman-1 -I/usr/include/uuid -I/usr/include/freetype2 -I/usr/include/libpng16 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/libmount -I/usr/include/blkid -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include
LDFLAGS = -lgtk-3 -lgdk-3 -lpangocairo-1.0 -lpango-1.0 -lharfbuzz -latk-1.0 -lcairo-gobject -lcairo -lgdk_pixbuf-2.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0 -lasound
#Gui Source
S_GUI_COMPONENTS_CONTROLPANEL = gui/components/control_panel/control_buttons.c gui/components/control_panel/tempo_setter.c
S_GUI_COMPONENTS = $(S_GUI_COMPONENTS_CONTROLPANEL)
S_GUI_WINDOWS = gui/windows/project_window.c # All app window source files
S_GUI_TRACKSVIEW_VIEWCONTEXT = gui/tracks_view/view_context/initialize_context.c # All tracks_view state control files
S_GUI_TRACKSVIEW = gui/tracks_view/tracks_view.c gui/tracks_view/control_panel.c $(S_GUI_TRACKSVIEW_VIEWCONTEXT) # source files for tracks view
S_GUI_THEME = gui/theme/colours.c # Source files for theme
S_GUI = $(S_GUI_THEME) $(S_GUI_COMPONENTS) $(S_GUI_TRACKSVIEW) $(S_GUI_WINDOWS) # Gui source files

#Project Source
S_PROJECT = project/init_project.c

SOURCES = main.c $(S_GUI) $(S_PROJECT) # All source files

all: $(SOURCES)
	$(CC) $(CFLAGS) -o $(NAME) $(SOURCES) $(LDFLAGS)
