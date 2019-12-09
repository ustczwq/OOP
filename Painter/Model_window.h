#ifndef MODEL_WINDOW_GUARD
#define MODEL_WINDOW_GUARD 1

#include <iostream>
#include <fstream>
#include "Model_window.pb.h"
#include <FL/Fl.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Sys_Menu_Bar.H>
#include "Model.h"
#include "Window.h"
#include "GUI.h"
#include "Graph.h"
#include <stack>
#include <FL/Fl_File_Chooser.H>
#include <FL/Fl_File_Browser.H>


namespace Graph_lib
{

// layout
const int WIN_W = 960;
const int WIN_H = 540;
const int MENU_W = 100;
const int MENU_H = 30;


// MENU BAR
class Menubar : public Fl_Menu_Bar
{
protected:
    Fl_Callback *cb_open;
    Fl_Callback *cb_save;
    Fl_Callback *cb_quit;
    Fl_Callback *cb_trans;

public:
    Menubar(int x, int y, int w, int h, Fl_Callback *cb_open, Fl_Callback *cb_save, Fl_Callback *cb_trans, Fl_Callback *cb_quit)
        : Fl_Menu_Bar(x, y, w, h)
    {
        this->cb_open = cb_open;
        this->cb_save = cb_save;
        this->cb_quit = cb_quit;
        this->cb_trans = cb_trans;

        Fl_Menu_Item menuitems[] = {
            {"&File ", 0, 0, 0, FL_SUBMENU},
            {"@-2fileopen Open  ", FL_CTRL + 'o', cb_open, (void *)1},
            {"@-2filesave Save  ", FL_CTRL + 's', cb_save, (void *)2, FL_MENU_DIVIDER},
            {"E&xit", FL_CTRL + 'q', cb_quit, 0},
            {0},
            {"&Style ", 0, 0, 0, FL_SUBMENU},
            {"&Color ", 0, 0, 0, FL_SUBMENU},
            {"RED     ", 'r', cb_trans, (void *)FL_RED},
            {"Blue    ", 'b', cb_trans, (void *)FL_BLUE},
            {"Green   ", 'g', cb_trans, (void *)FL_GREEN},
            {"Yellow  ", 'y', cb_trans, (void *)FL_YELLOW},
            {"Black   ", 'k', cb_trans, (void *)FL_BLACK},
            {"Cyan    ", 'c', cb_trans, (void *)FL_CYAN},
            {0},
            {"&Line ", 0, 0, 0, FL_SUBMENU},
            {"____   ", 's', cb_trans, (void *)FL_SOLID},
            {". . . .   ", 'd', cb_trans, (void *)FL_DOT},
            {"- - - -   ", 'a', cb_trans, (void *)FL_DASH},
            {"- . - .   ", 'b', cb_trans, (void *)FL_DASHDOT},
            {"- . . -   ", 'c', cb_trans, (void *)FL_DASHDOTDOT},
            {0},
            {0},
            {0}};

        copy(menuitems);
        color(FL_WHITE);
        box(FL_FLAT_BOX);
    }
};


// DRAW SHAPES WINDOW
class Shapes_window : Graph_lib::Window
{
public:
    Shapes_window(Point xy, int w, int h, const string &title);

private:
    // data
    enum Shapes
    {
        line = 1,
        rect = 2,
        circle = 3,
        polygon = 4
    };

    vector<Model_lib::Model *> sm;
    vector<Model_lib::Model *> rm;
    stack<int> rm_nums;

    // widgets
    Graph_lib::Button quit_button; // end program
    Graph_lib::Button delete_button;
    Graph_lib::Button recover_button;
    Graph_lib::Menu shape_menu;
    Fl_Menu_Bar *m;
    Menubar *menu;

    void draw_shape(Shapes s);
    void quit();
    void delete_model();
    void recover_model();

    static vector<Point> protobuf_to_points(mw::Points);
    static vector<Model_lib::Model *> protobuf_to_models(mw::Models);
    static mw::Models models_to_protobuf(vector<Model_lib::Model *>);
    static mw::Window save_to_protobuf(vector<Model_lib::Model *>, vector<Model_lib::Model *>, stack<int>);

    // callback functions
    static void cb_circle(Graph_lib::Address, Graph_lib::Address);
    static void cb_rect(Graph_lib::Address, Graph_lib::Address);
    static void cb_line(Graph_lib::Address, Graph_lib::Address);
    static void cb_menu(Graph_lib::Address, Graph_lib::Address);
    static void cb_quit(Graph_lib::Address, Graph_lib::Address);
    static void cb_polygon(Graph_lib::Address, Graph_lib::Address);
    static void cb_delete(Graph_lib::Address, Graph_lib::Address);
    static void cb_recover(Graph_lib::Address, Graph_lib::Address);

    // menubar callback
    void menu_open(Fl_Widget *o, void *v);
    void menu_save(Fl_Widget *o, void *v);
    void menu_quit(Fl_Widget *o, void *v);
    void menu_trans(Fl_Widget *o, void *v);
    static void cb_menu_open(Fl_Widget *, void *);
    static void cb_menu_save(Fl_Widget *, void *);
    static void cb_menu_quit(Fl_Widget *, void *);
    static void cb_menu_trans(Fl_Widget *, void *);
};

} // namespace Graph_lib

#endif