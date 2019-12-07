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
        rect,
        line,
        polygon
    };

    Vector_ref<Shape> s;
	Vector_ref<Model_lib::Model> sm;

    // widgets
    Button quit_button; // end program
    Button delete_button;
    Menu shape_menu;

    void draw_shape(Shapes s);
    void quit();
    void delete_model();
    void recover_model();

    // callback functions
    static void cb_circle(Address, Address);
    static void cb_rect(Address, Address);
    static void cb_line(Address, Address);
    static void cb_menu(Address, Address);
    static void cb_quit(Address, Address);
    static void cb_polygon(Address, Address);
    static void cb_delete(Address, Address);
};

Shapes_window::Shapes_window(Point xy, int w, int h, const string &title)
    : Window(xy, w, h, title) ,
      quit_button(Point(x_max() - MENU_W, 0), MENU_W, MENU_H, "Quit", cb_quit),
      delete_button(Point(x_max() - 3*MENU_W, 0), MENU_W, MENU_H, "DEL", cb_delete),
      shape_menu(Point(0, 0), MENU_W, MENU_H, Menu::horizontal, "shape")
      
{
    attach(quit_button);
    attach(delete_button);
 
    shape_menu.attach(new Button(Point(0, 0), 0, 0, "@line  line", cb_line));
    shape_menu.attach(new Button(Point(0, 0), 0, 0, "@square  rect", cb_rect));
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
        Model_lib::Circle* circle = new Model_lib::Circle(0, MENU_H, WIN_W, WIN_H - MENU_H);
        sm.push_back(circle);
        add(circle);
        break;
    }
    case rect:
    {
        Model_lib::Rect* rect = new Model_lib::Rect(0, MENU_H, WIN_W, WIN_H - MENU_H);
        sm.push_back(rect);
        add(rect);
        break;
    }
    case line:
    {
        Model_lib::Line* line = new Model_lib::Line(0, MENU_H, WIN_W, WIN_H - MENU_H);
        sm.push_back(line);
        add(line);
        break;
    }
    case polygon:
    {
        Model_lib::Polygon* polygon = new Model_lib::Polygon(0, MENU_H, WIN_W, WIN_H - MENU_H);
        sm.push_back(polygon);
        add(polygon);
        break;
    }
    default: break;
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

void Shapes_window::delete_model()
{
    for (int i = 0; i < sm.size(); i++)
    {
        if (sm[i].focused())
            remove(sm[i]);
    }
    redraw();
}

void Shapes_window::cb_delete(Address, Address pw)
{
    reference_to<Shapes_window>(pw).delete_model();
}

void Shapes_window::cb_circle(Address, Address pw)
{
    reference_to<Shapes_window>(pw).draw_shape(circle);
}

void Shapes_window::cb_rect(Address, Address pw)
{
    reference_to<Shapes_window>(pw).draw_shape(rect);
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
        Shapes_window win(Point(100, 100), 	WIN_W, WIN_H, "Naive FLTK Painter");
		
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
