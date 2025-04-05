#include "spiral_generator.h"
static void activate(GtkApplication *app, gpointer user_data) {
    AppData *app_data = (AppData *)user_data;
    setup_gui(app, app_data);
}
int main(int argc, char *argv[]) {
    GtkApplication *app = gtk_application_new("org.example.spiralgenerator",
                                            G_APPLICATION_DEFAULT_FLAGS);
    if (!app) {
        g_print("Error: Failed to create application\n");
        return -1;
    }
    AppData app_data;
    app_data.type = THEODORUS;
    app_data.drawing_area = NULL;
    app_data.animation_id = 0;
    g_signal_connect(app, "activate", G_CALLBACK(activate), &app_data);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
