#include "spiral_generator.h"
#include <math.h>
void draw_hyperbolic(cairo_t *cr, AppData *app_data) {
    if (!cr || !app_data) {
        g_print("Error: Null Cairo context or data in draw_hyperbolic\n");
        return;
    }
    int width = gtk_widget_get_width(app_data->drawing_area);
    int height = gtk_widget_get_height(app_data->drawing_area);
    g_print("Drawing Hyperbolic with size %d x %d, point %d/%d\n",
            width, height, app_data->spiral_data.current_point, app_data->spiral_data.max_points);
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_paint(cr);
    cairo_translate(cr, width/2.0, height/2.0);
    cairo_set_source_rgb(cr, 0, 0, 1);
    cairo_set_line_width(cr, 2.0);
    for (int i = 0; i < app_data->spiral_data.current_point && i < app_data->spiral_data.max_points - 1; i++) {
        cairo_move_to(cr, app_data->spiral_data.x[i], app_data->spiral_data.y[i]);
        cairo_line_to(cr, app_data->spiral_data.x[i+1], app_data->spiral_data.y[i+1]);
    }
    cairo_stroke(cr);
    cairo_set_source_rgb(cr, 1, 0, 0);
    cairo_arc(cr, 0, 0, 4.0, 0, 2 * M_PI);
    cairo_fill(cr);
    double radii[3] = {1.0 * 50.0, 2.0 * 50.0, 3.0 * 50.0};
    cairo_set_source_rgb(cr, 0.5, 0.5, 0.5);
    cairo_set_line_width(cr, 0.5);
    for (int i = 0; i < 3; i++) {
        cairo_arc(cr, 0, 0, radii[i], 0, 2 * M_PI);
        cairo_stroke(cr);
    }
    if (app_data->spiral_data.current_point >= 100) {
        cairo_set_source_rgb(cr, 1, 1, 1);
        cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
        cairo_set_font_size(cr, 12.0);
        char label[20];
        snprintf(label, sizeof(label), "r = 5.0/θ");
        cairo_move_to(cr, app_data->spiral_data.x[99], app_data->spiral_data.y[99] - 10);  // Slightly above point 100
        cairo_show_text(cr, label);
    }
}
