#pragma once
#include "objects.h"
#include <string>
#include <memory>
#include <unordered_map>

class Canvas {
public:
	template<typename Obj>
	void AddObject(const std::string& name, Obj&& object) {
		if (canvas.count(name) == 0) {
			canvas[name] = std::shared_ptr<Object>(new Obj (std::move(object)));
		}
	}

	const Object* GetObject(const std::string& obj_name) const;

	void PrintAll(std::ostream& out) const;
private:
	std::unordered_map<std::string, std::shared_ptr<Object>>  canvas;
};
