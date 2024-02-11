#include <gtk/gtk.h>
#include <glib/gstdio.h>
#include <stdio.h>
#include <math.h>

typedef struct {
    GtkButton* first;
    GtkButton* second;
    int mode;
} labels;

typedef void (*callback)(GtkWidget* widget, gpointer data);

static void change(GtkWidget* widget, gpointer data) {
    labels* l = (labels*)data;
    char entered[] = "Пришел";
    char left[] = "Ушел";
    if(l->mode) {
        gtk_button_set_label(GTK_BUTTON(l->first), entered);
        gtk_button_set_label(GTK_BUTTON(l->second), left);
    }
    else {
        gtk_button_set_label(GTK_BUTTON(l->first), left);
        gtk_button_set_label(GTK_BUTTON(l->second), entered);
    }
}

static void left(GtkWidget* widget, gpointer data) {
    labels* l = (labels*)data;
    char empty[] = "";
    gtk_button_set_label(GTK_BUTTON(l->first), empty);
    gtk_button_set_label(GTK_BUTTON(l->second), empty);
}

void set_event(const char* s, GtkWidget* widget, labels* l, callback func) {
    GtkEventController *controller = gtk_event_controller_motion_new();
    gtk_widget_add_controller(widget, controller);
    g_signal_connect(controller, s, G_CALLBACK(func), l);
}

static void activate(GtkApplication *app, gpointer user_data) {
    GtkBuilder *builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "task2.ui", NULL);
    GObject *window = gtk_builder_get_object(builder, "window");
    GtkWidget *button = GTK_WIDGET(gtk_builder_get_object(builder, "button"));
    GtkWidget *button2 = GTK_WIDGET(gtk_builder_get_object(builder, "button2"));

    gtk_window_set_application(GTK_WINDOW(window), app);
    gtk_window_set_default_size(GTK_WINDOW(window), 300, 300);

    labels* ls = malloc(sizeof(*ls));
    ls->first = GTK_BUTTON(button);
    ls->second = GTK_BUTTON(button2);
    ls->mode = 1;

    //i dont understand why cant we just memcpy the first pointer but...
    labels* ls2 = malloc(sizeof(*ls));
    ls2->first = GTK_BUTTON(button);
    ls2->second = GTK_BUTTON(button2);
    ls2->mode = 0;

    set_event("enter", button, ls, change);
    set_event("enter", button2, ls2, change);
    set_event("leave", button, ls, left);
    set_event("leave", button2, ls, left);

    gtk_widget_set_visible(GTK_WIDGET(window), TRUE);

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
