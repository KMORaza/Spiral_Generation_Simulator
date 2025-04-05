#include "spiral_generator.h"
#include <math.h>
double fresnelC(double t) {
    const int steps = 100;
    double sum = 0.0;
    double dt = t / steps;
    for (int i = 0; i < steps; i++) {
        double u1 = i * dt;
        double u2 = (i + 1) * dt;
        sum += (cos(M_PI * u1 * u1 / 2) + cos(M_PI * u2 * u2 / 2)) * dt / 2;
    }
    return sum;
}
double fresnelS(double t) {
    const int steps = 100;
    double sum = 0.0;
    double dt = t / steps;
    for (int i = 0; i < steps; i++) {
        double u1 = i * dt;
        double u2 = (i + 1) * dt;
        sum += (sin(M_PI * u1 * u1 / 2) + sin(M_PI * u2 * u2 / 2)) * dt / 2;
    }
    return sum;
}
void draw_euler(cairo_t *cr, AppData *app_data) {
    if (!cr || !app_data) {
        g_print("Error: Null Cairo context or data in draw_euler\n");
        return;
    }
    int width = gtk_widget_get_width(app_data->drawing_area);
    int height = gtk_widget_get_height(app_data->drawing_area);
    g_print("Drawing Euler with size %d x %d, point %d/%d\n",
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
    cairo_arc(cr, app_data->spiral_data.x[app_data->spiral_data.max_points/2],
              app_data->spiral_data.y[app_data->spiral_data.max_points/2], 4.0, 0, 2 * M_PI);
    cairo_fill(cr);
    cairo_set_source_rgb(cr, 0, 0, 0);
    double scale = 300.0;
    double asymptote_x[2] = {0.5 * scale, -0.5 * scale};
    double asymptote_y[2] = {0.5 * scale, -0.5 * scale};
    for (int i = 0; i < 2; i++) {
        cairo_move_to(cr, asymptote_x[i] - 5, asymptote_y[i] - 5);
        cairo_line_to(cr, asymptote_x[i] + 5, asymptote_y[i] + 5);
        cairo_move_to(cr, asymptote_x[i] - 5, asymptote_y[i] + 5);
        cairo_line_to(cr, asymptote_x[i] + 5, asymptote_y[i] - 5);
        cairo_stroke(cr);
    }
}
