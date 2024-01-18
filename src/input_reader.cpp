#include "input_reader.h"

std::vector<object> RenderObjects(const std::string& file_name) {
    std::ifstream input(file_name);
    if (!input.is_open())throw std::exception("no such infile");
    using namespace std::literals;
    std::vector<object> objects;
    while (input) {
        std::string name;
        getline(input, name);
        object poligon;
        poligon.first = name;
        int points = 0;
        input >> points;
        while (points > 0) {
            double x = 0;
            input >> x;
            double y = 0;
            input >> y;
            poligon.second.push_back(std::make_pair(x, y));
            points--;
        }
        objects.push_back(std::move(poligon));
        input.get();
    }
    return objects;
}