#ifndef MODEL_GUARD
#define MODEL_GUARD 1

#include <FL/fl_draw.H>
#include <FL/Fl_Widget.H>
#include <FL/Fl.H>
#include <fstream>
#include <iostream>
#include <cmath>
#include "Point.h"
#include "std_lib_facilities.h"
#include <vector>

namespace Model_lib
{

class Model : public Fl_Widget {
public:
    vector<Point> points;
	Model(int x, int y, int w, int h, const char *l=0);
	virtual int handle(int);
    virtual void resize_by_points();
    void draw();
    bool can_resize(int, int);
    void update_points(int, int);
    bool focused() {return this->is_focused;}
    void set_line_color(int color) {this->line_color = color;}
    void set_line_style(int style) {this->line_style = style;}
    void set_all_style();

protected:
	bool is_created;
	bool can_draw;
    bool drag_resize;
    int drag_idx;
    int points_limit;
    bool is_focused;
    int line_color;
    int line_style;

    virtual void draw_shapes();

}; 

class Polygon : public Model
{
public:
    Polygon(int x, int y, int w, int h) :  Model(x, y, w, h) {}
};

class Rect : public Model 
{
public:
    Rect(int x, int y, int w, int h);
    void draw_shapes();
};

class Circle : public Model 
{
public:
    Circle(int x, int y, int w, int h);
    void draw_shapes();
    // void resize_by_points();
};

class Line : public Model 
{
public:
    Line(int x, int y, int w, int h);
    void draw_shapes();
};


}

#endif