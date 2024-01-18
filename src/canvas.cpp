#include "canvas.h"



const Object* Canvas::GetObject(const std::string& obj_name) const {
	if (canvas.count(obj_name) != 0) {
		return canvas.at(obj_name).get();
	}
}

void Canvas::PrintAll(std::ostream& out) const {
	for (const auto& [name, object] : canvas) {
		out << "poligon : \"" << name << "\"";
		out << std::endl;
		out << "  Space: ";
		out << object->Space();
		out << std::endl;
		out << "  Points: ";
		object->Print(out);
		out << ";" << std::endl;
		out << std::endl;
	}
}