#pragma once
#include <deque>
#include <cassert>
#include <map>
#include <vector>
#include <iostream>

#include "elements.h"

class Object {
public:
	virtual double Space() const = 0;
	virtual void Print(std::ostream& out) const = 0;
	virtual ~ Object() = default;
};

class Poligon : public Object {
public:
	Poligon() = default;
	Poligon(const Poligon& other);
	Poligon(Poligon&& other) noexcept;
	void operator=(const Poligon& other);
	void operator=(Poligon&& other) noexcept;

	const std::deque<Point>& GetPoligon() const;

	size_t GetSize() const;

	Point GetPoint(size_t point_num) const;

	void AddPoint(Point new_point, size_t after_pos);

	double Space() const override;

	// check if point is directly inside of poligon
	bool PointInPoligon(const Point& point) const;

	// check if point is on one of edge
	// and return point to which the edge comes clockwise
	int PointOnPoligonEdge(const Point& point) const;

	// remove extra points, lying on the edges of the polygon
	void Optimize();

	// return inside poligon from crossing of two
	Poligon HaveCrossPoligon(const Poligon& other) const;

	// return poligon, resulting by union this poligon with another
	Poligon Union(const Poligon& other) const;

	void Print(std::ostream& out) const override;

private:
	std::deque<Point> poligon;
};

Poligon operator+(const Poligon& P_1, const Poligon& P_2);

