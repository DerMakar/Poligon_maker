#include "canvas.h"
#include "testframe.h"
#include "input_reader.h"


int main(int argc, char* argv[]) {
	if (argc != 3) {
		std::cerr << "Unvalid arguments ([program name] [input_file] [output_file])";
		return -1;
	}
	//FullTest();
	const auto objects = RenderObjects(argv[1]);
	Canvas canvas;
	for (const auto& [obj, points] : objects) {
		Poligon poligon;
		size_t i = 0;
		for (const auto& [x, y] : points) {
			poligon.AddPoint(Point(x, y), i++);
		}
		canvas.AddObject(obj, std::move(poligon));
	}
	const Poligon* baser = dynamic_cast<const Poligon*> (canvas.GetObject(objects[0].first));
	const Poligon* crosser = dynamic_cast<const Poligon*> (canvas.GetObject(objects[1].first));
	canvas.AddObject("inside_poligon", baser->HaveCrossPoligon(*crosser));
	canvas.AddObject("outside_poligon", baser->Union(*crosser));
	std::ofstream out(argv[2]);
	if (out.is_open()) {
		canvas.PrintAll(out);
	}	
	return 0;
}
