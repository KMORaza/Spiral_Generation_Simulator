Spiraldiagramm-Simulator (Spiral Generation Simulator) 
---
* Desktop-App zum Simulieren der Generierung mehrerer mathematischer Spiraldiagramme. (Desktop app for simulating generation of several mathematical spirals.)
* Die App besteht aus einer grafischen Benutzeroberfläche und ist vollständig in der C-Programmiersprache geschrieben. (This app has graphical user interface and is written fully in C-language.)


![](https://github.com/KMORaza/Spiral_Generation_Simulator/blob/main/Spiral%20Generation%20Simulator/images/screenshot.png)

![](https://github.com/KMORaza/Spiral_Generation_Simulator/blob/main/Spiral%20Generation%20Simulator/images/001.png)

![](https://github.com/KMORaza/Spiral_Generation_Simulator/blob/main/Spiral%20Generation%20Simulator/images/002.png)

![](https://github.com/KMORaza/Spiral_Generation_Simulator/blob/main/Spiral%20Generation%20Simulator/images/003.png)

![](https://github.com/KMORaza/Spiral_Generation_Simulator/blob/main/Spiral%20Generation%20Simulator/images/004.png)

![](https://github.com/KMORaza/Spiral_Generation_Simulator/blob/main/Spiral%20Generation%20Simulator/images/005.png)

![](https://github.com/KMORaza/Spiral_Generation_Simulator/blob/main/Spiral%20Generation%20Simulator/images/006.png)

![](https://github.com/KMORaza/Spiral_Generation_Simulator/blob/main/Spiral%20Generation%20Simulator/images/007.png)

![](https://github.com/KMORaza/Spiral_Generation_Simulator/blob/main/Spiral%20Generation%20Simulator/images/008.png)

![](https://github.com/KMORaza/Spiral_Generation_Simulator/blob/main/Spiral%20Generation%20Simulator/images/009.png)

![](https://github.com/KMORaza/Spiral_Generation_Simulator/blob/main/Spiral%20Generation%20Simulator/images/010.png)

![](https://github.com/KMORaza/Spiral_Generation_Simulator/blob/main/Spiral%20Generation%20Simulator/images/011.png)

![](https://github.com/KMORaza/Spiral_Generation_Simulator/blob/main/Spiral%20Generation%20Simulator/images/012.png)

![](https://github.com/KMORaza/Spiral_Generation_Simulator/blob/main/Spiral%20Generation%20Simulator/images/013.png)

![](https://github.com/KMORaza/Spiral_Generation_Simulator/blob/main/Spiral%20Generation%20Simulator/images/014.png)

![](https://github.com/KMORaza/Spiral_Generation_Simulator/blob/main/Spiral%20Generation%20Simulator/images/015.png)

![](https://github.com/KMORaza/Spiral_Generation_Simulator/blob/main/Spiral%20Generation%20Simulator/images/016.png)

![](https://github.com/KMORaza/Spiral_Generation_Simulator/blob/main/Spiral%20Generation%20Simulator/images/017.png)

![](https://github.com/KMORaza/Spiral_Generation_Simulator/blob/main/Spiral%20Generation%20Simulator/images/018.png)

![](https://github.com/KMORaza/Spiral_Generation_Simulator/blob/main/Spiral%20Generation%20Simulator/images/019.png)

![](https://github.com/KMORaza/Spiral_Generation_Simulator/blob/main/Spiral%20Generation%20Simulator/images/020.png)

![](https://github.com/KMORaza/Spiral_Generation_Simulator/blob/main/Spiral%20Generation%20Simulator/images/021.png)

![](https://github.com/KMORaza/Spiral_Generation_Simulator/blob/main/Spiral%20Generation%20Simulator/images/022.png)

![](https://github.com/KMORaza/Spiral_Generation_Simulator/blob/main/Spiral%20Generation%20Simulator/images/023.png)

![](https://github.com/KMORaza/Spiral_Generation_Simulator/blob/main/Spiral%20Generation%20Simulator/images/024.png)

![](https://github.com/KMORaza/Spiral_Generation_Simulator/blob/main/Spiral%20Generation%20Simulator/images/025.png)

![](https://github.com/KMORaza/Spiral_Generation_Simulator/blob/main/Spiral%20Generation%20Simulator/images/026.png)

![](https://github.com/KMORaza/Spiral_Generation_Simulator/blob/main/Spiral%20Generation%20Simulator/images/027.png)

![](https://github.com/KMORaza/Spiral_Generation_Simulator/blob/main/Spiral%20Generation%20Simulator/images/028.png)

![](https://github.com/KMORaza/Spiral_Generation_Simulator/blob/main/Spiral%20Generation%20Simulator/images/029.png)

![](https://github.com/KMORaza/Spiral_Generation_Simulator/blob/main/Spiral%20Generation%20Simulator/images/030.png)

![](https://github.com/KMORaza/Spiral_Generation_Simulator/blob/main/Spiral%20Generation%20Simulator/images/031.png)

* I wrote this desktop application completely in C-language using the GTK4 library for the user interface and Cairo for 2D graphics rendering.
* The app allows users to select and visualize various mathematical spirals, simulating their construction point-by-point.
* `spiral_generator.h`: Header file defining constants, enums, structs, and function prototypes.
  * Constants: `WINDOW_WIDTH` (800), `WINDOW_HEIGHT` (600), `ANIMATION_STEPS` (1000), `ANIMATION_INTERVAL` (20 ms).
  * Enum `SpiralType` lists all supported spiral types.
  * Struct `SpiralData` stores x and y coordinates, `max_points`, and `current_point` for simulation.
  * Struct `AppData` combines SpiralType, `drawing_area`, two SpiralData instances (primary and secondary), and `animation_id`.
* `main.c`: Entry point, initializes the GTK application, and sets the default spiral.
* `gui.c`: Handles GUI setup, spiral selection, and simulation logic.
* Spiral-specific files (e.g., `theodorus.c`, `archimedean.c`, etc.): Each implements drawing logic for a specific spiral.
* I have used GTK4’s `GtkApplication`, `GtkWindow`, `GtkBox`, `GtkDrawingArea`, and `GtkListBox` for interface components.
* Cairo draws spirals on the `GtkDrawingArea` using `cairo_t` contexts.



