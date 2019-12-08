#include "Model.h"
#include <iostream>

namespace Model_lib
{
    
Model::Model(int X, int Y, int W, int H, const char *l)
    : Fl_Widget(X, Y, W, H, l)
{
    is_created = false;
    can_draw = false;
    points_limit = 10;
    is_focused = false;
    line_color = FL_BLACK;
}

void Model::draw_shapes()
{
    if (!can_draw || !points.size()) return;

    if (1 < points.size())
    {
        int i = 1;
        for (i; i < points.size(); ++i)
            fl_line(points[i-1].x, points[i-1].y, points[i].x, points[i].y);
        
        if (is_created)
        {
            fl_line(points[i-1].x, points[i-1].y, points[0].x, points[0].y);
            resize_by_points();
        }
    }
    else if (!is_created)
    {
        fl_rectf(points[0].x - 2, points[0].y - 2 , 4, 4);
    }

}

void Model::resize_by_points()
{
    if (0 < points.size())
    {
        int x_min = points[0].x;
        int x_max = x_min;
        int y_min = points[0].y;
        int y_max = y_min;

        for (unsigned int i = 1; i < points.size(); ++i)
        {
            int x = points[i].x;
            int y = points[i].y;
            if (x < x_min) x_min = x;
            if (x > x_max) x_max = x;
            if (y < y_min) y_min = y;
            if (y > y_max) y_max = y;
        }
        resize(x_min, y_min, x_max - x_min, y_max - y_min);
    }
}

void Model::draw()
{
    draw_box();
    draw_label();
    set_all_style();
    draw_shapes();
}

void Model::set_all_style()
{
    fl_color(line_color);
    fl_line_style(line_style);
    
    if (is_focused)
    {
        for (int i = 0; i < points.size(); i++)
        {
            fl_rectf(points[i].x - 3, points[i].y - 3, 6, 6);
        }
    }
}

int Model::handle(int event)
{
    int X = Fl::event_x();
    int Y = Fl::event_y();

    if (!is_created)    // creating
    {
        int button = Fl::event_button();
        if ((can_draw && button == FL_RIGHT_MOUSE) || points.size() >= points_limit)
        {
            is_created = true;
            parent()->redraw();
            return 0;
        }   // created by right click or limit
        switch (event)
        {
        case FL_PUSH:   // add a point at event position
        {
            can_draw = true;
            points.push_back(Point(X, Y));  
            parent()->redraw();
            return 1;
        }
        case FL_DRAG:   // drag to change a point created
        {
            points[points.size() - 1].x = X;
            points[points.size() - 1].y = Y;
            parent()->redraw();
            return 1;
        }
        default: return 1;
        }
    }
    else  // after created
    {
        static int dx, dy;
        switch (event)
        {       
        case FL_PUSH:   // get distance between cursor and model 
        {
            // std::cout << "push " << event << std::endl;
            dx = X - x();
            dy = Y - y();
            is_focused = !is_focused;
            
            parent()->redraw();
            return 1;
        }
        case FL_DRAG:
        {
            // std::cout << "drag " << event << std::endl;

            drag_idx = -1;
            drag_resize = can_resize(X, Y);
           
            if (drag_resize)    // drag to resize
            {
                // std::cout << drag_resize << " drag to resize " << drag_idx << std::endl;
                window()->cursor(FL_CURSOR_CROSS);
                points[drag_idx].x = X;
                points[drag_idx].y = Y;
                parent()->redraw();
            }
            else    // just move
            {
                window()->cursor(FL_CURSOR_MOVE);
                update_points(X - dx - x(), Y - dy - y());
                parent()->redraw();
            }
            return 1;
        }
        case FL_LEAVE:
        {
            window()->cursor(FL_CURSOR_DEFAULT);
            return 1;
        }
        case FL_RELEASE:
        {
            window()->cursor(FL_CURSOR_DEFAULT);
            return 1;
        }
        default:
        {
            window()->cursor(can_resize(X, Y) ? FL_CURSOR_CROSS : FL_CURSOR_DEFAULT);
            return 1;
        }
        }
    }
    
    return 1;
}

void Model::update_points(int dx, int dy)
{
    for (int i = 0; i < points.size(); i++)
    {
        points[i].x += dx;
        points[i].y += dy;
    }
    
}

bool Model::can_resize(int event_x, int event_y)
{
    for (int i = 0; i < points.size(); i++)
    {
        int dx = std::abs(event_x - points[i].x);
        int dy = std::abs(event_y - points[i].y);
        if (dx < 15 && dy < 15)
        {
            drag_idx = i;
            return true;
        }
    }
    return false;
}

Rect::Rect(int x, int y, int w, int h) :  Model(x, y, w, h) 
{
    points_limit = 2;
}

void Rect::draw_shapes()
{
    if (!can_draw || !points.size()) return;

    if (1 < points.size())
    {
        int x1 = points[0].x;
        int y1 = points[0].y;
        int x2 = points[1].x;
        int y2 = points[1].y;

        int x = x1 < x2 ? x1 : x2;
        int y = y1 < y2 ? y1 : y2;
        int w = std::abs(x2 - x1);
        int h = std::abs(y2 - y1);

        fl_rect(x, y, w, h);
        // resize_by_points();
        resize(x, y, w, h);
    }
    else if (!is_created)
    {
        fl_rectf(points[0].x - 2, points[0].y - 2 , 4, 4);
    }
}

Circle::Circle(int x, int y, int w, int h) :  Model(x, y, w, h) 
{
    points_limit = 2;
}

void Circle::draw_shapes()
{
    if (!can_draw || !points.size()) return;

    if (1 < points.size())
    {
        int x1 = points[0].x;
        int y1 = points[0].y;
        int x2 = points[1].x;
        int y2 = points[1].y;

        int x = x1 < x2 ? x1 : x2;
        int y = y1 < y2 ? y1 : y2;
        int w = std::abs(x2 - x1);
        int h = std::abs(y2 - y1);
        fl_arc(x, y, w, h, 0, 360);
        
        resize(x, y, w, h);
    }
    else if (!is_created)
    {
        fl_rectf(points[0].x - 2, points[0].y - 2 , 4, 4);
    }

}

Line::Line(int x, int y, int w, int h) :  Model(x, y, w, h) 
{
    points_limit = 2;
}

void Line::draw_shapes()
{
    if (!can_draw || !points.size()) return;

    if (1 < points.size())
    {
        int x1 = points[0].x;
        int y1 = points[0].y;
        int x2 = points[1].x;
        int y2 = points[1].y;

        fl_line(x1, y1, x2, y2);

        int x = x1 < x2 ? x1 : x2;
        int y = y1 < y2 ? y1 : y2;
        int w = std::abs(x2 - x1);
        int h = std::abs(y2 - y1);
        
        resize(x, y, w, h);
    }
    else if (!is_created)
    {
        fl_rectf(points[0].x - 2, points[0].y - 2 , 4, 4);
    }
}

} // namespace Model_lib