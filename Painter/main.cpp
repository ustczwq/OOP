#include "Model_window.h"


int main()
{
    try
    {
        Graph_lib::Shapes_window window(Point(100, 100), Graph_lib::WIN_W, Graph_lib::WIN_H, "Naive FLTK Painter");

        return Graph_lib::gui_main();
    }
    catch (exception &e)
    {
        std::cerr << "error: " << e.what() << '\n';
        return 1;
    }
    catch (...)
    {
        std::cerr << "Unknown exception!\n";
        return 2;
    }
}
