/**
 * see: https://www.quora.com/How-do-I-create-a-beautiful-GUI-in-C-Linux
 *
 * compile:
 * gcc second.c -o second `pkg-config --cflags --libs gtk+-2.0`
 *
 * pkg-config --cflags --libs gtk+-2.0
 * expands to:
 *
 * -pthread
 * -I/usr/include/gtk-2.0
 * -I/usr/lib/x86_64-linux-gnu/gtk-2.0/include
 * -I/usr/include/gio-unix-2.0/
 * -I/usr/include/cairo
 * -I/usr/include/pango-1.0
 * -I/usr/include/atk-1.0
 * -I/usr/include/cairo
 * -I/usr/include/pixman-1
 * -I/usr/include/gdk-pixbuf-2.0
 * -I/usr/include/libpng16
 * -I/usr/include/pango-1.0
 * -I/usr/include/harfbuzz
 * -I/usr/include/pango-1.0
 * -I/usr/include/glib-2.0
 * -I/usr/lib/x86_64-linux-gnu/glib-2.0/include
 * -I/usr/include/freetype2
 * -I/usr/include/libpng16
 * -I/usr/include/freetype2
 * -I/usr/include/libpng16
 * -lgtk-x11-2.0
 * -lgdk-x11-2.0
 * -lpangocairo-1.0
 * -latk-1.0
 * -lcairo
 * -lgdk_pixbuf-2.0
 * -lgio-2.0
 * -lpangoft2-1.0
 * -lpango-1.0
 * -lgobject-2.0
 * -lglib-2.0
 * -lfontconfig
 * -lfreetype
 */

#include "/usr/include/gtk-2.0/gtk/gtk.h"

void hello(GtkWidget* widget, gpointer data){
	g_print("Hello World\n");
}

gint delete_event_handler(GtkWidget* widget, GdkEvent* event, gpointer data){
    /* If you return FALSE in the "delete-event" signal handler,
     * GTK will emit the "destroy" signal. Returning TRUE means
     * you don't want the window to be destroyed.
     * This is useful for popping up 'are you sure you want to quit?'
     * type dialogs. */

	g_print("delete event occured\n");
	return FALSE;
}

void destroy(GtkWidget* widget, gpointer data){
	gtk_main_quit();
}

int main(int argc, char *argv[]){
	GtkWidget *window;
	GtkWidget *button;

	gtk_init(&argc, &argv);
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	g_signal_connect(G_OBJECT(window), "delete_event", G_CALLBACK(delete_event_handler), NULL);
	g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(destroy), NULL);

	gtk_container_set_border_width(GTK_CONTAINER(window), 10);

	button = gtk_button_new_with_label("Hello World");
	g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(hello), NULL);
	gtk_container_add(GTK_CONTAINER(window), button);

	gtk_widget_show(button);
	gtk_widget_show(window);

	gtk_main();

	return 0;
}
