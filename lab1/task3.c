#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <glib/gstdio.h>
#include <stdio.h>
#include <math.h>

typedef struct {
    int color;
    GtkWidget* label;
} color;

typedef void (*callback)(GtkWidget* widget, gpointer data);

static void change_color(GtkWidget* widget, gpointer data) {
    color* c = (color*)data;
    if(c->color) {
        gtk_widget_remove_css_class(GTK_WIDGET(c->label), "red-background");
        gtk_widget_add_css_class(GTK_WIDGET(c->label), "green-background");
        c->color = 0;
    }
    else {
        gtk_widget_add_css_class(GTK_WIDGET(c->label), "red-background");
        gtk_widget_remove_css_class(GTK_WIDGET(c->label), "green-background");
        c->color = 1;
    }
}

void set_event(const char* s, GtkWidget* widget, color* l, callback func) {
    GtkEventController *controller = gtk_event_controller_motion_new();
    gtk_widget_add_controller(widget, controller);
    g_signal_connect(controller, s, G_CALLBACK(func), l);
}

static void activate(GtkApplication *app, gpointer user_data) {
    GtkBuilder *builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "task3.ui", NULL);
    GdkDisplay *display = gdk_display_get_default ();
    GtkCssProvider *provider = gtk_css_provider_new ();
    GObject *window = gtk_builder_get_object(builder, "window");
    GObject *label = gtk_builder_get_object(builder, "label");
    gtk_css_provider_load_from_path(provider, "styles.css");
    gtk_style_context_add_provider_for_display (display,
                                                GTK_STYLE_PROVIDER (provider),
                                                GTK_STYLE_PROVIDER_PRIORITY_FALLBACK);
    gtk_window_set_application(GTK_WINDOW(window), app);
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 300);
    gtk_widget_add_css_class(GTK_WIDGET(label), "red-background");
    color* color = malloc(sizeof(*color));
    color->color = 1;
    color->label = GTK_WIDGET(label);
    set_event("motion", GTK_WIDGET(label), color, change_color);

    gtk_widget_show(GTK_WIDGET(window));

    g_object_unref(provider);
    g_object_unref(builder);
}

int main(int argc, char **argv) {
    #ifdef GTK_SRCDIR
        g_chdir(GTK_SRCDIR);
    #endif

    GtkApplication* app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);

    return status;
}
