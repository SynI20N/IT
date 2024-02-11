#include <gtk/gtk.h>
#include <glib/gstdio.h>
#include <stdio.h>
#include <math.h>

typedef struct
{
  GtkWidget* input;
  GtkWidget* output;
} myio;

char *get_text_of_textview(GtkWidget *text_view) {
  GtkTextIter start, end;
  GtkTextBuffer *buffer = gtk_text_view_get_buffer((GtkTextView *)text_view);
  gchar *text;
  gtk_text_buffer_get_bounds(buffer, &start, &end);
  text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);
  return text;
}

static void input(GtkWidget *widget, gpointer data) {
  myio *io = data;
  char *text = get_text_of_textview(io->input);
  float num = atof(text);
  char res[100];
  if (!num) {
    sprintf(res, "%s", "Вы ввели не число");
  }
  else {
    sprintf(res, "%.2f", pow(num, 3) + num - 3.0);
  }
  gtk_label_set_text(GTK_LABEL(io->output), res);
}

static void activate(GtkApplication *app, gpointer user_data) {
  GtkBuilder *builder = gtk_builder_new();
  gtk_builder_add_from_file(builder, "task1.ui", NULL);
  GObject *window = gtk_builder_get_object(builder, "window");
  GtkWidget *button = GTK_WIDGET(gtk_builder_get_object(builder, "button"));
  GtkWidget *box = GTK_WIDGET(gtk_builder_get_object(builder, "box"));
  GtkWidget *view = GTK_WIDGET(gtk_builder_get_object(builder, "view"));
  GtkWidget *label = GTK_WIDGET(gtk_builder_get_object(builder, "label"));

  gtk_window_set_application(GTK_WINDOW(window), app);
  gtk_window_set_default_size(GTK_WINDOW(window), 300, 300);

  myio *io = malloc(sizeof(*io));
  io->input = GTK_WIDGET(view);
  io->output = GTK_WIDGET(label);
  g_signal_connect(button, "clicked", G_CALLBACK(input), io);
  gtk_widget_set_visible(GTK_WIDGET(window), TRUE);

  g_object_unref(builder);
}

int main(int argc, char **argv) {
  #ifdef GTK_SRCDIR
    g_chdir(GTK_SRCDIR);
  #endif

  GtkApplication *app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  int status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
  }
