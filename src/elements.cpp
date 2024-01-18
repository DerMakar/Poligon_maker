#include "elements.h"

bool operator==(Point left, Point right) {
	return std::abs(left.x - right.x) < epsilon && std::abs(left.y - right.y) < epsilon;
}

bool operator!=(Point left, Point right) {
	return !(left == right);
}

double PtoPDistance(const Point& start, const Point& finish) {
	return std::pow(std::pow(start.x - finish.x, 2) + std::pow(start.y - finish.y, 2), 0.5);
}

bool PointOnLineSegm(const Point& line_s, const Point& line_f, const Point& point) {
	double dx = std::abs(line_f.x - line_s.x);
	double dy = std::abs(line_f.y - line_s.y);
	if (std::abs(point.x - line_f.x) + std::abs(point.x - line_s.x) != dx
		&& std::abs(point.y - line_f.y) + std::abs(point.y - line_s.y) != dy) return false;
	Point new_f(line_f.x + dx, line_f.y + dy);
	Point new_p(point.x + dx, point.y + dy);
	Line line(line_s, line_f);
	return std::abs(line.dX * point.x + line.dY * point.y + line.C) < epsilon;
}

Vector operator* (const Vector& A, const Vector& B) {
	Vector res;
	res.dx = A.dy * B.dz - A.dz * B.dy;
	res.dy = A.dz * B.dx - A.dx * B.dz;
	res.dz = A.dx * B.dy - A.dy * B.dx;
	return res;
}

std::optional<Point> LineCrossingPoint(const Point& beginA, const Point& endA, const Point& beginB, const Point& endB) {
	Vector A(beginA, endA);
	Vector bAbB(beginA, beginB);
	Vector bAeB(beginA, endB);
	Vector Z1 = A * bAbB;
	Vector Z2 = A * bAeB;
	if (Z1.dz == 0 && Z2.dz == 0) return endA;
	if ((Z1.dz > 0 && Z2.dz > 0) || (Z1.dz < 0 && Z2.dz < 0)) return std::nullopt;
	Vector B(beginB, endB);
	Vector bBbA(beginB, beginA);
	Vector bBeA(beginB, endA);
	Vector Z3 = B * bBbA;
	Vector Z4 = B * bBeA;
	if ((Z3.dz > 0 && Z4.dz > 0) || (Z3.dz < 0 && Z4.dz < 0)) return std::nullopt;
	double sin = std::abs(Z1.dz) / std::abs(Z2.dz - Z1.dz);
	double cross_x = beginB.x + (endB.x - beginB.x) * sin;
	double cross_y = beginB.y + (endB.y - beginB.y) * sin;
	return Point(cross_x, cross_y);
}