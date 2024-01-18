#pragma once

#include <string>
#include <fstream>
#include <vector>

using points = std::vector<std::pair<double, double>>;
using object = std::pair<std::string, points>;

std::vector<object> RenderObjects(const std::string& file_name);
