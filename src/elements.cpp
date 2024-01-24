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

	
DrawLine::DrawLine(Point A, Point B, double Xmin, double Xmax, double Ymin, double Ymax)
	{
		start = std::move(A);
		end = std::move(B);
		dy = A.y - B.y;
		dx = A.x - B.x;
		dxy = A.x * B.y - A.y * B.x;
		qx = Xmin * dy;
		qX = Xmax * dy;
		qy = Ymin * dx;
		qY = Ymax * dx;
	}

DrawLine::DrawLine(const DrawLine& other) {
		start = other.start;
		end = other.end;
		dx = other.dx;
		dy = other.dy;
		dxy = other.dxy;
		qx = other.qx;
		qX = other.qX;
		qy = other.qy;
		qY = other.qY;
	}

DrawLine::DrawLine(DrawLine&& other) {
		start = std::move(other.start);
		end = std::move(other.end);
		dx = std::move(other.dx);
		dy = std::move(other.dy);
		dxy = std::move(other.dxy);
		qx = std::move(other.qx);
		qX = std::move(other.qX);
		qy = std::move(other.qy);
		qY = std::move(other.qY);
	}

DrawLine& DrawLine::operator=(const DrawLine& other) {
		start = other.start;
		end = other.end;
		dx = other.dx;
		dy = other.dy;
		dxy = other.dxy;
		qx = other.qx;
		qX = other.qX;
		qy = other.qy;
		qY = other.qY;
		return *this;
	}

DrawLine& DrawLine::operator=(DrawLine&& other) {
		start = std::move(other.start);
		end = std::move(other.end);
		dx = std::move(other.dx);
		dy = std::move(other.dy);
		dxy = std::move(other.dxy);
		qx = std::move(other.qx);
		qX = std::move(other.qX);
		qy = std::move(other.qy);
		qY = std::move(other.qY);
		return *this;
	}

double DrawLine::GetU1() const{
	return qx - qy + dxy;
}
double DrawLine::GetU2() const {
	return qx - qY + dxy;
}

double DrawLine::GetU3() const {
	return qX - qY + dxy;
}

double DrawLine::GetU4() const {
	return qX - qy + dxy;
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

std::optional<DrawLine> RectangleCut(const Point& start, const Point& finish, double Xmin, double Xmax, double Ymin, double Ymax){
	DrawLine result;
	double x1 = start.x
		, y1 = start.y
		, x2 = finish.x
		, y2 = finish.y;
	// step 1
	if ((x1 < Xmin && x2 < Xmin) || (x1 > Xmax && x2 > Xmax) || (y1 < Ymin && y2 < Ymin) || (y1 > Ymax && y2 > Ymax)) return std::nullopt;
	
	//step 2
	if (y1 > y2) {
		std::swap(x1, x2);
		std::swap(y1, y2);
	}
	//step 3
	if (y1 == y2) {
		// step 3.a
		if (x1 > x2) {
			std::swap(x1, x2);
			std::swap(y1, y2);
		}
		// step 3.b
		if (x1 < Xmin) x1 = Xmin;
		if (x2 > Xmax) x2 = Xmax;
		// step 3.c
		result = DrawLine (Point(x1, y1), Point(x2, y2), Xmin, Xmax, Ymin, Ymax);
		return result;
	}
	//step 4
	if (x1 == x2){
		// step 4.a
		if (y1 < Ymin) y1 = Ymin;
		//step 4.b
		if (y2 > Ymax) y2 = Ymax;
		//step 4.c
		result = DrawLine(Point(x1, y1), Point(x2, y2), Xmin, Xmax, Ymin, Ymax);
		return result;
	}
	//step 5
	result = DrawLine(Point(x1, y1), Point(x2, y2), Xmin, Xmax, Ymin, Ymax);
	//step 6
	size_t j = 0;
	double U1 = result.GetU1();
	double U2 = result.GetU2();
	// step 7 - crossing left border
	if ((U1 <= 0 && U2 > 0) || (U1 > 0 && U2 <= 0)) {
		//step 7.a
		j++;
		//step 7.b
		if (x1 < Xmin) {
			y1 = (Xmin * result.dy + result.dxy) / result.dx;
			x1 = Xmin;
			result = DrawLine(Point(x1, y1), Point(x2, y2), Xmin, Xmax, Ymin, Ymax);
		// step 7.c
		} else if (x2 < Xmin) {
			y2 = (Xmin * result.dy + result.dxy) / result.dx;
			x2 = Xmin;
			result = DrawLine(Point(x1, y1), Point(x2, y2), Xmin, Xmax, Ymin, Ymax);
		}
	}
	U2 = result.GetU2();
	double U3 = result.GetU3();
	//step 8 - crossing up border
	if ((U2 <= 0 && U3 > 0) || (U2 > 0 && U3 <= 0)) {
		//step 8.a
		j++;
		//step 8.b
		if (y2 > Ymax) {
			x2 = (Ymax * result.dx - result.dxy) / result.dy;
			y2 = Ymax;
			result = DrawLine(Point(x1, y1), Point(x2, y2), Xmin, Xmax, Ymin, Ymax);
		}
	}
	U3 = result.GetU3();
	double U4 = result.GetU4();
	//step 9 - crossing right border
	if ((U3 > 0 && U4 <= 0) || (U3 <= 0 && U4 > 0)) {
		//step 9.a
		j++;
		//step 9.b
		if (x1 > Xmax) {
			y1 = (Xmax * result.dy + result.dxy) / result.dx;
			x1 = Xmax;
			result = DrawLine(Point(x1, y1), Point(x2, y2), Xmin, Xmax, Ymin, Ymax);
		}
		//step 9.c
		else if (x2 > Xmax) {
			y2 = (Xmax * result.dy + result.dxy) / result.dx;
			x2 = Xmax;
			result = DrawLine(Point(x1, y1), Point(x2, y2), Xmin, Xmax, Ymin, Ymax);
		}
	}
	U1 = result.GetU1();
	U4 = result.GetU4();
	//step 10 - crossing down border
	if ((U4 <= 0 && U1 > 0) || (U4 > 0 && U1 <= 0)) {
		//step 10.a
		j++;
		//step 10.b
		if (y1 < Ymin) {
			x1 = (Ymin * result.dx - result.dxy) / result.dy;
			y1 = Ymin;
			result = DrawLine(Point(x1, y1), Point(x2, y2), Xmin, Xmax, Ymin, Ymax);
		}
	}
	//step 11
	return result;
}