#include "Lines_window.h"
#include "Graph.h"
#include <iostream>

int main()
{
	using namespace Graph_lib;	

	try {
		Lines_window win(Point(100, 100), 600, 400, "Lines");
		return gui_main();
	} catch(exception& e) {
		std::cerr << "exception: " << e.what() << endl;
		return 1;
	}
}