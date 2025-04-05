#ifndef SPIRAL_GENERATOR_H
#define SPIRAL_GENERATOR_H

#include <gtk/gtk.h>
#include <cairo.h>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600
#define ANIMATION_STEPS 1000
#define ANIMATION_INTERVAL 20

typedef enum {
    THEODORUS,
    ARCHIMEDEAN,
    FERMAT,
    CALKIN_WILF,
    COTES_ELLIPTIC,
    COTES_PARABOLIC,
    COTES_HYPERBOLIC,
    EULER,
    FIBONACCI,
    FRASER,
    GOLDEN,
    HELIX,
    HYPERBOLIC,
    INVOLUTE,
    LITUUS,
    LOGARITHMIC,
    LOXODROME,
    NIELSEN,
    POINSOT,
    SINUSOIDAL,
    CATENARY,
    OVAL,
    COCHLEOID,
    TANGENT_ARCH,
    CARDIOID,
    KLEIN,
    PENTAGONAL,
    CISSOID,
    CUBIC_TRACTRIX,
    LISSAJOUS,
    BESSEL
} SpiralType;

typedef struct {
    double x[ANIMATION_STEPS + 1];
    double y[ANIMATION_STEPS + 1];
    int max_points;
    int current_point;
} SpiralData;

typedef struct {
    SpiralType type;
    GtkWidget *drawing_area;
    SpiralData spiral_data;
    SpiralData spiral_data_neg;
    guint animation_id;
} AppData;

void draw_theodorus(cairo_t *cr, AppData *app_data);
void draw_archimedean(cairo_t *cr, AppData *app_data);
void draw_fermat(cairo_t *cr, AppData *app_data);
void draw_calkin_wilf(cairo_t *cr, AppData *app_data);
void draw_cotes_elliptic(cairo_t *cr, AppData *app_data);
void draw_cotes_parabolic(cairo_t *cr, AppData *app_data);
void draw_cotes_hyperbolic(cairo_t *cr, AppData *app_data);
void draw_euler(cairo_t *cr, AppData *app_data);
void draw_fibonacci(cairo_t *cr, AppData *app_data);
void draw_fraser(cairo_t *cr, AppData *app_data);
void draw_golden(cairo_t *cr, AppData *app_data);
void draw_helix(cairo_t *cr, AppData *app_data);
void draw_hyperbolic(cairo_t *cr, AppData *app_data);
void draw_involute(cairo_t *cr, AppData *app_data);
void draw_lituus(cairo_t *cr, AppData *app_data);
void draw_logarithmic(cairo_t *cr, AppData *app_data);
void draw_loxodrome(cairo_t *cr, AppData *app_data);
void draw_nielsen(cairo_t *cr, AppData *app_data);
void draw_poinsot(cairo_t *cr, AppData *app_data);
void draw_sinusoidal(cairo_t *cr, AppData *app_data);
void draw_catenary(cairo_t *cr, AppData *app_data);
void draw_oval(cairo_t *cr, AppData *app_data);
void draw_cochleoid(cairo_t *cr, AppData *app_data);
void draw_tangent_arch(cairo_t *cr, AppData *app_data);
void draw_cardioid(cairo_t *cr, AppData *app_data);
void draw_klein(cairo_t *cr, AppData *app_data);
void draw_pentagonal(cairo_t *cr, AppData *app_data);
void draw_cissoid(cairo_t *cr, AppData *app_data);
void draw_cubic_tractrix(cairo_t *cr, AppData *app_data);
void draw_lissajous(cairo_t *cr, AppData *app_data);
void draw_bessel(cairo_t *cr, AppData *app_data);
void setup_gui(GtkApplication *app, AppData *app_data);
void init_spiral_data(AppData *app_data);
double fresnelC(double t);
double fresnelS(double t);
double bessel_j0(double x);

#endif
