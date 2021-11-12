//
// Created by hansana on 24/02/2020.
//

#include "gtk_window.h"

static RsvgHandle *svg_handle;

// gtk_widget_queue_draw

static void do_drawing_svg(cairo_t * cr)
{
    //  rsvg_handle_render_document (svg_handle, cr, &viewport, NULL);
    rsvg_handle_render_cairo(svg_handle, cr);
}

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr,
                              gpointer user_data)
{
    do_drawing_svg(cr);
    return FALSE;
}

Gtk_window::Gtk_window(int x, int y,char* svg) {
    this->x_axis = x;
    this->y_axis = y;
    tinyxml2::XMLDocument svg_data;
    svg_data.LoadFile(svg);
    tinyxml2::XMLPrinter printer;
    svg_data.Print(&printer);
    svg_handle = rsvg_handle_new_from_data ((const unsigned char*) printer.CStr(),
                                                  printer.CStrSize()-1, NULL);
}

Gtk_window::~Gtk_window() {}

void Gtk_window::init(int* argc, char*** argv){
    GtkWidget *darea;

    gtk_init(argc, argv);
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    darea = gtk_drawing_area_new();
    gtk_container_add(GTK_CONTAINER(this->window), darea);

    tinyxml2::XMLDocument svg_data;
    svg_data.LoadFile("toto.svg");
    tinyxml2::XMLPrinter printer;
    svg_data.Print(&printer);
    svg_handle = rsvg_handle_new_from_data ((const unsigned char*) printer.CStr(),
            printer.CStrSize()-1, NULL);

    g_signal_connect(G_OBJECT(darea), "draw", G_CALLBACK(on_draw_event), NULL);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    gtk_window_set_position(GTK_WINDOW(this->window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(this->window), this->x_axis, this->y_axis);
    gtk_window_set_title(GTK_WINDOW(this->window), "La maison de ton enfance");

    gtk_widget_show_all(window);

}

void Gtk_window::setHandler(RsvgHandle* ici) {
    svg_handle = ici;
}

void Gtk_window::start() {
    gtk_main();
}

void Gtk_window::stop(){
    gtk_widget_destroy(this->window);
}

GtkWidget* Gtk_window::getWidget(){
    return this->window;
};
