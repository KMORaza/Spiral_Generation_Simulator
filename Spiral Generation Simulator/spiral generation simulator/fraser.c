#include "spiral_generator.h"
#include <math.h>
void draw_fraser(cairo_t *cr, AppData *app_data) {
    if (!cr || !app_data) {
        g_print("Error: Null Cairo context or data in draw_fraser\n");
        return;
    }
    int width = gtk_widget_get_width(app_data->drawing_area);
    int height = gtk_widget_get_height(app_data->drawing_area);
    g_print("Drawing Fraser with size %d x %d, point %d/%d\n",
            width, height, app_data->spiral_data.current_point, app_data->spiral_data.max_points);
    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_paint(cr);
    cairo_translate(cr, width/2.0, height/2.0);
    int num_circles = app_data->spiral_data.max_points / 10;
    int current_circles = app_data->spiral_data.current_point / 10;
    double base_radius = 20.0;
    double radius_step = 10.0;
    int segments_per_circle = 36;
    for (int i = 0; i < current_circles && i < num_circles; i++) {
        double radius = base_radius + i * radius_step;
        double angle_step = 2 * M_PI / segments_per_circle;
        for (int j = 0; j < segments_per_circle; j++) {
            double start_angle = j * angle_step + (i % 2) * angle_step / 2;
            double end_angle = start_angle + angle_step;
            if (j % 2 == 0) {
                cairo_set_source_rgb(cr, 0, 0, 0);
            } else {
                cairo_set_source_rgb(cr, 1, 1, 1);
            }
            cairo_set_line_width(cr, 4.0);
            cairo_arc(cr, 0, 0, radius, start_angle, end_angle);
            cairo_stroke(cr);
        }
    }
}
