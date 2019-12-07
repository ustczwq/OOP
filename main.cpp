#define _USE_MATH_DEFINES
#include "Simple_window.h"
#include "Graph.h"
#include <iostream>
#include <cmath>
#include "GUI.h"
#include <FL/Fl_Box.H>

// layout
constexpr int xmax = 600;
constexpr int ymax = 400;

const int WIN_W = 800;
const int WIN_H = 450;
const int MENU_W = 80;
const int MENU_H = 50;
 
 
// DRAW SHAPES WINDOW
struct Shapes_window : Graph_lib::Window {
    Shapes_window(Point xy, int w, int h, const string& title);
private:
    // data
    enum Shapes
    {
        circle, square, line
    };
 
    Vector_ref<Shape> s;
 
    // widgets
    Button quit_button; // end program
    In_box draw_pos_x;
    In_box draw_pos_y;
    Out_box xy_out;
    Menu shape_menu;
 
    void draw_shape(Shapes s);
    void quit();

 
    // callback functions
    static void cb_circle(Address, Address);
    static void cb_square(Address, Address);
	static void cb_line(Address, Address);
    static void cb_menu(Address, Address);
    static void cb_quit(Address, Address);
	
};
 
Shapes_window::Shapes_window(Point xy, int w, int h, const string& title)
    :Window(xy, w, h, title),
    quit_button(Point(x_max() - 70, 0), 70, 20, "Quit", cb_quit),
    draw_pos_x(Point(x_max() - 310, 0), 50, 20, "pos x:"),
    draw_pos_y(Point(x_max() - 210, 0), 50, 20, "pos y:"),
    xy_out(Point(100, 0), 100, 20, "drawn at (x,y):"),
    shape_menu(Point(x_max() - 70, 30), 70, 20, Menu::vertical, "shape")
{
    attach(quit_button);
    attach(draw_pos_x);
    attach(draw_pos_y);
    attach(xy_out);
 
    xy_out.put("no shape");
 
	shape_menu.attach(new Button(Point(0, 0), 0, 0, "line", cb_line));
    shape_menu.attach(new Button(Point(0, 0), 0, 0, "circle", cb_circle));
    shape_menu.attach(new Button(Point(0, 0), 0, 0, "square", cb_square));
     
    attach(shape_menu);

}
 
void Shapes_window::draw_shape(Shapes shape)
{
 
    if (draw_pos_x.get_int() == -999999)
    {
        xy_out.put("enter position");
    }
    else {
 
        int x = draw_pos_x.get_int();
        int y = draw_pos_y.get_int();

		// int button = Fl::event_button();
		// x = Fl::event_x();
		// y = Fl::event_y();
 
        switch (shape)
        {
        case circle: { s.push_back(new Circle(Point(x, y), 20)); break; }
        case square: { s.push_back(new Rectangle(Point(x, y), 40, 40)); break; }
		case line:   { s.push_back(new Line(Point(x - 20, y), Point(x + 20, y))); break; }
        }
 
        // update current position readout
        ostringstream ss;
        ss << '(' << x << ',' << y << ')';
        xy_out.put(ss.str());
 
        attach(s[s.size() - 1]);
        redraw();
        
    }
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
 
int main()
{
	try
	{
		Shapes_window win(Point(100, 100), xmax, ymax, "lines");
		return gui_main();
	}
	catch (exception& e) {
		std::cerr << "error: " << e.what() << '\n';
		return 1;
	}
	catch (...) {
		std::cerr << "Unknown exception!\n";
		return 2;
	}
}
