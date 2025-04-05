#include "spiral_generator.h"
#include <math.h>
void draw_nielsen(cairo_t *cr, AppData *app_data) {
    if (!cr || !app_data) {
        g_print("Error: Null Cairo context or data in draw_nielsen\n");
        return;
    }
    int width = gtk_widget_get_width(app_data->drawing_area);
    int height = gtk_widget_get_height(app_data->drawing_area);
    g_print("Drawing Nielsen with size %d x %d, point %d/%d\n",
            width, height, app_data->spiral_data.current_point, app_data->spiral_data.max_points);
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_paint(cr);
    cairo_translate(cr, width/2.0, height/2.0);
    int n = 200;
    double scale = 200.0;
    int multiplier = 2;
    cairo_set_line_width(cr, 1.0);
    for (int i = 0; i < app_data->spiral_data.current_point && i < n; i++) {
        double start_x = app_data->spiral_data.x[i];
        double start_y = app_data->spiral_data.y[i];
        int end_idx = (i * multiplier) % n;
        double end_x = app_data->spiral_data.x[end_idx];
        double end_y = app_data->spiral_data.y[end_idx];
        double r = (double)i / n;
        double g = 1.0 - (double)i / n;
        double b = 0.5;
        cairo_set_source_rgb(cr, r, g, b);
        cairo_move_to(cr, start_x, start_y);
        cairo_line_to(cr, end_x, end_y);
        cairo_stroke(cr);
    }
    if (app_data->spiral_data.current_point > 50) {
        cairo_set_source_rgb(cr, 1, 1, 1);
        cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
        cairo_set_font_size(cr, 16.0);
        char title[50];
        snprintf(title, sizeof(title), "Nielsen Spiral (n=%d, m=%d)", n, multiplier);
        cairo_move_to(cr, -scale, -scale - 20);
        cairo_show_text(cr, title);
    }
}
