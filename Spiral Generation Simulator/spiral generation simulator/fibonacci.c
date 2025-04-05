#include "spiral_generator.h"
#include <math.h>
void draw_fibonacci(cairo_t *cr, AppData *app_data) {
    if (!cr || !app_data) {
        g_print("Error: Null Cairo context or data in draw_fibonacci\n");
        return;
    }
    int width = gtk_widget_get_width(app_data->drawing_area);
    int height = gtk_widget_get_height(app_data->drawing_area);
    g_print("Drawing Fibonacci with size %d x %d, point %d/%d\n",
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
    for (int i = 0; i < app_data->spiral_data.current_point && i < app_data->spiral_data.max_points; i++) {
        cairo_arc(cr, app_data->spiral_data.x[i], app_data->spiral_data.y[i], 3.0, 0, 2 * M_PI);
        cairo_fill(cr);
    }
    cairo_set_source_rgb(cr, 0.5, 0.5, 0.5);
    cairo_set_line_width(cr, 1.0);
    double phi = (1 + sqrt(5)) / 2;
    double fib[app_data->spiral_data.max_points];
    fib[0] = 1.0;
    fib[1] = 1.0;
    for (int k = 2; k < app_data->spiral_data.max_points; k++) {
        fib[k] = fib[k-1] + fib[k-2];
    }
    for (int k = 0; k < app_data->spiral_data.current_point - 1 && k < app_data->spiral_data.max_points - 1; k++) {
        double r = fib[k] * 10.0;
        double start_angle = (2 * M_PI * k / phi);
        double end_angle = start_angle + M_PI/2;
        double center_x = app_data->spiral_data.x[k];
        double center_y = app_data->spiral_data.y[k];
        if (k % 4 == 0) {
            center_x -= r;
        } else if (k % 4 == 1) {
            center_y -= r;
        } else if (k % 4 == 2) {
            center_x += r;
        } else if (k % 4 == 3) {
            center_y += r;
        }
        cairo_arc(cr, center_x, center_y, r, start_angle, end_angle);
        cairo_stroke(cr);
    }
}
