#include "spiral_generator.h"
#include <math.h>
double bessel_j0(double x) {
    double sum = 1.0;
    double term = 1.0;
    double x2 = x * x / 4.0;
    int k = 1;
    const int max_terms = 20;
    for (k = 1; k < max_terms; k++) {
        term *= -x2 / (k * k);
        sum += term;
        if (fabs(term) < 1e-10) break;
    }
    return sum;
}
void draw_bessel(cairo_t *cr, AppData *app_data) {
    if (!cr || !app_data) {
        g_print("Error: Null Cairo context or data in draw_bessel\n");
        return;
    }
    int width = gtk_widget_get_width(app_data->drawing_area);
    int height = gtk_widget_get_height(app_data->drawing_area);
    g_print("Drawing Bessel Spiral with size %d x %d, point %d/%d\n",
            width, height, app_data->spiral_data.current_point, app_data->spiral_data.max_points);
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_paint(cr);
    cairo_translate(cr, width/2.0, height/2.0);
    cairo_set_source_rgb(cr, 0.5, 0, 0.5);
    cairo_set_line_width(cr, 2.0);
    for (int i = 0; i < app_data->spiral_data.current_point && i < app_data->spiral_data.max_points - 1; i++) {
        cairo_move_to(cr, app_data->spiral_data.x[i], app_data->spiral_data.y[i]);
        cairo_line_to(cr, app_data->spiral_data.x[i+1], app_data->spiral_data.y[i+1]);
    }
    cairo_stroke(cr);
    if (app_data->spiral_data.current_point > 50) {
        cairo_set_source_rgb(cr, 1, 1, 1);
        cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
        cairo_set_font_size(cr, 16.0);
        cairo_move_to(cr, -width/2 + 10, -height/2 + 20);
        cairo_show_text(cr, "Bessel Spiral (J0)");
    }
}
