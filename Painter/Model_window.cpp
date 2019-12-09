#include "Model_window.h"

namespace Graph_lib
{

Shapes_window::Shapes_window(Point xy, int w, int h, const string &title)
    : Window(xy, w, h, title),
      quit_button(Point(x_max() - MENU_W, 0), MENU_W, MENU_H, "@returnarrow  Quit", cb_quit),
      delete_button(Point(x_max() - 3 * MENU_W - 40, 0), MENU_W, MENU_H, "X  Delete", cb_delete),
      recover_button(Point(x_max() - 2 * MENU_W - 40, 0), MENU_W, MENU_H, "@-2undo  Undo", cb_recover),
      shape_menu(Point(x_max() - 7 * MENU_W - 80, 0), MENU_W, MENU_H, Menu::horizontal, "shape"),
      menu(new Menubar(0, 0, 150, MENU_H, cb_menu_open, cb_menu_save, cb_menu_trans, cb_menu_quit))
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
        Model_lib::Circle *c = new Model_lib::Circle(0, MENU_H, WIN_W, WIN_H - MENU_H, 0, circle);
        sm.push_back(c);
        add(c);
        break;
    }
    case rect:
    {
        Model_lib::Rect *r = new Model_lib::Rect(0, MENU_H, WIN_W, WIN_H - MENU_H, 0, rect);
        sm.push_back(r);
        add(r);
        break;
    }
    case line:
    {
        Model_lib::Line *l = new Model_lib::Line(0, MENU_H, WIN_W, WIN_H - MENU_H, 0, line);
        sm.push_back(l);
        add(l);
        break;
    }
    case polygon:
    {
        Model_lib::Polygon *p = new Model_lib::Polygon(0, MENU_H, WIN_W, WIN_H - MENU_H, 0, polygon);
        sm.push_back(p);
        add(p);
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

vector<Point> Shapes_window::protobuf_to_points(mw::Points ps)
{
    vector<Point> points;
    
    for (int i = 0; i < ps.points_size(); i++)
    {
        points.push_back(Point(ps.points(i).x(), ps.points(i).y()));
    }
    return points;
}

vector<Model_lib::Model *> Shapes_window::protobuf_to_models(mw::Models ms)
{
    vector<Model_lib::Model *> models;

    for (int i = models.size() - 1; i >= 0; i--)
    {
        models.erase(models.begin() + i);
    }

    for (int i = 0; i < ms.models_size(); i++)
    {
        int x = ms.models(i).x();
        int y = ms.models(i).y();
        int w = ms.models(i).w();
        int h = ms.models(i).h();
        int id = ms.models(i).shape_id();
        int lim = ms.models(i).points_limit();
        bool is = ms.models(i).is_created();
        bool can = ms.models(i).can_draw();
        int color = ms.models(i).line_color();
        int style = ms.models(i).line_style();
        vector<Point> points = protobuf_to_points(ms.models(i).points());

        switch (id)
        {
        case line:
        {
            Model_lib::Line *l = new Model_lib::Line(x, y, w, h, 0, id);
            l->set_draw(lim, is, can);
            l->set_line_color(color);
            l->set_line_style(style);
            l->set_points(points);
            l->resize_by_points();
            models.push_back(l);
            break;
        }
        case rect:
        {
            Model_lib::Rect *r = new Model_lib::Rect(x, y, w, h, 0, id);
            r->set_draw(lim, is, can);
            r->set_line_color(color);
            r->set_line_style(style);
            r->set_points(points);
            r->resize_by_points();
            models.push_back(r);
            break;
        }
        case circle:
        {
            Model_lib::Circle *c = new Model_lib::Circle(x, y, w, h, 0, id);
            c->set_draw(lim, is, can);
            c->set_line_color(color);
            c->set_line_style(style);
            c->set_points(points);
            c->resize_by_points();
            models.push_back(c);
            break;
        }
        case polygon:
        {
            Model_lib::Polygon *p = new Model_lib::Polygon(x, y, w, h, 0, id);
            p->set_draw(lim, is, can);
            p->set_line_color(color);
            p->set_line_style(style);
            p->set_points(points);
            p->resize_by_points();
            models.push_back(p);
            break;
        }
        default:
            break;
        }
    }

    return models;
}

mw::Models Shapes_window::models_to_protobuf(vector<Model_lib::Model *> ms)
{
    mw::Models models;
    mw::Model* model;

    for (int i = 0; i < ms.size(); i++)
    {
        model = models.add_models();
        model->set_x(ms[i]->x());
        model->set_y(ms[i]->y());
        model->set_w(ms[i]->w());
        model->set_h(ms[i]->h());
        model->set_points_limit(ms[i]->get_points_limit());
        model->set_is_created(ms[i]->get_is_created());
        model->set_can_draw(ms[i]->get_can_draw());
        model->set_drag_resize(ms[i]->get_drag_resize());
        model->set_drag_idx(ms[i]->get_drag_idx());
        model->set_line_color(ms[i]->get_line_color());
        model->set_line_style(ms[i]->get_line_style());
        model->set_is_focused(ms[i]->get_is_focused());
        model->set_shape_id(ms[i]->get_shape_id());

        mw::Points points;
        mw::Point* point;
        vector<Point> ps = ms[i]->get_points();
        for (int j = 0; j < ps.size(); j++)
        {
            point = points.add_points();
            point->set_x(ps[j].x);
            point->set_y(ps[j].y);
        }

        model->mutable_points()->MergeFrom(points);
    }

    return models;
} 

mw::Window Shapes_window::save_to_protobuf(vector<Model_lib::Model *> saved, vector<Model_lib::Model *> removed, stack<int> rm_nums)
{
    mw::Window win;
    mw::Num* num;
    mw::Models s = models_to_protobuf(saved);
    mw::Models r = models_to_protobuf(removed);
    win.mutable_sm()->MergeFrom(s);
    win.mutable_rm()->MergeFrom(r);

    stack<int> _nums = rm_nums;
    while (!_nums.empty())
    {
        num = win.add_nums();
        num->set_num(_nums.top());
        _nums.pop();
    }

    return win;
}

void Shapes_window::delete_model()
{
    int num = 0;
    for (int i = sm.size() - 1; i >= 0; i--)
    {
        if (sm[i]->get_is_focused())
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

void Shapes_window::menu_quit(Fl_Widget *o, void *v)
{
    hide();
}

void Shapes_window::menu_open(Fl_Widget *o, void *v)
{
    char *filename = fl_file_chooser("./", "*.pb", "");
    if (!filename) return;

    for (int i = sm.size() - 1; i >=0; i--)
    {
        remove(sm[i]);
        sm.erase(sm.begin() + i);
    }
 
    mw::Window win;
    fstream input(filename, ios::in | ios::binary);
    if (!win.ParseFromIstream(&input))
    {
        std::cerr << "failed to open" << std::endl;
    }
    else
    {
        stack<int> nums;
        for (int i = win.nums_size() - 1; i >=0; i--)
            nums.push(win.nums(i).num());
        rm_nums = nums;

        mw::Models s = win.sm();
        mw::Models r = win.rm();
        sm = protobuf_to_models(s);
        rm = protobuf_to_models(r);
    }

    for (int i = sm.size() - 1; i >= 0; i--)
    {
        add(sm[i]);
    }

    redraw();
    
}

void Shapes_window::menu_save(Fl_Widget *o, void *v)
{
    char *newfile = fl_file_chooser("Save file as?", "*.pb", "untitled.pb");
    if (!newfile) return;

    mw::Window win = save_to_protobuf(sm, rm, rm_nums);
    fstream output(newfile, ios::out | ios::trunc | ios::binary);

    if (!win.SerializeToOstream(&output))
    {
        std::cerr << "failed to save .pb" << std::endl;
    }
    else
    {
        std::cout << "save successfully" << std::endl;
    }

}

void Shapes_window::menu_trans(Fl_Widget *o, void *v)
{
    char str[10];
    sprintf(str, "%d", (int*)v);
    istringstream ss(str);
    int userdata;
    ss >> userdata;
    if (userdata > FL_DASHDOTDOT) // set line color
    {
        for (int i = sm.size() - 1; i >= 0; i--)
            if (sm[i]->get_is_focused())
                sm[i]->set_line_color(userdata);
    }
    else // set line style
    {
        for (int i = sm.size() - 1; i >= 0; i--)
            if (sm[i]->get_is_focused())
                sm[i]->set_line_style(userdata);
    }
    redraw();
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

void Shapes_window::cb_menu_open(Fl_Widget *o, void *v)
{
    reference_to<Shapes_window>(o->parent()).menu_open(o, v);
}

void Shapes_window::cb_menu_save(Fl_Widget *o, void *v)
{
    reference_to<Shapes_window>(o->parent()).menu_save(o, v);
}

void Shapes_window::cb_menu_quit(Fl_Widget *o, void *v)
{
    reference_to<Shapes_window>(o->parent()).menu_quit(o, v);
}

void Shapes_window::cb_menu_trans(Fl_Widget *o, void *v)
{
    reference_to<Shapes_window>(o->parent()).menu_trans(o, v);
}

} // namespace Model_window