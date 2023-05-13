CC = gcc 
CFLAGS = -pthread -I/usr/include/gtk-3.0 -I/usr/include/at-spi2-atk/2.0 -I/usr/include/at-spi-2.0 -I/usr/include/dbus-1.0 -I/usr/lib/x86_64-linux-gnu/dbus-1.0/include -I/usr/include/gtk-3.0 -I/usr/include/gio-unix-2.0 -I/usr/include/cairo -I/usr/include/pango-1.0 -I/usr/include/fribidi -I/usr/include/harfbuzz -I/usr/include/atk-1.0 -I/usr/include/cairo -I/usr/include/pixman-1 -I/usr/include/uuid -I/usr/include/freetype2 -I/usr/include/libpng16 -I/usr/include/gdk-pixbuf-2.0 -I/usr/include/libmount -I/usr/include/blkid -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include
LDFLAGS = -lgtk-3 -lgdk-3 -lpangocairo-1.0 -lpango-1.0 -lharfbuzz -latk-1.0 -lcairo-gobject -lcairo -lgdk_pixbuf-2.0 -lgio-2.0 -lgobject-2.0 -lglib-2.0 -lasound


# #Final compilation
# mixdown: main.o gui.o
# 	$(CC) $(CFLAGS) -o mixdown main.o gui.o $(LDFLAGS)
# #Compile main file
# main.o: main.c
# 	$(CC) -c $(CFLAGS) -o main.o main.c $(LDFLAGS)
#Compile GUI Files
gui.o: windows.o tracks_view.o
	$(CC) -c $(CFLAGS) -o gui.o windows.o tracks_view.o $(LDFLAGS)
#Compile files for tracks view
tracks_view.o: gui/tracks_view/tracks_view.c
	$(CC) -c $(CFLAGS) -o tracks_view.o gui/tracks_view/tracks_view.c $(LDFLAGS)
#Compile all gui windows
windows.o: gui/windows/project_window.c
	$(CC) -c $(CFLAGS) -o windows.o gui/windows/project_window.c $(LDFLAGS)