#include <iostream>
#include <fstream>
#include <istream>
#include "Model_window.pb.h"


using namespace std;

void list_point_msg(const mw::Point &msg)
{
    // for (int i = 0; i < msg.poi; i++)
    cout << msg.x() << " " << msg.y() << endl;
}

void list_points_msg(const mw::Points &msg)
{
    for (int i = 0; i < msg.points_size(); i++)
        list_point_msg(msg.points(i));
}

int main()
{
    mw::Point* point;
    mw::Points points;

    mw::Models models;
    mw::Model* model;

    for (int i = 0; i < 5; i++)
    {
        model = models.add_models();
        model->set_x(i);
        model->set_y(i + 1);
        model->set_points_limit(2);
        model->set_shape_id(i);
        model->set_w(100);
        model->set_h(80);
    }
    
    fstream output("./log2.pb", ios::out | ios::trunc | ios::binary);
    if (!models.SerializeToOstream(&output))
    {
        cerr << "falied" << endl;
        return -1;
    }
    // cout << points.points_size() << endl;

    // fstream input("./log.pb", ios::in | ios::binary);
    // if (!points.ParseFromIstream(&input))
    // {
    //     cerr << "failed to load .pb" << endl;
    //     return -1;
    // }

    // list_points_msg(points);
    
    return 0;
}

