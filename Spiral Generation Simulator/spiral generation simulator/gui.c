#include "spiral_generator.h"
#include <stdio.h>
static void on_draw(GtkDrawingArea *area, cairo_t *cr, int width, int height, gpointer data) {
    AppData *app_data = (AppData *)data;
    if (!cr || !app_data) {
        g_print("Error: Invalid drawing context or data\n");
        return;
    }
    switch(app_data->type) {
        case THEODORUS:
            draw_theodorus(cr, app_data);
            break;
        case ARCHIMEDEAN:
            draw_archimedean(cr, app_data);
            break;
        case FERMAT:
            draw_fermat(cr, app_data);
            break;
        case CALKIN_WILF:
            draw_calkin_wilf(cr, app_data);
            break;
        case COTES_ELLIPTIC:
            draw_cotes_elliptic(cr, app_data);
            break;
        case COTES_PARABOLIC:
            draw_cotes_parabolic(cr, app_data);
            break;
        case COTES_HYPERBOLIC:
            draw_cotes_hyperbolic(cr, app_data);
            break;
        case EULER:
            draw_euler(cr, app_data);
            break;
        case FIBONACCI:
            draw_fibonacci(cr, app_data);
            break;
        case FRASER:
            draw_fraser(cr, app_data);
            break;
        case GOLDEN:
            draw_golden(cr, app_data);
            break;
        case HELIX:
            draw_helix(cr, app_data);
            break;
        case HYPERBOLIC:
            draw_hyperbolic(cr, app_data);
            break;
        case INVOLUTE:
            draw_involute(cr, app_data);
            break;
        case LITUUS:
            draw_lituus(cr, app_data);
            break;
        case LOGARITHMIC:
            draw_logarithmic(cr, app_data);
            break;
        case LOXODROME:
            draw_loxodrome(cr, app_data);
            break;
        case NIELSEN:
            draw_nielsen(cr, app_data);
            break;
        case POINSOT:
            draw_poinsot(cr, app_data);
            break;
        case SINUSOIDAL:
            draw_sinusoidal(cr, app_data);
            break;
        case CATENARY:
            draw_catenary(cr, app_data);
            break;
        case OVAL:
            draw_oval(cr, app_data);
            break;
        case COCHLEOID:
            draw_cochleoid(cr, app_data);
            break;
        case TANGENT_ARCH:
            draw_tangent_arch(cr, app_data);
            break;
        case CARDIOID:
            draw_cardioid(cr, app_data);
            break;
        case KLEIN:
            draw_klein(cr, app_data);
            break;
        case PENTAGONAL:
            draw_pentagonal(cr, app_data);
            break;
        case CISSOID:
            draw_cissoid(cr, app_data);
            break;
        case CUBIC_TRACTRIX:
            draw_cubic_tractrix(cr, app_data);
            break;
        case LISSAJOUS:
            draw_lissajous(cr, app_data);
            break;
        case BESSEL:
            draw_bessel(cr, app_data);
            break;
        default:
            g_print("Unknown spiral type\n");
            break;
    }
}
static gboolean animate_spiral(gpointer data) {
    AppData *app_data = (AppData *)data;
    if (app_data->type == LITUUS || app_data->type == POINSOT) {
        if (app_data->spiral_data.current_point < app_data->spiral_data.max_points) {
            app_data->spiral_data.current_point++;
            app_data->spiral_data_neg.current_point++;
            gtk_widget_queue_draw(app_data->drawing_area);
            return TRUE;
        }
    } else if (app_data->spiral_data.current_point < app_data->spiral_data.max_points) {
        app_data->spiral_data.current_point++;
        gtk_widget_queue_draw(app_data->drawing_area);
        return TRUE;
    }
    return FALSE;
}
void init_spiral_data(AppData *app_data) {
    if (app_data->animation_id) {
        g_source_remove(app_data->animation_id);
    }
    app_data->spiral_data.current_point = 0;
    app_data->spiral_data_neg.current_point = 0;
    double scale, theta_max, theta_step;
    int steps = ANIMATION_STEPS;
    switch(app_data->type) {
        case THEODORUS: {
            const int n = 17;
            app_data->spiral_data.max_points = n + 1;
            double theta = 0.0;
            scale = 25.0;
            app_data->spiral_data.x[0] = 0.0;
            app_data->spiral_data.y[0] = 0.0;
            for (int k = 1; k <= n; k++) {
                if (k == 1) {
                    theta = M_PI/2;
                    app_data->spiral_data.x[k] = 0.0 * scale;
                    app_data->spiral_data.y[k] = 1.0 * scale;
                } else {
                    theta -= atan(1.0/sqrt(k-1));
                    app_data->spiral_data.x[k] = app_data->spiral_data.x[k-1] + cos(theta) * scale;
                    app_data->spiral_data.y[k] = app_data->spiral_data.y[k-1] + sin(theta) * scale;
                }
            }
            break;
        }
        case ARCHIMEDEAN: {
            double a = 0.0, b = 0.5;
            theta_max = 10 * M_PI;
            scale = 10.0;
            app_data->spiral_data.max_points = steps + 1;
            theta_step = theta_max / steps;
            for (int i = 0; i <= steps; i++) {
                double theta = i * theta_step;
                double r = (a + b * theta) * scale;
                app_data->spiral_data.x[i] = r * cos(theta);
                app_data->spiral_data.y[i] = r * sin(theta);
            }
            break;
        }
        case FERMAT: {
            double a = 1.0;
            theta_max = 6 * M_PI;
            scale = 25.0;
            int branch_steps = steps / 2;
            app_data->spiral_data.max_points = branch_steps * 2;
            theta_step = theta_max / (branch_steps - 1);
            for (int i = 0; i < branch_steps; i++) {
                double theta = i * theta_step;
                double r = a * sqrt(theta) * scale;
                app_data->spiral_data.x[i] = r * cos(theta);
                app_data->spiral_data.y[i] = r * sin(theta);
            }
            for (int i = 0; i < branch_steps; i++) {
                double theta = -i * theta_step;
                double r = -a * sqrt(-theta) * scale;
                int index = branch_steps + i;
                if (index >= ANIMATION_STEPS + 1) {
                    g_print("Error: Fermat index %d exceeds ANIMATION_STEPS\n", index);
                    break;
                }
                app_data->spiral_data.x[index] = r * cos(theta);
                app_data->spiral_data.y[index] = r * sin(theta);
            }
            g_print("Fermat initialized: max_points=%d, branch_steps=%d\n",
                    app_data->spiral_data.max_points, branch_steps);
            break;
        }
        case CALKIN_WILF: {
            const int n = 50;
            app_data->spiral_data.max_points = n;
            scale = 15.0;
            double num[n], den[n];
            num[0] = 1.0;
            den[0] = 1.0;
            for (int i = 1; i < n; i++) {
                double ratio = num[i-1] / den[i-1];
                double floor_ratio = floor(ratio);
                if (fabs(ratio - floor_ratio) < 1e-10) {
                    num[i] = num[i-1];
                    den[i] = num[i-1] + den[i-1];
                } else {
                    double a = floor_ratio;
                    num[i] = num[i-1] - a * den[i-1];
                    den[i] = den[i-1];
                }
            }
            theta_max = 4 * M_PI;
            theta_step = theta_max / (n - 1);
            for (int i = 0; i < n; i++) {
                double theta = i * theta_step;
                double r = sqrt(i + 1) * scale;
                app_data->spiral_data.x[i] = r * cos(theta);
                app_data->spiral_data.y[i] = r * sin(theta);
            }
            break;
        }
        case COTES_ELLIPTIC: {
            double k = 1.0, p = 0.8 * sqrt(k);
            theta_max = 10 * M_PI;
            scale = 200.0;
            app_data->spiral_data.max_points = steps + 1;
            theta_step = theta_max / steps;
            for (int i = 0; i <= steps; i++) {
                double theta = i * theta_step;
                double r = scale / (p * cosh(k * theta - p * theta));
                app_data->spiral_data.x[i] = r * cos(theta);
                app_data->spiral_data.y[i] = r * sin(theta);
            }
            break;
        }
        case COTES_PARABOLIC: {
            double k = 1.0, p = sqrt(k);
            theta_max = 10 * M_PI;
            scale = 200.0;
            app_data->spiral_data.max_points = steps + 1;
            theta_step = theta_max / steps;
            for (int i = 0; i <= steps; i++) {
                double theta = i * theta_step;
                double r = scale / (1 + p * theta);
                app_data->spiral_data.x[i] = r * cos(theta);
                app_data->spiral_data.y[i] = r * sin(theta);
            }
            break;
        }
        case COTES_HYPERBOLIC: {
            double k = 1.0, p = 1.2 * sqrt(k);
            theta_max = 2 * M_PI;
            scale = 100.0;
            app_data->spiral_data.max_points = steps + 1;
            theta_step = theta_max / steps;
            for (int i = 0; i <= steps; i++) {
                double theta = i * theta_step;
                double cos_val = cos(p * theta - k * theta);
                double r = (fabs(cos_val) < 1e-6) ? 0 : scale / (p * cos_val);
                app_data->spiral_data.x[i] = r * cos(theta);
                app_data->spiral_data.y[i] = r * sin(theta);
            }
            break;
        }
        case EULER: {
            double t_max = 5.0;
            scale = 300.0;
            app_data->spiral_data.max_points = steps + 1;
            theta_step = (2 * t_max) / steps;
            for (int i = 0; i <= steps; i++) {
                double t = -t_max + i * theta_step;
                app_data->spiral_data.x[i] = fresnelC(t) * scale;
                app_data->spiral_data.y[i] = fresnelS(t) * scale;
            }
            break;
        }
        case FIBONACCI: {
            const int n = 20;
            app_data->spiral_data.max_points = n;
            scale = 10.0;
            double phi = (1 + sqrt(5)) / 2;
            double fib[n];
            fib[0] = 1.0;
            fib[1] = 1.0;
            for (int k = 2; k < n; k++) {
                fib[k] = fib[k-1] + fib[k-2];
            }
            for (int i = 0; i < n; i++) {
                double theta = 2 * M_PI * i / phi;
                double r = fib[i] * scale;
                app_data->spiral_data.x[i] = r * cos(theta);
                app_data->spiral_data.y[i] = r * sin(theta);
            }
            break;
        }
        case FRASER: {
            app_data->spiral_data.max_points = steps;
            for (int i = 0; i < steps; i++) {
                app_data->spiral_data.x[i] = 0;
                app_data->spiral_data.y[i] = 0;
            }
            break;
        }
        case GOLDEN: {
            double phi = (1 + sqrt(5)) / 2;
            double b = log(phi) / (M_PI / 2);
            theta_max = 6 * M_PI;
            scale = 0.1;
            app_data->spiral_data.max_points = steps + 1;
            theta_step = theta_max / steps;
            for (int i = 0; i <= steps; i++) {
                double theta = i * theta_step;
                double r = exp(b * theta) * scale;
                app_data->spiral_data.x[i] = r * cos(theta);
                app_data->spiral_data.y[i] = r * sin(theta);
            }
            break;
        }
        case HELIX: {
            double radius = 2.0;
            double pitch = 1.0;
            int n_turns = 3;
            theta_max = 2 * M_PI * n_turns;
            scale = 50.0;
            app_data->spiral_data.max_points = steps + 1;
            theta_step = theta_max / steps;
            double alpha = M_PI / 6;
            for (int i = 0; i <= steps; i++) {
                double theta = i * theta_step;
                double z = pitch * (theta / (2 * M_PI)) * scale;
                double x_3d = radius * cos(theta) * scale;
                double y_3d = radius * sin(theta) * scale;
                app_data->spiral_data.x[i] = x_3d - z * cos(alpha);
                app_data->spiral_data.y[i] = y_3d - z * sin(alpha);
            }
            break;
        }
        case HYPERBOLIC: {
            double a = 5.0;
            double theta_min = 0.1;
            theta_max = 10 * M_PI;
            scale = 10.0;
            app_data->spiral_data.max_points = steps + 1;
            theta_step = (theta_max - theta_min) / steps;
            for (int i = 0; i <= steps; i++) {
                double theta = theta_min + i * theta_step;
                double r = (a / theta) * scale;
                app_data->spiral_data.x[i] = r * cos(theta);
                app_data->spiral_data.y[i] = r * sin(theta);
            }
            break;
        }
        case INVOLUTE: {
            double R = 1.0;
            theta_max = 6 * M_PI;
            scale = 50.0;
            app_data->spiral_data.max_points = steps + 1;
            theta_step = theta_max / steps;
            for (int i = 0; i <= steps; i++) {
                double theta = i * theta_step;
                app_data->spiral_data.x[i] = R * (cos(theta) + theta * sin(theta)) * scale;
                app_data->spiral_data.y[i] = R * (sin(theta) - theta * cos(theta)) * scale;
            }
            break;
        }
        case LITUUS: {
            double a = 2.0;
            double theta_min = 0.1;
            theta_max = 20 * M_PI;
            scale = 50.0;
            app_data->spiral_data.max_points = steps + 1;
            app_data->spiral_data_neg.max_points = steps + 1;
            double log_theta_min = log(theta_min);
            double log_theta_max = log(theta_max);
            theta_step = (log_theta_max - log_theta_min) / steps;
            for (int i = 0; i <= steps; i++) {
                double log_theta = log_theta_min + i * theta_step;
                double theta = exp(log_theta);
                double r_pos = (a / sqrt(theta)) * scale;
                double r_neg = (-a / sqrt(theta)) * scale;
                app_data->spiral_data.x[i] = r_pos * cos(theta);
                app_data->spiral_data.y[i] = r_pos * sin(theta);
                app_data->spiral_data_neg.x[i] = r_neg * cos(theta);
                app_data->spiral_data_neg.y[i] = r_neg * sin(theta);
            }
            break;
        }
        case LOGARITHMIC: {
            double a = 1.0;
            double b = 0.2;
            theta_max = 6 * M_PI;
            scale = 50.0;
            app_data->spiral_data.max_points = steps + 1;
            theta_step = theta_max / steps;
            for (int i = 0; i <= steps; i++) {
                double theta = i * theta_step;
                double r = a * exp(b * theta) * scale;
                app_data->spiral_data.x[i] = r * cos(theta);
                app_data->spiral_data.y[i] = r * sin(theta);
            }
            break;
        }
        case LOXODROME: {
            double R = 1.0;
            double azi_rad = 45 * M_PI / 180;
            double lat0_rad = 0;
            double lon0_rad = 0;
            scale = 200.0;
            app_data->spiral_data.max_points = steps + 1;
            double lat_min = -85 * M_PI / 180;
            double lat_max = 85 * M_PI / 180;
            theta_step = (lat_max - lat_min) / steps;
            for (int i = 0; i <= steps; i++) {
                double lat_rad = lat_min + i * theta_step;
                double delta_lon = tan(azi_rad) * (log(tan(M_PI/4 + lat_rad/2)) - log(tan(M_PI/4 + lat0_rad/2)));
                double lon_rad = lon0_rad + delta_lon;
                app_data->spiral_data.x[i] = R * lon_rad * cos(lat_rad) * scale;
                app_data->spiral_data.y[i] = R * lat_rad * scale;
            }
            break;
        }
        case NIELSEN: {
            int n = 200;
            scale = 200.0;
            app_data->spiral_data.max_points = n;
            theta_step = 2 * M_PI / n;
            for (int i = 0; i < n; i++) {
                double t = i * theta_step;
                app_data->spiral_data.x[i] = cos(t) * scale;
                app_data->spiral_data.y[i] = sin(t) * scale;
            }
            break;
        }
        case POINSOT: {
            double a = 1.0;
            double b = 0.1;
            theta_max = 10 * M_PI;
            scale = 30.0;
            app_data->spiral_data.max_points = steps + 1;
            app_data->spiral_data_neg.max_points = steps + 1;
            theta_step = theta_max / steps;
            for (int i = 0; i <= steps; i++) {
                double t = i * theta_step;
                double r1 = a * exp(b * t);
                double r2 = a * exp(-b * t);
                app_data->spiral_data.x[i] = r1 * cos(t) * scale;
                app_data->spiral_data.y[i] = r1 * sin(t) * scale;
                app_data->spiral_data_neg.x[i] = r2 * cos(t) * scale;
                app_data->spiral_data_neg.y[i] = r2 * sin(t) * scale;
            }
            break;
        }
        case SINUSOIDAL: {
            double a = 100.0;
            double b = 4.0;
            theta_max = 10 * M_PI;
            scale = 1.0;
            app_data->spiral_data.max_points = steps + 1;
            theta_step = theta_max / steps;
            for (int i = 0; i <= steps; i++) {
                double theta = i * theta_step;
                double r = a * sin(b * theta);
                app_data->spiral_data.x[i] = r * cos(theta);
                app_data->spiral_data.y[i] = r * sin(theta);
            }
            break;
        }
        case CATENARY: {
            double a = 50.0;
            double b = 0.1;
            theta_max = 6 * M_PI;
            scale = 1.0;
            app_data->spiral_data.max_points = steps + 1;
            theta_step = theta_max / steps;
            for (int i = 0; i <= steps; i++) {
                double theta = i * theta_step;
                double r = a * cosh(b * theta);
                app_data->spiral_data.x[i] = r * cos(theta);
                app_data->spiral_data.y[i] = r * sin(theta);
            }
            break;
        }
        case OVAL: {
            double a = 100.0;
            double b = 3.0;
            theta_max = 10 * M_PI;
            scale = 1.0;
            app_data->spiral_data.max_points = steps + 1;
            theta_step = theta_max / steps;
            for (int i = 0; i <= steps; i++) {
                double theta = i * theta_step;
                double r = a * cos(b * theta);
                app_data->spiral_data.x[i] = r * cos(theta);
                app_data->spiral_data.y[i] = r * sin(theta);
            }
            break;
        }
        case COCHLEOID: {
            double a = 100.0;
            double theta_min = 0.01;
            theta_max = 20 * M_PI;
            scale = 1.0;
            app_data->spiral_data.max_points = steps + 1;
            theta_step = (theta_max - theta_min) / steps;
            for (int i = 0; i <= steps; i++) {
                double theta = theta_min + i * theta_step;
                double r = a * sin(theta) / theta;
                app_data->spiral_data.x[i] = r * cos(theta);
                app_data->spiral_data.y[i] = r * sin(theta);
            }
            break;
        }
        case TANGENT_ARCH: {
            double theta_min = 0.01;
            theta_max = 3 * M_PI / 2;
            scale = 50.0;
            app_data->spiral_data.max_points = steps + 1;
            theta_step = (theta_max - theta_min) / steps;
            for (int i = 0; i <= steps; i++) {
                double theta = theta_min + i * theta_step;
                double r = tan(theta) * scale;
                app_data->spiral_data.x[i] = r * cos(theta);
                app_data->spiral_data.y[i] = r * sin(theta);
            }
            break;
        }
        case CARDIOID: {
            theta_max = 2 * M_PI;
            scale = 200.0;
            app_data->spiral_data.max_points = steps + 1;
            theta_step = theta_max / steps;
            for (int i = 0; i <= steps; i++) {
                double theta = i * theta_step;
                double r = (1 - sin(theta)) * scale;
                app_data->spiral_data.x[i] = r * cos(theta);
                app_data->spiral_data.y[i] = r * sin(theta);
            }
            break;
        }
        case KLEIN: {
            double a = 10.0;
            double theta_min = 0.01;
            theta_max = 6 * M_PI;
            scale = 1.0;
            app_data->spiral_data.max_points = steps + 1;
            theta_step = (theta_max - theta_min) / steps;
            for (int i = 0; i <= steps; i++) {
                double theta = theta_min + i * theta_step;
                double r = a * theta / sin(theta);
                app_data->spiral_data.x[i] = r * cos(theta);
                app_data->spiral_data.y[i] = r * sin(theta);
            }
            break;
        }
        case PENTAGONAL: {
            const int n = 50;
            app_data->spiral_data.max_points = n;
            scale = 5.0;
            double phi = (1 + sqrt(5)) / 2;
            double angle_step = 2 * M_PI / 5;
            for (int i = 0; i < n; i++) {
                double theta = i * angle_step;
                double r = scale * pow(phi, i / 5.0);
                app_data->spiral_data.x[i] = r * cos(theta);
                app_data->spiral_data.y[i] = r * sin(theta);
            }
            break;
        }
        case CISSOID: {
            double a = 50.0;
            double b = 100.0;
            theta_max = 6 * M_PI;
            scale = 1.0;
            app_data->spiral_data.max_points = steps + 1;
            theta_step = theta_max / steps;
            for (int i = 0; i <= steps; i++) {
                double theta = i * theta_step;
                double r = a * cos(theta) + b;
                app_data->spiral_data.x[i] = r * cos(theta);
                app_data->spiral_data.y[i] = r * sin(theta);
            }
            break;
        }
        case CUBIC_TRACTRIX: {
            double a = 100.0;
            theta_max = 10 * M_PI;
            scale = 1.0;
            app_data->spiral_data.max_points = steps + 1;
            theta_step = theta_max / steps;
            for (int i = 0; i <= steps; i++) {
                double theta = i * theta_step;
                double r = a / sqrt(1 + theta * theta);
                app_data->spiral_data.x[i] = r * cos(theta);
                app_data->spiral_data.y[i] = r * sin(theta);
            }
            break;
        }
        case LISSAJOUS: {
            double A = 100.0;
            double B = 100.0;
            double a_freq = 3.0;
            double b_freq = 2.0;
            double k = 0.001;
            theta_max = 10 * M_PI;
            scale = 1.0;
            app_data->spiral_data.max_points = steps + 1;
            theta_step = theta_max / steps;
            for (int i = 0; i <= steps; i++) {
                double t = i * theta_step;
                double decay = exp(-k * t);
                app_data->spiral_data.x[i] = A * decay * sin(a_freq * t);
                app_data->spiral_data.y[i] = B * decay * sin(b_freq * t);
            }
            break;
        }
        case BESSEL: {
            double a = 0.5;  
            theta_max = 20 * M_PI;  
            scale = 200.0;  
            app_data->spiral_data.max_points = steps + 1;
            theta_step = theta_max / steps;
            for (int i = 0; i <= steps; i++) {
                double t = i * theta_step;
                double r = bessel_j0(a * t);
                app_data->spiral_data.x[i] = r * cos(t) * scale;
                app_data->spiral_data.y[i] = r * sin(t) * scale;
            }
            break;
        }
    }
    app_data->animation_id = g_timeout_add(ANIMATION_INTERVAL, animate_spiral, app_data);
}

static void on_row_activated(GtkListBox *box, GtkListBoxRow *row, gpointer data) {
    AppData *app_data = (AppData *)data;
    gint index = gtk_list_box_row_get_index(row);

    switch(index) {
        case 0: app_data->type = THEODORUS; g_print("Selected Theodorus\n"); break;
        case 1: app_data->type = ARCHIMEDEAN; g_print("Selected Archimedean\n"); break;
        case 2: app_data->type = FERMAT; g_print("Selected Fermat\n"); break;
        case 3: app_data->type = CALKIN_WILF; g_print("Selected Calkin-Wilf\n"); break;
        case 4: app_data->type = COTES_ELLIPTIC; g_print("Selected Cotes Elliptic\n"); break;
        case 5: app_data->type = COTES_PARABOLIC; g_print("Selected Cotes Parabolic\n"); break;
        case 6: app_data->type = COTES_HYPERBOLIC; g_print("Selected Cotes Hyperbolic\n"); break;
        case 7: app_data->type = EULER; g_print("Selected Euler\n"); break;
        case 8: app_data->type = FIBONACCI; g_print("Selected Fibonacci\n"); break;
        case 9: app_data->type = FRASER; g_print("Selected Fraser\n"); break;
        case 10: app_data->type = GOLDEN; g_print("Selected Golden\n"); break;
        case 11: app_data->type = HELIX; g_print("Selected Helix\n"); break;
        case 12: app_data->type = HYPERBOLIC; g_print("Selected Hyperbolic\n"); break;
        case 13: app_data->type = INVOLUTE; g_print("Selected Involute\n"); break;
        case 14: app_data->type = LITUUS; g_print("Selected Lituus\n"); break;
        case 15: app_data->type = LOGARITHMIC; g_print("Selected Logarithmic\n"); break;
        case 16: app_data->type = LOXODROME; g_print("Selected Loxodrome\n"); break;
        case 17: app_data->type = NIELSEN; g_print("Selected Nielsen\n"); break;
        case 18: app_data->type = POINSOT; g_print("Selected Poinsot\n"); break;
        case 19: app_data->type = SINUSOIDAL; g_print("Selected Sinusoidal\n"); break;
        case 20: app_data->type = CATENARY; g_print("Selected Catenary\n"); break;
        case 21: app_data->type = OVAL; g_print("Selected Oval\n"); break;
        case 22: app_data->type = COCHLEOID; g_print("Selected Cochleoid\n"); break;
        case 23: app_data->type = TANGENT_ARCH; g_print("Selected Tangent-Arch\n"); break;
        case 24: app_data->type = CARDIOID; g_print("Selected Cardioid\n"); break;
        case 25: app_data->type = KLEIN; g_print("Selected Klein\n"); break;
        case 26: app_data->type = PENTAGONAL; g_print("Selected Pentagonal\n"); break;
        case 27: app_data->type = CISSOID; g_print("Selected Cissoid\n"); break;
        case 28: app_data->type = CUBIC_TRACTRIX; g_print("Selected Cubic Tractrix\n"); break;
        case 29: app_data->type = LISSAJOUS; g_print("Selected Lissajous\n"); break;
        case 30: app_data->type = BESSEL; g_print("Selected Bessel\n"); break;
    }
    init_spiral_data(app_data);
}
void setup_gui(GtkApplication *app, AppData *app_data) {
    if (!app || !app_data) {
        g_print("Error: Invalid application or data pointer\n");
        return;
    }
    GtkWidget *window = gtk_application_window_new(app);
    if (!window) {
        g_print("Error: Failed to create window\n");
        return;
    }
    gtk_window_set_title(GTK_WINDOW(window), "Spiral Generator");
    gtk_window_set_default_size(GTK_WINDOW(window), WINDOW_WIDTH, WINDOW_HEIGHT);
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    if (!vbox) {
        g_print("Error: Failed to create vertical box\n");
        gtk_window_destroy(GTK_WINDOW(window));
        return;
    }
    gtk_window_set_child(GTK_WINDOW(window), vbox);
    app_data->drawing_area = gtk_drawing_area_new();
    if (!app_data->drawing_area) {
        g_print("Error: Failed to create drawing area\n");
        gtk_window_destroy(GTK_WINDOW(window));
        return;
    }
    gtk_widget_set_hexpand(app_data->drawing_area, TRUE);
    gtk_widget_set_vexpand(app_data->drawing_area, TRUE);
    gtk_box_append(GTK_BOX(vbox), app_data->drawing_area);

    gtk_widget_set_size_request(app_data->drawing_area, WINDOW_WIDTH, WINDOW_HEIGHT - 100);
    gtk_drawing_area_set_draw_func(GTK_DRAWING_AREA(app_data->drawing_area),
                                   on_draw,
                                   app_data,
                                   NULL);
    GtkWidget *scrolled = gtk_scrolled_window_new();
    gtk_widget_set_size_request(scrolled, WINDOW_WIDTH, 100);
    gtk_box_append(GTK_BOX(vbox), scrolled);
    GtkWidget *listbox = gtk_list_box_new();
    gtk_scrolled_window_set_child(GTK_SCROLLED_WINDOW(scrolled), listbox);
    GtkWidget *row1 = gtk_label_new("Theodorus Spiral");
    GtkWidget *row2 = gtk_label_new("Archimedean Spiral");
    GtkWidget *row3 = gtk_label_new("Fermat Spiral");
    GtkWidget *row4 = gtk_label_new("Calkin-Wilf Spiral");
    GtkWidget *row5 = gtk_label_new("Cotes Spiral (Elliptic)");
    GtkWidget *row6 = gtk_label_new("Cotes Spiral (Parabolic)");
    GtkWidget *row7 = gtk_label_new("Cotes Spiral (Hyperbolic)");
    GtkWidget *row8 = gtk_label_new("Euler Spiral");
    GtkWidget *row9 = gtk_label_new("Fibonacci Spiral");
    GtkWidget *row10 = gtk_label_new("Fraser Spiral");
    GtkWidget *row11 = gtk_label_new("Golden Spiral");
    GtkWidget *row12 = gtk_label_new("Helix");
    GtkWidget *row13 = gtk_label_new("Hyperbolic Spiral");
    GtkWidget *row14 = gtk_label_new("Involute of Circle");
    GtkWidget *row15 = gtk_label_new("Lituus Spiral");
    GtkWidget *row16 = gtk_label_new("Logarithmic Spiral");
    GtkWidget *row17 = gtk_label_new("Loxodrome");
    GtkWidget *row18 = gtk_label_new("Nielsen Spiral");
    GtkWidget *row19 = gtk_label_new("Poinsot Spirals");
    GtkWidget *row20 = gtk_label_new("Sinusoidal Spiral");
    GtkWidget *row21 = gtk_label_new("Catenary Spiral");
    GtkWidget *row22 = gtk_label_new("Oval Spiral");
    GtkWidget *row23 = gtk_label_new("Cochleoid Spiral");
    GtkWidget *row24 = gtk_label_new("Tangent-Arch Spiral");
    GtkWidget *row25 = gtk_label_new("Cardioid Spiral");
    GtkWidget *row26 = gtk_label_new("Klein Spiral");
    GtkWidget *row27 = gtk_label_new("Pentagonal Spiral");
    GtkWidget *row28 = gtk_label_new("Cissoid Spiral");
    GtkWidget *row29 = gtk_label_new("Cubic Tractrix Spiral");
    GtkWidget *row30 = gtk_label_new("Lissajous Spiral");
    GtkWidget *row31 = gtk_label_new("Bessel Spiral");
    gtk_list_box_append(GTK_LIST_BOX(listbox), row1);
    gtk_list_box_append(GTK_LIST_BOX(listbox), row2);
    gtk_list_box_append(GTK_LIST_BOX(listbox), row3);
    gtk_list_box_append(GTK_LIST_BOX(listbox), row4);
    gtk_list_box_append(GTK_LIST_BOX(listbox), row5);
    gtk_list_box_append(GTK_LIST_BOX(listbox), row6);
    gtk_list_box_append(GTK_LIST_BOX(listbox), row7);
    gtk_list_box_append(GTK_LIST_BOX(listbox), row8);
    gtk_list_box_append(GTK_LIST_BOX(listbox), row9);
    gtk_list_box_append(GTK_LIST_BOX(listbox), row10);
    gtk_list_box_append(GTK_LIST_BOX(listbox), row11);
    gtk_list_box_append(GTK_LIST_BOX(listbox), row12);
    gtk_list_box_append(GTK_LIST_BOX(listbox), row13);
    gtk_list_box_append(GTK_LIST_BOX(listbox), row14);
    gtk_list_box_append(GTK_LIST_BOX(listbox), row15);
    gtk_list_box_append(GTK_LIST_BOX(listbox), row16);
    gtk_list_box_append(GTK_LIST_BOX(listbox), row17);
    gtk_list_box_append(GTK_LIST_BOX(listbox), row18);
    gtk_list_box_append(GTK_LIST_BOX(listbox), row19);
    gtk_list_box_append(GTK_LIST_BOX(listbox), row20);
    gtk_list_box_append(GTK_LIST_BOX(listbox), row21);
    gtk_list_box_append(GTK_LIST_BOX(listbox), row22);
    gtk_list_box_append(GTK_LIST_BOX(listbox), row23);
    gtk_list_box_append(GTK_LIST_BOX(listbox), row24);
    gtk_list_box_append(GTK_LIST_BOX(listbox), row25);
    gtk_list_box_append(GTK_LIST_BOX(listbox), row26);
    gtk_list_box_append(GTK_LIST_BOX(listbox), row27);
    gtk_list_box_append(GTK_LIST_BOX(listbox), row28);
    gtk_list_box_append(GTK_LIST_BOX(listbox), row29);
    gtk_list_box_append(GTK_LIST_BOX(listbox), row30);
    gtk_list_box_append(GTK_LIST_BOX(listbox), row31);
    g_signal_connect(listbox, "row-activated", G_CALLBACK(on_row_activated), app_data);
    gtk_list_box_select_row(GTK_LIST_BOX(listbox),
                            GTK_LIST_BOX_ROW(gtk_list_box_get_row_at_index(GTK_LIST_BOX(listbox), 0)));
    init_spiral_data(app_data);
    gtk_window_present(GTK_WINDOW(window));
}
