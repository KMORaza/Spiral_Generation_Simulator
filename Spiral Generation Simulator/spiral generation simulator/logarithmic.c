#include "spiral_generator.h"
#include <math.h>
void draw_logarithmic(cairo_t *cr, AppData *app_data) {
    if (!cr || !app_data) {
        g_print("Error: Null Cairo context or data in draw_logarithmic\n");
        return;
    }
    int width = gtk_widget_get_width(app_data->drawing_area);
    int height = gtk_widget_get_height(app_data->drawing_area);
    g_print("Drawing Logarithmic with size %d x %d, point %d/%d\n",
            width, height, app_data->spiral_data.current_point, app_data->spiral_data.max_points);
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_paint(cr);
    cairo_translate(cr, width/2.0, height/2.0);
    cairo_set_source_rgb(cr, 0.83, 0.67, 0.22);
    cairo_set_line_width(cr, 3.0);
    for (int i = 0; i < app_data->spiral_data.current_point && i < app_data->spiral_data.max_points - 1; i++) {
        cairo_move_to(cr, app_data->spiral_data.x[i], app_data->spiral_data.y[i]);
        cairo_line_to(cr, app_data->spiral_data.x[i+1], app_data->spiral_data.y[i+1]);
    }
    cairo_stroke(cr);
    double a = 1.0 * 50.0;
    cairo_set_source_rgb(cr, 0, 0, 0);
    cairo_arc(cr, a, 0, 4.0, 0, 2 * M_PI);
    cairo_fill(cr);
    double b = 0.2;
    double theta_mark = M_PI / 2;
    double r_mark = a * exp(b * theta_mark);
    cairo_set_source_rgb(cr, 1, 0, 0);
    cairo_set_line_width(cr, 1.0);
    cairo_move_to(cr, 0, 0);
    cairo_line_to(cr, r_mark * cos(theta_mark), r_mark * sin(theta_mark));
    cairo_stroke(cr);
    if (app_data->spiral_data.current_point >= 300) {
        cairo_set_source_rgb(cr, 1, 1, 1);
        cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
        cairo_set_font_size(cr, 12.0);
        char growth_label[20];
        snprintf(growth_label, sizeof(growth_label), "Growth rate: b = %.2f", b);
        cairo_move_to(cr, app_data->spiral_data.x[299], app_data->spiral_data.y[299] - 10);
        cairo_show_text(cr, growth_label);
        double angle_deg = atan2(1, b) * 180 / M_PI;
        char angle_label[20];
        snprintf(angle_label, sizeof(angle_label), "Angle: %.1f°", angle_deg);
        cairo_move_to(cr, r_mark * cos(theta_mark) / 2, r_mark * sin(theta_mark) / 2 + 10);
        cairo_show_text(cr, angle_label);
        cairo_set_source_rgb(cr, 0, 0, 0);
        cairo_set_line_width(cr, 2.0);
        cairo_move_to(cr, 2 * a, -2 * a);
        cairo_line_to(cr, 3 * a, -2 * a);
        cairo_stroke(cr);
        cairo_set_source_rgb(cr, 1, 1, 1);
        cairo_move_to(cr, 2.5 * a - 20, -2.3 * a);
        cairo_show_text(cr, "Scale Reference");
    }
}
