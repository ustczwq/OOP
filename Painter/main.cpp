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
#include <stack>
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_File_Browser.H>
#include "Model_window.h"

// layout
const int WIN_W = 960;
const int WIN_H = 540;
const int MENU_W = 100;
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

    vector<Model_lib::Model *> sm;
    vector<Model_lib::Model *> rm;
    stack<int> rm_nums;

    // widgets
    Button quit_button; // end program
    Button delete_button;
    Button recover_button;
    Menu shape_menu;
    Fl_Menu_Bar* m;
    Model_window::Menubar *menu;

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
    static void cb_recover(Address, Address);

    // menubar callback
    static void menu_open(Fl_Widget* o, void* v);
    static void menu_save(Fl_Widget* o, void* v);
    static void menu_quit(Fl_Widget* o, void* v);
    static void menu_trans(Fl_Widget* o, void* v);
    static void cb_menu_open(Address, Address);
    static void cb_menu_save(Address, Address);
    static void cb_menu_quit(Address, Address);
    static void cb_menu_trans(Address, Address);

};

Shapes_window::Shapes_window(Point xy, int w, int h, const string &title)
    : Window(xy, w, h, title),
      quit_button(Point(x_max() - MENU_W, 0), MENU_W, MENU_H, "@returnarrow  Quit", cb_quit),
      delete_button(Point(x_max() - 3 * MENU_W - 40, 0), MENU_W, MENU_H, "X  Delete", cb_delete),
      recover_button(Point(x_max() - 2 * MENU_W - 40, 0), MENU_W, MENU_H, "@-2undo  Undo", cb_recover),
      shape_menu(Point(x_max() - 7 * MENU_W - 80, 0), MENU_W, MENU_H, Menu::horizontal, "shape"),
      menu(new Model_window::Menubar(0, 0, 150, MENU_H, menu_quit, menu_quit, menu_quit, menu_quit))
{
    attach(quit_button);
    attach(delete_button);
    attach(recover_button);

    shape_menu.attach(new Button(Point(0, 0), 0, 0, "@line  line", cb_line));
    shape_menu.attach(new Button(Point(0, 0), 0, 0, "@-2square  rect", cb_rect));
    shape_menu.attach(new Button(Point(0, 0), 0, 0, "@-2circle  circle", cb_circle));
    shape_menu.attach(new Button(Point(0, 0), 0, 0, "@-1|>  polygon", cb_polygon));

    attach(shape_menu);
    add(menu);
    
}

void Shapes_window::draw_shape(Shapes shape)
{
    switch (shape)
    {
    case circle:
    {
        // s.push_back(new Graph_lib::Circle(Point(x, y), 20));
        Model_lib::Circle *circle = new Model_lib::Circle(0, MENU_H, WIN_W, WIN_H - MENU_H);
        sm.push_back(circle);
        add(circle);
        break;
    }
    case rect:
    {
        Model_lib::Rect *rect = new Model_lib::Rect(0, MENU_H, WIN_W, WIN_H - MENU_H);
        sm.push_back(rect);
        add(rect);
        break;
    }
    case line:
    {
        Model_lib::Line *line = new Model_lib::Line(0, MENU_H, WIN_W, WIN_H - MENU_H);
        sm.push_back(line);
        add(line);
        break;
    }
    case polygon:
    {
        Model_lib::Polygon *polygon = new Model_lib::Polygon(0, MENU_H, WIN_W, WIN_H - MENU_H);
        sm.push_back(polygon);
        add(polygon);
        break;
    }
    default:
        break;
    }

    redraw();
}

void Shapes_window::quit()
{
    hide();
}

void Shapes_window::delete_model()
{
    int num = 0;
    for (int i = sm.size() - 1; i >= 0; i--)
    {
        if (sm[i]->focused())
        {
            remove(sm[i]);
            rm.push_back(sm[i]);
            sm.erase(sm.begin() + i);
            num++;
        }
    }
    if (num > 0)
        rm_nums.push(num);

    redraw();
}

void Shapes_window::recover_model()
{
    if (rm_nums.empty())
        return;

    int num = rm_nums.top();
    rm_nums.pop();

    for (int i = rm.size() - 1; i >= 0 && num > 0; i--)
    {
        add(rm[i]);
        sm.push_back(rm[i]);
        rm.erase(rm.begin() + i);
        num--;
    }
    redraw();
}

void Shapes_window::menu_quit(Fl_Widget* o, void* v)
{
    // hide();
    int *a = (int*) v;
    std::cout << "fuck class" << std::endl;
    printf("%d\n", a);

}

void Shapes_window::menu_open(Fl_Widget* o, void* v)
{
    // hide();
    std::cout << "fuck class" << std::endl;
    std::cout << v << std::endl;

}

void Shapes_window::menu_save(Fl_Widget* o, void* v)
{
    // hide();
    std::cout << "fuck class" << std::endl;
    std::cout << v << std::endl;

}

void Shapes_window::menu_trans(Fl_Widget* o, void* v)
{
    // hide();
    std::cout << "fuck class" << std::endl;
    std::cout << v << std::endl;

}

void Shapes_window::cb_delete(Address, Address pw)
{
    reference_to<Shapes_window>(pw).delete_model();
}

void Shapes_window::cb_recover(Address, Address pw)
{
    reference_to<Shapes_window>(pw).recover_model();
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

void Shapes_window::cb_menu_open(Address, Address pw)
{
    reference_to<Shapes_window>(pw).menu_open(0, 0);
}

void Shapes_window::cb_menu_save(Address, Address pw)
{
    reference_to<Shapes_window>(pw).menu_save(0, 0);
}

void Shapes_window::cb_menu_quit(Address, Address pw)
{
    reference_to<Shapes_window>(pw).menu_quit(0, 0);
}

void Shapes_window::cb_menu_trans(Address, Address pw)
{
    reference_to<Shapes_window>(pw).menu_trans(0, 0);
}

int main()
{
    try
    {
        Shapes_window win(Point(100, 100), WIN_W, WIN_H, "Naive FLTK Painter");

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
