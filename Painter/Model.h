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
	Model(int x, int y, int w, int h, const char *l=0);
	Model(Fl_Boxtype b, int X, int Y, int W, int H, const char *l);
	virtual int handle(int);
    void draw();

protected:
    bool can_resize;
    bool is_on_right_bottom_corner;
	bool created;
	bool can_draw;
    virtual void draw_shapes();
}; 

class Rect : public Model 
{
public:
    Rect(int x, int y, int w, int h) :  Model(x, y, w, h) {}
    // void draw();
    // int handle(int event){std::cout << event << std::endl; return 0;}
    void write(std::ostream&){}
    void read(std::istream&){}
    void draw_shapes();
};

class Line : public Model
{
public:
	Line(int x, int y, int w, int h) :  Model(x, y, w, h) {}
    // int handle(int event);
    void write(std::ostream&){}
    void read(std::istream&){}
    void draw_shapes();
};

class Circle : public Model
{
public:
	Circle(int x, int y, int w, int h) :  Model(x, y, w, h) {}
    // int handle(int event);
    void write(std::ostream&){}
    void read(std::istream&){}
    void draw_shapes();
};

class Polygon : public Model
{
public:
    vector<Point> points;
    Polygon(int x, int y, int w, int h) :  Model(x, y, w, h) {}
    void write(std::ostream&){}
    void read(std::istream&){}
    void draw_shapes();
    int handle(int);
    void resize_by_points();
    void update_points(int, int);
    bool if_resize(int, int, int*);
};

}

#endif