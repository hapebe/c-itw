#!/bin/bash
if [ -z $1 ] ; then
	echo "Usage: $0 <name of the GTK C main program file without extension>"
	exit 1
fi
gcc $1.c -o $1 \
-pthread \
-I/usr/include/gtk-2.0 \
-I/usr/lib/x86_64-linux-gnu/gtk-2.0/include \
-I/usr/lib/x86_64-linux-gnu/glib-2.0/include \
-I/usr/include/gio-unix-2.0/ \
-I/usr/include/cairo \
-I/usr/include/pango-1.0 \
-I/usr/include/atk-1.0 \
-I/usr/include/pixman-1 \
-I/usr/include/gdk-pixbuf-2.0 \
-I/usr/include/libpng16 \
-I/usr/include/harfbuzz \
-I/usr/include/glib-2.0 \
-I/usr/include/freetype2 \
-I/usr/include/libpng16 \
-lgtk-x11-2.0 \
-lpangocairo-1.0 \
-latk-1.0 \
-lcairo \
-lgdk_pixbuf-2.0 \
-lgio-2.0 \
-lpangoft2-1.0 \
-lpango-1.0 \
-lgobject-2.0 \
-lglib-2.0 \
-lfontconfig \
-lfreetype
# output of:
# `pkg-config --cflags --libs gtk+-2.0`
if [ $? -eq 0 ] ; then
	./$1 &
else
	echo "Compile failed!"
fi
