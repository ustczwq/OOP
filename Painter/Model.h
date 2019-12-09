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

class Model : public Fl_Widget
{
public:
    Model(int x, int y, int w, int h, const char *l = 0, const int id = 0);
    virtual int handle(int);
    virtual void resize_by_points();
    void draw();
    void set_all_style();
    bool can_resize(int, int);
    void update_points(int, int);

    void set_points(vector<Point> ps) { this->points =  ps; }
    void set_draw(int l = 10, bool is = false, bool can = false) 
    { this->points_limit = l; this->is_created = is; this->can_draw = can;}

    void set_line_color(int color) { this->line_color = color; }
    void set_line_style(int style) { this->line_style = style; }
    
    vector<Point> get_points() { return this->points; }
    int get_points_limit() { return this->points_limit; }
    bool get_is_created() { return this->is_created; }
    bool get_can_draw() { return this->can_draw; }
    bool get_drag_resize() { return this->drag_resize; }
    int get_drag_idx() { return this->drag_idx; }
    int get_line_color() { return this->line_color; }
    int get_line_style() { return this->line_style; }
    bool get_is_focused() { return this->is_focused; }
    int get_shape_id() { return this->shape_id; }

protected:
    vector<Point> points;
    int points_limit;
    bool is_created;
    bool can_draw;
    bool drag_resize;
    int drag_idx;
    int line_color;
    int line_style;
    bool is_focused;
    int shape_id;

    virtual void draw_shapes();
};

class Polygon : public Model
{
public:
    Polygon(int x, int y, int w, int h, const char* l, const int id) : Model(x, y, w, h, l, id) {}
};

class Rect : public Model
{
public:
    Rect(int x, int y, int w, int h, const char* l, const int id);
    void draw_shapes();
};

class Circle : public Model
{
public:
    Circle(int x, int y, int w, int h, const char* l, const int id);
    void draw_shapes();
};

class Line : public Model
{
public:
    Line(int x, int y, int w, int h, const char* l, const int id);
    void draw_shapes();
};

} // namespace Model_lib

#endif