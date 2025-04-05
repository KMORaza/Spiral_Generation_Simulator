#include "spiral_generator.h"
#include <math.h>
void draw_lituus(cairo_t *cr, AppData *app_data) {
    if (!cr || !app_data) {
        g_print("Error: Null Cairo context or data in draw_lituus\n");
        return;
    }
    int width = gtk_widget_get_width(app_data->drawing_area);
    int height = gtk_widget_get_height(app_data->drawing_area);
    g_print("Drawing Lituus with size %d x %d, point %d/%d\n",
            width, height, app_data->spiral_data.current_point, app_data->spiral_data.max_points);
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_paint(cr);
    cairo_translate(cr, width/2.0, height/2.0);
    cairo_set_source_rgb(cr, 0, 0.4, 0.8);
    cairo_set_line_width(cr, 3.0);
    for (int i = 0; i < app_data->spiral_data.current_point && i < app_data->spiral_data.max_points - 1; i++) {
        cairo_move_to(cr, app_data->spiral_data.x[i], app_data->spiral_data.y[i]);
        cairo_line_to(cr, app_data->spiral_data.x[i+1], app_data->spiral_data.y[i+1]);
    }
    cairo_stroke(cr);
    cairo_set_source_rgb(cr, 0.8, 0.2, 0.2);
    cairo_set_line_width(cr, 3.0);
    for (int i = 0; i < app_data->spiral_data_neg.current_point && i < app_data->spiral_data_neg.max_points - 1; i++) {
        cairo_move_to(cr, app_data->spiral_data_neg.x[i], app_data->spiral_data_neg.y[i]);
        cairo_line_to(cr, app_data->spiral_data_neg.x[i+1], app_data->spiral_data_neg.y[i+1]);
    }
    cairo_stroke(cr);
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_arc(cr, 0, 0, 5.0, 0, 2 * M_PI);
    cairo_fill(cr);
    double a = 2.0 * 50.0;
    double angles[4] = {M_PI/2, M_PI, 3*M_PI/2, 2*M_PI};
    cairo_set_source_rgb(cr, 0, 0, 0);
    for (int i = 0; i < 4; i++) {
        double theta = angles[i];
        double r_mark = a / sqrt(theta);
        double x_mark = r_mark * cos(theta);
        double y_mark = r_mark * sin(theta);
        cairo_arc(cr, x_mark, y_mark, 2.5, 0, 2 * M_PI);
        cairo_fill(cr);
        cairo_set_source_rgb(cr, 1, 1, 1);
        cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
        cairo_set_font_size(cr, 12.0);
        char label[20];
        if (theta == M_PI/2) snprintf(label, sizeof(label), "θ = π/2");
        else if (theta == M_PI) snprintf(label, sizeof(label), "θ = π");
        else if (theta == 3*M_PI/2) snprintf(label, sizeof(label), "θ = 3π/2");
        else snprintf(label, sizeof(label), "θ = 2π");
        cairo_move_to(cr, x_mark * 1.1, y_mark * 1.1);
        cairo_show_text(cr, label);
    }
    if (app_data->spiral_data.current_point > 100) {
        cairo_set_source_rgb(cr, 1, 1, 1);
        cairo_set_font_size(cr, 16.0);
        cairo_move_to(cr, 125, 190);
        cairo_show_text(cr, "r² = a²/θ");
    }
}
