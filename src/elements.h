#pragma once
#include <optional>
#include <cmath>

const double epsilon = 1e-6;

struct Point {
	Point() = default;
	Point(double x, double y) : x(x), y(y) {}
	double x = 0;
	double y = 0;
};

struct Line {
	Line(Point A, Point B)
		: dX(B.y - A.y)
		, dY(A.x - B.x) {
		C = (-1.0 * A.x) * (B.y - A.y);
		C -= (-1.0 * A.y) * (B.x - A.x);
	}
	double dX = 0;
	double dY = 0;
	double C = 0;
};

struct Vector {
	Vector() = default;
	Vector(Point A, Point B)
		: dx(B.x - A.x)
		, dy(B.y - A.y) {
	}
	double dx = 0;
	double dy = 0;
	double dz = 0;
};

bool operator==(Point left, Point right);

bool operator!=(Point left, Point right);

double PtoPDistance(const Point& start, const Point& finish);

bool PointOnLineSegm(const Point& line_s, const Point& line_f, const Point& point);

std::optional<Point> LineCrossingPoint(const Point& beginA, const Point& endA, const Point& beginB, const Point& endB);

Vector operator* (const Vector& A, const Vector& B);

