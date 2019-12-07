#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>
#include <FL/fl_draw.H>
#include <cmath>
#include <iostream>
#include "Model.h"
#include "Window.h"
#include "GUI.h"
#include "Graph.h"
#include <FL/Fl_Sys_Menu_Bar.H>
#include <FL/Fl_Button.H>
#include "Simple_window.h"

// layout
const int WIN_W = 960;
const int WIN_H = 540;
const int MENU_W = 120;
const int MENU_H = 30;

// DRAW SHAPES WINDOW
struct Shapes_window : Graph_lib::Window
{
    Shapes_window(Point xy, int w, int h, const string &title);

private:
    // data
    enum Shapes
    {
        circle,
        square,
        line,
        polygon
    };

    Vector_ref<Shape> s;
	Vector_ref<Model_lib::Model> sm;

    // widgets
    Button quit_button; // end program
    Menu shape_menu;

    void draw_shape(Shapes s);
    void quit();

    // callback functions
    static void cb_circle(Address, Address);
    static void cb_square(Address, Address);
    static void cb_line(Address, Address);
    static void cb_menu(Address, Address);
    static void cb_quit(Address, Address);
    static void cb_polygon(Address, Address);
};

Shapes_window::Shapes_window(Point xy, int w, int h, const string &title)
    : Window(xy, w, h, title) ,
      quit_button(Point(x_max() - MENU_W, 0), MENU_W, MENU_H, "Quit", cb_quit),
      shape_menu(Point(0, 0), MENU_W, MENU_H, Menu::horizontal, "shape")
      
{
    attach(quit_button);
 
    shape_menu.attach(new Button(Point(0, 0), 0, 0, "@line  line", cb_line));
    shape_menu.attach(new Button(Point(0, 0), 0, 0, "@square  rect", cb_square));
    shape_menu.attach(new Button(Point(0, 0), 0, 0, "@circle  circle", cb_circle));
    shape_menu.attach(new Button(Point(0, 0), 0, 0, "@|>  polygon", cb_polygon));

    attach(shape_menu);
}

void Shapes_window::draw_shape(Shapes shape)
{
    switch (shape)
    {
    case circle:
    {
        // s.push_back(new Graph_lib::Circle(Point(x, y), 20));
        add(new Model_lib::Circle(0, MENU_H, WIN_W, WIN_H - MENU_H));
        break;
    }
    case square:
    {
        // sm.push_back(new Rect(x - 30, y - 20, x + 20, y + 20));
        add(new Model_lib::Rect(0, MENU_H, WIN_W, WIN_H - MENU_H));
    
        // s.push_back(new Rect(x - 30, y - 20, x + 20, y + 20));
        break;
    }
    case line:
    {
        add(new Model_lib::Line(0, MENU_H, WIN_W, WIN_H - MENU_H));
        // s.push_back(new Graph_lib::Line(Point(x - 20, y), Point(x + 20, y)));
        break;
    }
    case polygon:
    {
        add(new Model_lib::Polygon(0, MENU_H, WIN_W, WIN_H - MENU_H));
        // s.push_back(new Graph_lib::Line(Point(x - 20, y), Point(x + 20, y)));
        break;
    }
    }

    // update current position readout

    // attach(s[s.size() - 1]);
    // attach(sm[sm.size() - 1]);
    redraw();

}

void Shapes_window::quit()
{
    hide();
}

void Shapes_window::cb_circle(Address, Address pw)
{
    reference_to<Shapes_window>(pw).draw_shape(circle);
}

void Shapes_window::cb_square(Address, Address pw)
{
    reference_to<Shapes_window>(pw).draw_shape(square);
}

void Shapes_window::cb_line(Address, Address pw)
{
    reference_to<Shapes_window>(pw).draw_shape(line);
}

void Shapes_window::cb_quit(Address, Address pw)
{
    reference_to<Shapes_window>(pw).quit();
}

void Shapes_window::cb_polygon(Address, Address pw)
{
    reference_to<Shapes_window>(pw).draw_shape(polygon);
}

int main()
{
    try
    {
        Shapes_window win(Point(100, 100), 	WIN_W, WIN_H, "lines");
		
        return gui_main();
    }
    catch (exception &e)
    {
        std::cerr << "error: " << e.what() << '\n';
        return 1;
    }
    catch (...)
    {
        std::cerr << "Unknown exception!\n";
        return 2;
    }
}
