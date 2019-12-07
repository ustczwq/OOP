#include "Model.h"
#include <iostream>

namespace Model_lib
{
    
Model::Model(int X, int Y, int W, int H, const char *l)
    : Fl_Widget(X, Y, W, H, l)
{
    created = false;
    can_draw = false;
}

Model::Model(Fl_Boxtype b, int X, int Y, int W, int H, const char *l)
    : Fl_Widget(X, Y, W, H, l)
{
    created = false;
    can_draw = false;
    box(b);
}

void Model::draw_shapes()
{
}

void Model::draw()
{
    draw_box();
    draw_label();
    draw_shapes();
}

int Model::handle(int event)
{
    int X = Fl::event_x();
    int Y = Fl::event_y();

    if (!created)
    {
        static int x_old, y_old;
        switch (event)
        {
        case FL_PUSH:
        {
            x_old = X;
            y_old = Y;
            can_draw = true;
            return 1;
        }
        case FL_DRAG:
        {
            position(x_old, y_old);
            int w = X - x_old > 1 ? X - x_old : 1;
            int h = Y - y_old > 1 ? Y - y_old : 1;
            size(w, h);
            parent()->redraw();
            break;
            return 1;
        }
        case FL_RELEASE:
        {
            created = true;
            return 1;
        }
        default:
            return 1;
        }
    }
    else
    {
        static int dx, dy;

        switch (event)
        {
        case FL_PUSH:
        {
            can_resize = is_on_right_bottom_corner;
            window()->cursor(can_resize ? FL_CURSOR_DEFAULT : FL_CURSOR_MOVE);
            dx = X - x();
            dy = Y - y();
            return 1;
        }
        case FL_DRAG:
        {
            if (can_resize)
            {
                int W = X > x() + 1 ? X - x() : w();
                int H = Y > y() + 1 ? Y - y() : h();
                size(W, H);
                parent()->redraw();
            }
            else
            {
                window()->cursor(FL_CURSOR_MOVE);
                position(X - dx, Y - dy);
                parent()->redraw();
            }

            return 1;
        }
        case FL_RELEASE:
        {
            can_resize = false;
            window()->cursor(FL_CURSOR_DEFAULT);
            return 1;
        }
        case FL_LEAVE:
        {
            window()->cursor(FL_CURSOR_DEFAULT);
            return 1;
        }
        default:
        {
            int dist_right_border = std::abs(x() + w() - Fl::event_x());
            int dist_bottom_border = std::abs(y() + h() - Fl::event_y());
            is_on_right_bottom_corner = (dist_right_border < 10 && dist_bottom_border < 10);
            window()->cursor(is_on_right_bottom_corner ? FL_CURSOR_SE : FL_CURSOR_DEFAULT);
            return 1;
        }
        }
    }
    return 0;
}

void Rect::draw_shapes()
{
    if (!can_draw)
        return;
    fl_rect(x(), y(), w(), h(), FL_RED);
    int bottom_right_x = w() + x();
    int bottom_right_y = h() + y();
    fl_polygon(bottom_right_x - 6, bottom_right_y - 1,
               bottom_right_x - 1, bottom_right_y - 6,
               bottom_right_x - 1, bottom_right_y - 1);
}

void Line::draw_shapes()
{
    if (!can_draw)
        return;
    int bottom_right_x = w() + x();
    int bottom_right_y = h() + y();
    fl_color(FL_BLUE);
    fl_line(x(), y(), bottom_right_x, bottom_right_y);
}

void Circle::draw_shapes()
{
    if (!can_draw)
        return;
    int bottom_right_x = w() + x();
    int bottom_right_y = h() + y();
    fl_color(FL_DARK_GREEN);
    fl_arc(x(), y(), w(), h(), 0, 360);
    fl_rectf(bottom_right_x - 5, bottom_right_y - 5, 5, 5);
}

void Polygon::draw_shapes()
{
    if (!can_draw || !points.size())
        return;

    if (1 < points.size())
    {
        int i = 1;
        for (i; i < points.size(); ++i)
            fl_line(points[i-1].x,points[i-1].y, points[i].x, points[i].y);

        if (created)
        {
            fl_line(points[i-1].x, points[i-1].y, points[0].x, points[0].y);
            resize_by_points();
        }
        
    }
    else 
        fl_rectf(points[0].x, points[0].y, 2, 2);
    

}

void Polygon::resize_by_points()
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

int Polygon::handle(int event)
{   
    int X = Fl::event_x();
    int Y = Fl::event_y();

    if (!created)
    {
        int button = Fl::event_button();
        if (can_draw && button == FL_RIGHT_MOUSE) 
        {
            created = true;
            parent()->redraw();
            return 0;
        }

        switch (event)
        {
        case FL_PUSH:
        {
            points.push_back(Point(X, Y));
            can_draw = true;
            parent()->redraw();
            return 1;
        }
        case FL_DRAG:
        {
            points[points.size() - 1].x = X;
            points[points.size() - 1].y = Y;
            can_draw = true;
            parent()->redraw();
            return 1;
        }
        case FL_RELEASE:
        {
            return 1;
        }
        default:
            return 1;
        }
    }
    else
    {
        static int dx, dy;
        int idx = -1;
        switch (event)
        {
        case FL_PUSH:
        {
            dx = X - x();
            dy = Y - y();
            return 1;
        }
        case FL_DRAG:
        {
            can_resize = if_resize(X, Y, &idx);
           
            if (can_resize)
            {
                window()->cursor(FL_CURSOR_CROSS);
                points[idx].x = X;
                points[idx].y = Y;
                parent()->redraw();
            }
            else //just move
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
            can_resize = if_resize(X, Y, &idx);
            window()->cursor(can_resize ? FL_CURSOR_CROSS : FL_CURSOR_DEFAULT);
            return 1;
        }
        }
    }
    
    return 0;
}

void Polygon::update_points(int dx, int dy)
{
    for (int i = 0; i < points.size(); i++)
    {
        points[i].x += dx;
        points[i].y += dy;
    }
    
}

bool Polygon::if_resize(int event_x, int event_y, int *idx)
{
    for (int i = 0; i < points.size(); i++)
    {
        int dx = std::abs(event_x - points[i].x);
        int dy = std::abs(event_y - points[i].y);
        if (dx < 10 && dy < 10)
        {
            *idx = i;
            return true;
        }
    }
    return false;

}

} // namespace Model_lib