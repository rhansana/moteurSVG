//
// Created by hansana on 24/02/2020.
//

#ifndef CHEVALIER_HANSANA_SAJOT_ROBIN_GTK_WINDOW_H
#define CHEVALIER_HANSANA_SAJOT_ROBIN_GTK_WINDOW_H

#include <librsvg/rsvg.h>
#include <cairo.h>
#include <gtk/gtk.h>
#include <gio/gfile.h>
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <string>
#include "../lib/tinyxml2/tinyxml2.h"

class Gtk_window{

private:
    int x_axis;
    int y_axis;
    GtkWidget * window;

public:
    Gtk_window(int x, int y,char*);

    ~Gtk_window();

    void init(int*, char***);

    static
    void start();

    void setHandler(RsvgHandle*);

    void stop();
    GtkWidget* getWidget();
};

#endif //CHEVALIER_HANSANA_SAJOT_ROBIN_GTK_WINDOW_H
