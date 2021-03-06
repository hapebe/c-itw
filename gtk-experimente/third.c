/**
 * see: https://www.quora.com/How-do-I-create-a-beautiful-GUI-in-C-Linux
 *
 * compile:
 * ./gtk-compile.sh third
 */

#include "/usr/include/gtk-2.0/gtk/gtk.h"

void hello(GtkWidget* widget, gpointer data){
	g_print("Hello World\n");
}

void handleMotionNotify(GtkWidget* widget, GdkEvent *event, gpointer data) {
	g_print("motion_notify_event\n");
}

void handleKeyPress(GtkWidget* widget, GdkEvent *event, gpointer data) {
	g_print("Key pressed...\n");
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
	g_signal_connect(G_OBJECT(window), "key_press_event", G_CALLBACK(handleKeyPress), NULL);
	g_signal_connect(G_OBJECT(window), "motion_notify_event", G_CALLBACK(handleMotionNotify), NULL);

	gtk_container_set_border_width(GTK_CONTAINER(window), 10);

	button = gtk_button_new_with_label("Hello World");
	g_signal_connect(G_OBJECT(button), "clicked", G_CALLBACK(hello), NULL);
	gtk_container_add(GTK_CONTAINER(window), button);

	gtk_widget_show(button);
	gtk_widget_show(window);

	gtk_main();

	return 0;
}
