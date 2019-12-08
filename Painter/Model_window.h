#ifndef MODEL_WINDOW_GUARD
#define MODEL_WINDOW_GUARD 1

#include <FL/Fl.H>
#include <Fl/fl_draw.H>
#include <Fl/Fl_Sys_Menu_Bar.H>

namespace Model_window
{

class FL_EXPORT Menubar : public Fl_Menu_Bar
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
            {"&File", 0, 0, 0, FL_SUBMENU},
            {"@-2fileopen Open File", FL_CTRL + 'o', cb_open, (void *)1},
            {"@-2filesave Save File", FL_CTRL + 's', cb_save, (void *)2, FL_MENU_DIVIDER},
            {"E&xit", FL_CTRL + 'q', cb_quit, 0},
            {0},
            {"&Style", 0, 0, 0, FL_SUBMENU},
            {"&Color", 0, 0, 0, FL_SUBMENU},
            {"Green", FL_CTRL + 'g', cb_trans, (void *)FL_GREEN},
            {"Yellow", FL_CTRL + 'y', cb_trans, (void *)FL_YELLOW},
            {"Blue", FL_CTRL + 'b', cb_trans, (void *)FL_BLUE},
            {"Black", FL_CTRL + 'k', cb_trans, (void *)FL_BLACK},
            {"Cyan", FL_CTRL + 'k', cb_trans, (void *)FL_CYAN},
            {0},
            {"&Line", 0, 0, 0, FL_SUBMENU},
            {"....", FL_SHIFT + 'd', cb_trans, (void *)FL_DOT},
            {"----", FL_SHIFT + 's', cb_trans, (void *)FL_SOLID},
            {"-.-.", FL_SHIFT + 'o', cb_trans, (void *)FL_DASHDOT},
            {"-..-", FL_SHIFT + 'o', cb_trans, (void *)FL_DASHDOTDOT},
            {0},
            {0},
            {0}
        };

        copy(menuitems);
        color(FL_WHITE);
        box(FL_FLAT_BOX);
    }
};

} // namespace Model_window

#endif