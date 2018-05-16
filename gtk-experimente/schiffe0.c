/**
 * compile:
 * ./gtk-compile.sh schiffe0
 */

#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>

/* Create a new hbox with an image and a label packed into it
 * and return the box. */
static GtkWidget *xpm_label_box(gchar *xpm_filename, gchar *label_text ) {
    // GtkWidget *box;
    // GtkWidget *label;
    GtkWidget *image;

    /* Create box for image and label */
    // box = gtk_hbox_new(FALSE, 0);
    // gtk_container_set_border_width(GTK_CONTAINER (box), 2);

    /* Now on to the image stuff */
    image = gtk_image_new_from_file(xpm_filename);

    /* Create a label for the button */
    // label = gtk_label_new(label_text);

    /* Pack the image and label into the box */
    // gint padding = 0; // was: 3
    // gtk_box_pack_start(GTK_BOX (box), image, FALSE, FALSE, padding);
    // gtk_box_pack_start(GTK_BOX (box), label, FALSE, FALSE, padding);

    gtk_widget_show(image);
    // gtk_widget_show(label);

    // return box;
    return image;
}

/* Our usual callback function */
static void callback( GtkWidget *widget, gpointer data ) {
    g_print ("Hello again - %s was pressed\n", (char *) data);
}

int main( int argc, char *argv[] ) {
    /* GtkWidget is the storage type for widgets */
    GtkWidget *window;
    GtkWidget *label;
    GtkWidget *button;
    GtkWidget *box;
    GtkWidget *table;

    gtk_init (&argc, &argv);

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title (GTK_WINDOW (window), "Ein Spielfeld zum Schiffe versenken");
    /* It's a good idea to do this for all windows. */
    g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);
    g_signal_connect (window, "delete-event", G_CALLBACK (gtk_main_quit), NULL);
    // gtk_container_set_border_width (GTK_CONTAINER (window), 10);

    // create a table to accept my button matrix:
    table = gtk_table_new (11, 11, TRUE);
    gtk_container_add (GTK_CONTAINER (window), table); // Put the table in the main window

	int x=0, y=0;
	// add column labels:
	for (x=0; x<10; x++) {
		char* txt = (char *)malloc(sizeof(char) * 2);
		txt[0] = (char)('A' + x);
		txt[1] = '\0';

		label = gtk_label_new (txt);
	    gtk_table_attach_defaults (GTK_TABLE (table), label, x+1, x+2, 0, 1);
		gtk_widget_show (label);
	}

	// add row labels:
	for (y=0; y<10; y++) {
		char* txt = (char *)malloc(sizeof(char) * 3);
		sprintf(txt, "%d", y+1);

		label = gtk_label_new (txt);
	    gtk_table_attach_defaults (GTK_TABLE (table), label, 0, 1, y+1, y+2);
		gtk_widget_show (label);
	}

	// add action buttons:
	for (x=0; x<10; x++) {
		for (y=0; y<10; y++) {
			char* label = (char *)malloc(sizeof(char) * 32);
			sprintf(label, "btn(%d;%d)", x, y);

			/* Create a new button */
			button = gtk_button_new ();
			g_signal_connect (button, "clicked", G_CALLBACK (callback), (gpointer) label);

			/* This calls our box creating function */
			box = xpm_label_box ("sea.xpm", "cool button");
			gtk_widget_show (box);

			gtk_container_add (GTK_CONTAINER (button), box);
			gtk_widget_show (button);

			// gtk_container_add (GTK_CONTAINER (window), button);
		    gtk_table_attach_defaults (GTK_TABLE (table), button, x+1, x+2, y+1, y+2);
		}
	}
	gtk_widget_show (table);

    gtk_widget_show (window);

    /* Rest in gtk_main and wait for the fun to begin! */
    gtk_main ();

    return 0;
}
