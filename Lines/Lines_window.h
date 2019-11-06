#ifndef LINES_WINDOW_GUARD
#define LINES_WINDOW_GUARD 1

#include "GUI.h"    // for Simple_window only (doesn't really belong in Window.h)
#include "Graph.h"

using namespace Graph_lib;

struct Lines_window : Graph_lib::Window
{
    Lines_window(Point xy, int w, int h, const string& title);
    Open_polyline lines;

private:
    Button next_button;
    Button quit_button;
    In_box next_x;
    In_box next_y;
    Out_box xy_out;

    void next();
    void quit();

};



#endif