/**
 * compile:
 * ./gtk-compile.sh table0
 */

#include <gtk/gtk.h>

/* Our callback.
 * The data passed to this function is printed to stdout */
static void callback( GtkWidget *widget, gpointer   data ) {
    g_print ("Hello again - %s was pressed\n", (char *) data);
}

/* This callback quits the program */
static gboolean delete_event( GtkWidget *widget, GdkEvent  *event, gpointer   data ) {
    gtk_main_quit ();
    return FALSE;
}

int main( int argc, char *argv[] ) {
    GtkWidget *window;
    GtkWidget *button;
    GtkWidget *table;

    gtk_init (&argc, &argv);

    /* Create a new window */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "Table");
    gtk_container_set_border_width (GTK_CONTAINER (window), 20);
    // Set a handler for delete_event that immediately exits GTK.
    g_signal_connect (window, "delete-event", G_CALLBACK (delete_event), NULL);

    /* Create a 2x2 table */
    table = gtk_table_new (2, 2, TRUE);

    gtk_container_add (GTK_CONTAINER (window), table); // Put the table in the main window

    /* Create first button */
    button = gtk_button_new_with_label ("button 1");
    g_signal_connect (button, "clicked", G_CALLBACK (callback), (gpointer) "action 1");
    /* Insert button 1 into the upper left quadrant of the table */
    gtk_table_attach_defaults (GTK_TABLE (table), button, 0, 1, 0, 1);
    gtk_widget_show (button);

    /* Create second button */
    button = gtk_button_new_with_label ("button 2");
    g_signal_connect (button, "clicked", G_CALLBACK (callback), (gpointer) "action 2");
    /* Insert button 2 into the upper right quadrant of the table */
    gtk_table_attach_defaults (GTK_TABLE (table), button, 1, 2, 0, 1);
    gtk_widget_show (button);

    /* Create "Quit" button */
    button = gtk_button_new_with_label ("Quit");
    g_signal_connect (button, "clicked", G_CALLBACK (delete_event), NULL);
    /* Insert the quit button into the both lower quadrants of the table */
    gtk_table_attach_defaults (GTK_TABLE (table), button, 0, 2, 1, 2);
    gtk_widget_show (button);

    gtk_widget_show (table);
    gtk_widget_show (window);

    gtk_main ();

    return 0;
}
