#include "spiral_generator.h"
#include <math.h>
void draw_loxodrome(cairo_t *cr, AppData *app_data) {
    if (!cr || !app_data) {
        g_print("Error: Null Cairo context or data in draw_loxodrome\n");
        return;
    }
    int width = gtk_widget_get_width(app_data->drawing_area);
    int height = gtk_widget_get_height(app_data->drawing_area);
    g_print("Drawing Loxodrome with size %d x %d, point %d/%d\n",
            width, height, app_data->spiral_data.current_point, app_data->spiral_data.max_points);
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_paint(cr);
    cairo_translate(cr, width/2.0, height/2.0);
    double R = 200.0;
    cairo_set_source_rgb(cr, 0.7, 0.7, 0.7);
    cairo_set_line_width(cr, 1.0);
    cairo_arc(cr, 0, 0, R, 0, 2 * M_PI);
    cairo_stroke(cr);
    for (double lon = -M_PI; lon <= M_PI; lon += M_PI/2) {
        for (double lat = -M_PI/2; lat <= M_PI/2; lat += 0.1) {
            double x = R * cos(lon) * cos(lat);
            double y = R * sin(lat);
            if (lat == -M_PI/2) cairo_move_to(cr, x, y);
            else cairo_line_to(cr, x, y);
        }
        cairo_stroke(cr);
    }
    cairo_set_source_rgb(cr, 0, 0, 1);
    cairo_set_line_width(cr, 3.0);
    for (int i = 0; i < app_data->spiral_data.current_point && i < app_data->spiral_data.max_points - 1; i++) {
        cairo_move_to(cr, app_data->spiral_data.x[i], app_data->spiral_data.y[i]);
        cairo_line_to(cr, app_data->spiral_data.x[i+1], app_data->spiral_data.y[i+1]);
    }
    cairo_stroke(cr);
    if (app_data->spiral_data.current_point > 100) {
        cairo_set_source_rgb(cr, 1, 1, 1);
        cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
        cairo_set_font_size(cr, 16.0);
        cairo_move_to(cr, -R + 10, -R - 10);
        cairo_show_text(cr, "Loxodrome (α = 45°)");
    }
}
