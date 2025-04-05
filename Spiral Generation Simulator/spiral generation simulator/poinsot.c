#include "spiral_generator.h"
#include <math.h>
void draw_poinsot(cairo_t *cr, AppData *app_data) {
    if (!cr || !app_data) {
        g_print("Error: Null Cairo context or data in draw_poinsot\n");
        return;
    }
    int width = gtk_widget_get_width(app_data->drawing_area);
    int height = gtk_widget_get_height(app_data->drawing_area);
    g_print("Drawing Poinsot with size %d x %d, point %d/%d\n",
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
    for (int i = 0; i < app_data->spiral_data_neg.current_point && i < app_data->spiral_data_neg.max_points - 1; i++) {
        cairo_move_to(cr, app_data->spiral_data_neg.x[i], app_data->spiral_data_neg.y[i]);
        cairo_line_to(cr, app_data->spiral_data_neg.x[i+1], app_data->spiral_data_neg.y[i+1]);
    }
    cairo_stroke(cr);
    if (app_data->spiral_data.current_point > 50) {
        cairo_set_source_rgb(cr, 1, 1, 1);
        cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL, CAIRO_FONT_WEIGHT_NORMAL);
        cairo_set_font_size(cr, 16.0);
        cairo_move_to(cr, -width/2 + 10, -height/2 + 20);
        cairo_show_text(cr, "Poinsot's Spiral");
        cairo_set_font_size(cr, 12.0);
        cairo_set_source_rgb(cr, 0, 0, 1);
        cairo_move_to(cr, -width/2 + 10, -height/2 + 40);
        cairo_show_text(cr, "Outer Spiral");
        cairo_move_to(cr, -width/2 + 10, -height/2 + 40);
        cairo_line_to(cr, -width/2 + 40, -height/2 + 40);
        cairo_stroke(cr);
        cairo_set_source_rgb(cr, 1, 0, 0);
        cairo_move_to(cr, -width/2 + 10, -height/2 + 60);
        cairo_show_text(cr, "Inner Spiral");
        cairo_move_to(cr, -width/2 + 10, -height/2 + 60);
        cairo_line_to(cr, -width/2 + 40, -height/2 + 60);
        cairo_stroke(cr);
    }
}
