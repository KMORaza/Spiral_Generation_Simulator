#include "spiral_generator.h"
#include <math.h>
void draw_helix(cairo_t *cr, AppData *app_data) {
    if (!cr || !app_data) {
        g_print("Error: Null Cairo context or data in draw_helix\n");
        return;
    }
    int width = gtk_widget_get_width(app_data->drawing_area);
    int height = gtk_widget_get_height(app_data->drawing_area);
    g_print("Drawing Helix with size %d x %d, point %d/%d\n",
            width, height, app_data->spiral_data.current_point, app_data->spiral_data.max_points);
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_paint(cr);
    cairo_translate(cr, width/2.0, height/2.0);
    cairo_set_source_rgb(cr, 1, 0, 0);
    cairo_set_line_width(cr, 2.0);
    for (int i = 0; i < app_data->spiral_data.current_point && i < app_data->spiral_data.max_points - 1; i++) {
        cairo_move_to(cr, app_data->spiral_data.x[i], app_data->spiral_data.y[i]);
        cairo_line_to(cr, app_data->spiral_data.x[i+1], app_data->spiral_data.y[i+1]);
    }
    cairo_stroke(cr);
    double axis_length = 100.0;
    double alpha = M_PI / 6;
    cairo_set_source_rgb(cr, 0.5, 0.5, 0.5);
    cairo_set_line_width(cr, 1.0);
    cairo_move_to(cr, -axis_length, 0);
    cairo_line_to(cr, axis_length, 0);
    cairo_stroke(cr);
    cairo_move_to(cr, 0, -axis_length);
    cairo_line_to(cr, 0, axis_length);
    cairo_stroke(cr);
    cairo_move_to(cr, 0, 0);
    cairo_line_to(cr, -axis_length * cos(alpha), -axis_length * sin(alpha));
    cairo_stroke(cr);
}
