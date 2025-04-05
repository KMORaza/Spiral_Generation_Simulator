#include "spiral_generator.h"
#include <math.h>
void draw_golden(cairo_t *cr, AppData *app_data) {
    if (!cr || !app_data) {
        g_print("Error: Null Cairo context or data in draw_golden\n");
        return;
    }
    int width = gtk_widget_get_width(app_data->drawing_area);
    int height = gtk_widget_get_height(app_data->drawing_area);
    g_print("Drawing Golden with size %d x %d, point %d/%d\n",
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
    double phi = (1 + sqrt(5)) / 2;
    double a = 1.0 * 50.0;
    double rectangles[4][4] = {
        {1, 0, 0, 1},
        {0, -1, 1, 0},
        {-1, 0, 0, -1},
        {0, 1, -1, 0}
    };
    int num_rectangles = app_data->spiral_data.current_point / 100;
    if (num_rectangles > 12) num_rectangles = 12;
    cairo_set_source_rgb(cr, 0, 0, 1);
    cairo_set_line_width(cr, 1.0);
    for (int k = 0; k < num_rectangles; k++) {
        double w = (k % 2 == 0) ? a : a * phi;
        double h = (k % 2 == 0) ? a * phi : a;
        double rect_x[5] = {0, w, w, 0, 0};
        double rect_y[5] = {0, 0, h, h, 0};
        int quadrant = k % 4;
        double M[2][2] = {{rectangles[quadrant][0], rectangles[quadrant][1]},
                          {rectangles[quadrant][2], rectangles[quadrant][3]}};
        double rotated_x[5], rotated_y[5];
        for (int i = 0; i < 5; i++) {
            rotated_x[i] = M[0][0] * rect_x[i] + M[0][1] * rect_y[i];
            rotated_y[i] = M[1][0] * rect_x[i] + M[1][1] * rect_y[i];
        }
        for (int i = 0; i < 4; i++) {
            cairo_move_to(cr, rotated_x[i], rotated_y[i]);
            cairo_line_to(cr, rotated_x[i+1], rotated_y[i+1]);
        }
        cairo_stroke(cr);
        a *= phi;
    }
    a = 1.0 * 50.0;
    cairo_set_source_rgb(cr, 0, 1, 0);
    cairo_set_line_width(cr, 1.5);
    for (int k = 0; k < num_rectangles; k++) {
        int points_per_arc = 50;
        for (int i = 0; i < points_per_arc - 1; i++) {
            double theta1 = (k - 1) * M_PI / 2 + i * (M_PI / 2) / (points_per_arc - 1);
            double theta2 = (k - 1) * M_PI / 2 + (i + 1) * (M_PI / 2) / (points_per_arc - 1);
            double r1 = a * pow(phi, theta1 / (M_PI / 2));
            double r2 = a * pow(phi, theta2 / (M_PI / 2));
            int quadrant = k % 4;
            double x1, y1, x2, y2;
            if (quadrant == 0) {
                x1 = r1 * cos(theta1); y1 = r1 * sin(theta1);
                x2 = r2 * cos(theta2); y2 = r2 * sin(theta2);
            } else if (quadrant == 1) {
                x1 = -r1 * sin(theta1); y1 = r1 * cos(theta1);
                x2 = -r2 * sin(theta2); y2 = r2 * cos(theta2);
            } else if (quadrant == 2) {
                x1 = -r1 * cos(theta1); y1 = -r1 * sin(theta1);
                x2 = -r2 * cos(theta2); y2 = -r2 * sin(theta2);
            } else {
                x1 = r1 * sin(theta1); y1 = -r1 * cos(theta1);
                x2 = r2 * sin(theta2); y2 = -r2 * cos(theta2);
            }
            cairo_move_to(cr, x1, y1);
            cairo_line_to(cr, x2, y2);
        }
        cairo_stroke(cr);
        a *= phi;
    }
}
