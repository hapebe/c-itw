/**
 * see: https://www.quora.com/How-do-I-create-a-beautiful-GUI-in-C-Linux
 *
 * preparations / prerequisites:
 * sudo apt-get install build-essential
 * sudo apt-get install libgtk2.0-doc devhelp
 *
 * compile:
 * gcc first.c -o first `pkg-config --cflags --libs gtk+-2.0`
 *
 * I had to install some more packages first:
 * sudo apt-get install pkg-config libgtk2.0-dev
 *
 * Other recommendations include:
 * sudo apt-get install gnome-devel (which also includes Anjuta, i.a.?)
 */

#include <gtk/gtk.h>
int main(int  argc, char *argv[]) {
	GtkWidget *window;
	gtk_init (&argc, &argv);
	window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_widget_show (window);
	gtk_main ();
	return 0;
}
