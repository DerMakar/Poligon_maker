#pragma once

#include <cassert>
#include "elements.h"
#include "objects.h"

void TestElements() {
	{
		Point A(1, 1);
		Point B(3, 5);
		Line L(A, B);
		assert(L.dX == 4 && L.dY == -2 && L.C == -2);
	}
	{
		Point A(-7, -4);
		Point B(10, 8);
		Line L(A, B);
		assert(L.dX == 12 && L.dY == -17 && L.C == 16);
	}
	{
		Point A(1, 1);
		Point B(3, 4);
		Point C(1, 4);
		Point D(3, 1);
		assert(LineCrossingPoint(A, B, C, D) == Point(2, 2.5));
		Point F(3, 5);
		assert(!LineCrossingPoint(A, B, C, F).has_value());
		assert(LineCrossingPoint(A, B, C, B) == B);
		assert(LineCrossingPoint(A, B, A, C) == A);
	}
	{
		Point A(1, 1);
		Point B(3, 3);
		Point C(2, 2);
		Point D(4, 5);
		Point M(4, 4);
		assert(PointOnLineSegm(A, B, C));
		assert(!PointOnLineSegm(A, B, D));
		assert(!PointOnLineSegm(A, B, M));
		assert(PointOnLineSegm(A, B, A));
	}
	
}

void TestDrawLine() {
	Point A(1, 1);
	Point B(3, 3);
	Point C(-1, 1);
	Point D(6, 3);
	Point E(1, 6);
	Point F(3, -1);
	Point J(-1, -1);
	Point I(6, 5);
	Point H(4, 7);
	Point G(6, -1);
	Point K(-3, -3);
	Point L(8, 8);
	double Xmin = 0, Xmax = 5, Ymin = 0, Ymax = 5;
	auto line = RectangleCut(A, B, Xmin, Xmax, Ymin, Ymax);
	assert(line.value().start == A);
	assert(line.value().end == B);
	line = RectangleCut(A, C, Xmin, Xmax, Ymin, Ymax);
	assert(line.value().start == Point(0,1));
	line = RectangleCut(B, D, Xmin, Xmax, Ymin, Ymax);
	assert(line.value().end == Point(5, 3));
	line = RectangleCut(A, E, Xmin, Xmax, Ymin, Ymax);
	assert(line.value().end == Point(1, 5));
	line = RectangleCut(B, F, Xmin, Xmax, Ymin, Ymax);
	assert(line.value().start == Point(3, 0));
	line = RectangleCut(C, J, Xmin, Xmax, Ymin, Ymax);
	assert(!line.has_value());
	line = RectangleCut(A, I, Xmin, Xmax, Ymin, Ymax);
	assert(line.value().end == Point(5, 4.2));
	line = RectangleCut(A, H, Xmin, Xmax, Ymin, Ymax);
	assert(line.value().end == Point(3, 5));
	line = RectangleCut(B, K, Xmin, Xmax, Ymin, Ymax);
	assert(line.value().start == Point(0, 0));
	line = RectangleCut(L, B, Xmin, Xmax, Ymin, Ymax);
	assert(line.value().end == Point(5, 5));
}

void TestRandomLineCut() {
	{
		Point A(1, 1);
		Point B(3, 5);
		Point C(5, 3);
		std::vector<Point> point_collection({ A, B, C });
		Poligon square;
		for (size_t i = 0; i < point_collection.size(); ++i) {
			square.AddPoint(point_collection[i], i);
		}
		Line line(Point(0, 5), Point(5, 0));
		auto vectors = square.RandomLineCut(line);
	}
	{
		Point A(1, 3);
		Point B(3, 5);
		Point C(6, 2);
		Point D(4, 0);
		Point E(3, 1);
		Point F(4, 3);
		Point G(3, 3);
		Point H(2, 2);
		std::vector<Point> point_collection({ A, B, C, D, E, F, G, H });
		Poligon square;
		for (size_t i = 0; i < point_collection.size(); ++i) {
			square.AddPoint(point_collection[i], i);
		}
		Line line(Point(0, 5), Point(5, 0));
		auto vectors = square.RandomLineCut(line);
	}
	{
		Point A(1, 1);
		Point B(1, 5);
		Point C(3, 5);
		Point D(3, 1);
		std::vector<Point> point_collection({ A, B, C, D });
		Poligon square;
		for (size_t i = 0; i < point_collection.size(); ++i) {
			square.AddPoint(point_collection[i], i);
		}
		Line line(Point(0, 5), Point(5, 0));
		auto vectors = square.RandomLineCut(line);
	}
}

void TestSpace() {
	{
		Point A(1, 1);
		Point B(1, 5);
		Point C(4, 5);
		Point D(4, 1);
		std::vector<Point> point_collection({ A, B, C, D });
		Poligon square;
		for (size_t i = 0; i < 4; ++i) {
			square.AddPoint(point_collection[i], i);
		}
		assert(square.Space() == 12.0);
	}
	{
		Point A(1, 1);
		Point B(1, 5);
		Point D(4, 1);
		std::vector<Point> point_collection({ A, B, D });
		Poligon square;
		for (size_t i = 0; i < 3; ++i) {
			square.AddPoint(point_collection[i], i);
		}
		assert(square.Space() == 6.0);
	}
	{
		Point A(1, 1);
		Point B(1, 5);
		std::vector<Point> point_collection({ A, B });
		Poligon square;
		for (size_t i = 0; i < 2; ++i) {
			square.AddPoint(point_collection[i], i);
		}
		assert(square.Space() == 0.0);
	}

}

void TestPoligon() {
	{
		Point A(1, 1);
		Point B(1, 5);
		Point C(4, 5);
		Point D(4, 1);
		std::vector<Point> point_collection({ A, B, C, D });
		Poligon square;
		for (size_t i = 0; i < 4; ++i) {
			square.AddPoint(point_collection[i], i);
		}
		assert(square.GetPoint(1) == A && square.GetPoint(4) == D);
		Point M(3, 4);
		Point N(3, 8);
		Point R(7, 8);
		Point S(7, 4);
		point_collection = std::vector<Point>({ M, N, R, S });
		Poligon cross_square;
		for (size_t i = 0; i < 4; ++i) {
			cross_square.AddPoint(point_collection[i], i);
		}
		assert(square.PointInPoligon(M));
		assert(!square.PointInPoligon(N));
		assert(cross_square.PointInPoligon(C));
		auto inside_poligon = square.HaveCrossPoligon(cross_square);
		double square_s = square.Space();
		double cross_square_s = cross_square.Space();
		double inside_poligon_s = inside_poligon.Space();
		auto outside_pol = square + cross_square;
		double outside_s = outside_pol.Space();
		assert(inside_poligon_s - std::abs(square_s + cross_square_s - outside_s) < epsilon);
	}
	{
		Point A(-2, 0);
		Point B(0, 2);
		Point C(2, 0);
		Point D(0, -2);
		std::vector<Point> point_collection({ A, B, C, D });
		Poligon square;
		for (size_t i = 0; i < 4; ++i) {
			square.AddPoint(point_collection[i], i);
		}
		assert(square.GetPoint(1) == A && square.GetPoint(4) == D);
		Point M(-1, 1);
		Point N(-1, 4);
		Point R(1, 4);
		Point S(1, 1);
		point_collection = std::vector<Point>({ M, N, R, S });
		Poligon cross_square;
		for (size_t i = 0; i < 4; ++i) {
			cross_square.AddPoint(point_collection[i], i);
		}
		auto inside_poligon = square.HaveCrossPoligon(cross_square);
		double square_s = square.Space();
		double cross_square_s = cross_square.Space();
		double inside_poligon_s = inside_poligon.Space();
		auto outside_pol = square + cross_square;
		double outside_s = outside_pol.Space();
		assert(inside_poligon_s - std::abs(square_s + cross_square_s - outside_s) < epsilon);
	}
	{
		Point A(0, 0);
		Point B(0, 4);
		Point C(3, 0);
		std::vector<Point> point_collection({ A, B, C });
		Poligon square;
		for (size_t i = 0; i < 3; ++i) {
			square.AddPoint(point_collection[i], i);
		}
		Point N(1, -3);
		Point R(1, 6);
		Point S(4, 6);
		Point M(4, -3);
		point_collection = std::vector<Point>({ N, R, S, M });
		Poligon cross_square;
		for (size_t i = 0; i < 4; ++i) {
			cross_square.AddPoint(point_collection[i], i);
		}
		auto inside_poligon = square.HaveCrossPoligon(cross_square);
		double square_s = square.Space();
		double cross_square_s = cross_square.Space();
		double inside_poligon_s = inside_poligon.Space();
		auto outside_pol = square + cross_square;
		double outside_s = outside_pol.Space();
		assert(inside_poligon_s - std::abs(square_s + cross_square_s - outside_s) < epsilon);
	}
	{
		Point A(0, 0);
		Point B(0, 5);
		Point C(4, 0);
		std::vector<Point> point_collection({ A, B, C });
		Poligon square;
		for (size_t i = 0; i < 3; ++i) {
			square.AddPoint(point_collection[i], i);
		}
		Point N(1, -3);
		Point R(1, 6);
		Point S(3, 6);
		Point M(3, -3);
		point_collection = std::vector<Point>({ N, R, S, M });
		Poligon cross_square;
		for (size_t i = 0; i < 4; ++i) {
			cross_square.AddPoint(point_collection[i], i);
		}
		auto inside_poligon = square.HaveCrossPoligon(cross_square);
		double square_s = square.Space();
		double cross_square_s = cross_square.Space();
		double inside_poligon_s = inside_poligon.Space();
		auto outside_pol = square + cross_square;
		double outside_s = outside_pol.Space();
		assert(inside_poligon_s - std::abs(square_s + cross_square_s - outside_s) < epsilon);
	}
	{
		Point A(0, 0);
		Point B(0, 4);
		Point C(4, 0);
		std::vector<Point> point_collection({ A, B, C });
		Poligon square;
		for (size_t i = 0; i < 3; ++i) {
			square.AddPoint(point_collection[i], i);
		}
		Point N(0, 4);
		Point R(1, 5);
		Point S(5, 1);
		Point M(4, 0);
		point_collection = std::vector<Point>({ N, R, S, M });
		Poligon cross_square;
		for (size_t i = 0; i < 4; ++i) {
			cross_square.AddPoint(point_collection[i], i);
		}
		auto inside_poligon = square.HaveCrossPoligon(cross_square);
		double square_s = square.Space();
		double cross_square_s = cross_square.Space();
		double inside_poligon_s = inside_poligon.Space();
		auto outside_pol = square + cross_square;
		double outside_s = outside_pol.Space();
		assert(inside_poligon_s - std::abs(square_s + cross_square_s - outside_s) < epsilon);
	}
	{
		Point A(0, 0);
		Point B(0, 4);
		Point C(4, 0);
		std::vector<Point> point_collection({ A, B, C });
		Poligon square;
		for (size_t i = 0; i < 3; ++i) {
			square.AddPoint(point_collection[i], i);
		}
		Point N(2, 2);
		Point R(3, 3);
		Point S(5, 1);
		Point M(4, 0);
		point_collection = std::vector<Point>({ N, R, S, M });
		Poligon cross_square;
		for (size_t i = 0; i < 4; ++i) {
			cross_square.AddPoint(point_collection[i], i);
		}
		auto inside_poligon = square.HaveCrossPoligon(cross_square);
		double square_s = square.Space();
		double cross_square_s = cross_square.Space();
		double inside_poligon_s = inside_poligon.Space();
		auto outside_pol = square + cross_square;
		double outside_s = outside_pol.Space();
		assert(inside_poligon_s - std::abs(square_s + cross_square_s - outside_s) < epsilon);
	}
	{
		Point A(0, 0);
		Point B(0, 4);
		Point C(4, 0);
		std::vector<Point> point_collection({ A, B, C });
		Poligon square;
		for (size_t i = 0; i < 3; ++i) {
			square.AddPoint(point_collection[i], i);
		}
		Point N(2, 2);
		Point R(2, 5);
		Point S(5, 5);
		Point M(5, 2);
		point_collection = std::vector<Point>({ N, R, S, M });
		Poligon cross_square;
		for (size_t i = 0; i < 4; ++i) {
			cross_square.AddPoint(point_collection[i], i);
		}
		auto inside_poligon = square.HaveCrossPoligon(cross_square);
		double square_s = square.Space();
		double cross_square_s = cross_square.Space();
		double inside_poligon_s = inside_poligon.Space();
		auto outside_pol = square + cross_square;
		double outside_s = outside_pol.Space();
		assert(inside_poligon_s - std::abs(square_s + cross_square_s - outside_s) < epsilon);
	}
	{
		Point A(0, 0);
		Point B(0, 3);
		Point C(3, 3);
		Point D(3, 0);
		std::vector<Point> point_collection({ A, B, C, D });
		Poligon square;
		for (size_t i = 0; i < 4; ++i) {
			square.AddPoint(point_collection[i], i);
		}
		Point N(0, 0);
		Point R(0, 1);
		Point S(1, 1);
		Point M(1, 0);
		point_collection = std::vector<Point>({ N, R, S, M });
		Poligon cross_square;
		for (size_t i = 0; i < 4; ++i) {
			cross_square.AddPoint(point_collection[i], i);
		}
		auto inside_poligon = square.HaveCrossPoligon(cross_square);
		double square_s = square.Space();
		double cross_square_s = cross_square.Space();
		double inside_poligon_s = inside_poligon.Space();
		auto outside_pol = square + cross_square;
		double outside_s = outside_pol.Space();
		assert(inside_poligon_s - std::abs(square_s + cross_square_s - outside_s) < epsilon);
	}
	{
		Point A(0, 0);
		Point B(0, 3);
		Point C(3, 3);
		Point D(3, 0);
		std::vector<Point> point_collection({ A, B, C, D });
		Poligon square;
		for (size_t i = 0; i < 4; ++i) {
			square.AddPoint(point_collection[i], i);
		}
		Point N(1, 1);
		Point R(1, 2);
		Point S(2, 2);
		Point M(2, 1);
		point_collection = std::vector<Point>({ N, R, S, M });
		Poligon cross_square;
		for (size_t i = 0; i < 4; ++i) {
			cross_square.AddPoint(point_collection[i], i);
		}
		auto inside_poligon = square.HaveCrossPoligon(cross_square);
		double square_s = square.Space();
		double cross_square_s = cross_square.Space();
		double inside_poligon_s = inside_poligon.Space();
		auto outside_pol = square + cross_square;
		double outside_s = outside_pol.Space();
		assert(inside_poligon_s - std::abs(square_s + cross_square_s - outside_s) < epsilon);
	}
	{
		Point A(1, 1);
		Point B(1, 2);
		Point C(2, 2);
		Point D(2, 1);
		std::vector<Point> point_collection({ A, B, C, D });
		Poligon square;
		for (size_t i = 0; i < 4; ++i) {
			square.AddPoint(point_collection[i], i);
		}
		Point N(0, 0);
		Point R(0, 3);
		Point S(3, 3);
		Point M(3, 0);
		point_collection = std::vector<Point>({ N, R, S, M });
		Poligon cross_square;
		for (size_t i = 0; i < 4; ++i) {
			cross_square.AddPoint(point_collection[i], i);
		}
		auto inside_poligon = square.HaveCrossPoligon(cross_square);
		double square_s = square.Space();
		double cross_square_s = cross_square.Space();
		double inside_poligon_s = inside_poligon.Space();
		auto outside_pol = square + cross_square;
		double outside_s = outside_pol.Space();
		assert(inside_poligon_s - std::abs(square_s + cross_square_s - outside_s) < epsilon);
	}
	{
		Point A(0, 0);
		Point B(-5, 0.5);
		Point C(-3, 5);
		Point D(0, 4);
		Point F(1.5, 7);
		Point G(3.5, 0);
		Point H(0, -8);
		std::vector<Point> point_collection({ A, B, C, D, F, G, H });
		Poligon square;
		for (size_t i = 0; i < point_collection.size(); ++i) {
			square.AddPoint(point_collection[i], i);
		}
		Point N(-5, -4);
		Point R(-1, 2);
		Point S(6.5, 4);
		Point M(7, -6);
		Point K(2, -1.5);
		Point L(-2.5, -6.5);
		point_collection = std::vector<Point>({ N, R, S, M, K, L });
		Poligon cross_square;
		for (size_t i = 0; i < point_collection.size(); ++i) {
			cross_square.AddPoint(point_collection[i], i);
		}
		auto inside_poligon = square.HaveCrossPoligon(cross_square);
		double square_s = square.Space();
		double cross_square_s = cross_square.Space();
		double inside_poligon_s = inside_poligon.Space();
		auto outside_pol = square + cross_square;
		double outside_s = outside_pol.Space();
		assert(inside_poligon_s - std::abs(square_s + cross_square_s - outside_s) < epsilon);
	}
	{
		// two triangles, one crosser point on base's edge
		Point A(-84.17998071, 91.75441033);
		Point B(-67.05146691, 70.00209191);
		Point C(-84.40989365, 52.09442871);
		std::vector<Point> point_collection({ A, B, C});
		Poligon base_poligon;
		for (size_t i = 0; i < point_collection.size(); ++i) {
			base_poligon.AddPoint(point_collection[i], i);
		}
		Point N(-100.72093923, 70.00209191);
		Point R(-54.12525068, 70.00209191);
		Point S(-83.14537250, 34.03349022);
		point_collection = std::vector<Point>({ N, R, S });
		Poligon cross_poligon;
		for (size_t i = 0; i < point_collection.size(); ++i) {
			cross_poligon.AddPoint(point_collection[i], i);
		}
		auto inside_poligon = base_poligon.HaveCrossPoligon(cross_poligon);
		double baser_s = base_poligon.Space();
		double crosser_s = cross_poligon.Space();
		double inside_poligon_s = inside_poligon.Space();
		auto outside_pol = base_poligon + cross_poligon;
		double outside_s = outside_pol.Space();
		assert(inside_poligon_s - std::abs(baser_s + crosser_s - outside_s) < epsilon);
		assert(outside_s - std::abs(baser_s + crosser_s - inside_poligon_s) < epsilon);
	}
	{
		// two inside poligons case
		Point A(39.15891839, 146.28916144);
		Point B(98.37750070, 146.28916144);
		Point C(98.37750070, 128.37429620);
		Point D(64.04067567 ,128.37429620);
		Point E(64.04067567 ,102.99490378);
		Point F(98.87513585, 102.99490378);
		Point G(98.87513585 ,77.11787622);
		Point H(47.12108072, 77.11787622);
		std::vector<Point> point_collection({ A, B, C, D, E, F, G, H});
		Poligon base_poligon;
		for (size_t i = 0; i < point_collection.size(); ++i) {
			base_poligon.AddPoint(point_collection[i], i);
		}
		Point N(89.42006809, 53.72902438);
		Point R(89.42006809, 159.72531036);
		Point S(139.18358263, 159.22767522);
		Point M(135.20250147, 57.21247040);
		point_collection = std::vector<Point>({ N, R, S, M });
		Poligon cross_poligon;
		for (size_t i = 0; i < point_collection.size(); ++i) {
			cross_poligon.AddPoint(point_collection[i], i);
		}
		auto inside_poligon = base_poligon.HaveCrossPoligon(cross_poligon);
		double baser_s = base_poligon.Space();
		double crosser_s = cross_poligon.Space();
		double inside_poligon_s = inside_poligon.Space();
		auto outside_pol = base_poligon + cross_poligon;
		double outside_s = outside_pol.Space();
		assert(inside_poligon_s - std::abs(baser_s + crosser_s - outside_s) < epsilon);
		assert(outside_s - std::abs(baser_s + crosser_s - inside_poligon_s) < epsilon);
	}
	{
		// complex form case
		Point A(-13.61568677, 79.48443934);
		Point B(- 13.61568677, 88.47658976);
		Point C(- 1.96676463, 88.47658976);
		Point D(- 2.14185600 ,80.30565952);
		Point E(- 2.46158533 ,65.38495725);
		Point F(- 11.57201622 ,50.87305163);
		Point G(- 11.57201622 ,77.23640173);
		Point H(- 18.72486315, 51.48615280);
		Point I(- 18.72486315, 95.42506964);
		std::vector<Point> point_collection({ A, B, C, D, E, F, G, H, I });
		Poligon base_poligon;
		for (size_t i = 0; i < point_collection.size(); ++i) {
			base_poligon.AddPoint(point_collection[i], i);
		}
		Point N(-1.96676463, 88.47658976);
		Point R(-2.57986580, 59.86520205);
		Point S(-28.73884885, 77.84950290);
		point_collection = std::vector<Point>({ N, R, S });
		Poligon cross_poligon;
		for (size_t i = 0; i < point_collection.size(); ++i) {
			cross_poligon.AddPoint(point_collection[i], i);
		}
		auto inside_poligon = base_poligon.HaveCrossPoligon(cross_poligon);
		double baser_s = base_poligon.Space();
		double crosser_s = cross_poligon.Space();
		double inside_poligon_s = inside_poligon.Space();
		auto outside_pol = base_poligon + cross_poligon;
		double outside_s = outside_pol.Space();
		assert(inside_poligon_s - std::abs(baser_s + crosser_s - outside_s) < epsilon);
		assert(outside_s - std::abs(baser_s + crosser_s - inside_poligon_s) < epsilon);
	}
}

void TestMergePoligons() {
	{
		Point A(0, 0);
		Point B(0, 3);
		Point C(3, 3);
		Point D(3, 0);
		std::vector<Point> point_collection({ A, B, C, D });
		Poligon square;
		for (size_t i = 0; i < point_collection.size(); ++i) {
			square.AddPoint(point_collection[i], i);
		}
		Point N(2, 2);
		Point R(2, 5);
		Point S(5, 5);
		Point M(5, 2);
		point_collection = std::vector<Point>({ N, R, S, M });
		Poligon cross_square;
		for (size_t i = 0; i < point_collection.size(); ++i) {
			cross_square.AddPoint(point_collection[i], i);
		}
		auto outside_poligon = square + cross_square;
		assert(outside_poligon.GetSize() == 8);
		double square_s = square.Space();
		double cross_square_s = cross_square.Space();
		double inside_sq_s = square.HaveCrossPoligon(cross_square).Space();
		assert((outside_poligon.Space() - (square_s + cross_square_s - inside_sq_s)) < epsilon);
	}
	{
		Point A(0, 0);
		Point B(0, 3);
		Point C(3, 3);
		Point D(3, 0);
		std::vector<Point> point_collection({ A, B, C, D });
		Poligon square;
		for (size_t i = 0; i < point_collection.size(); ++i) {
			square.AddPoint(point_collection[i], i);
		}
		Point N(2, 5);
		Point R(5, 5);
		Point S(5, 2);
		Point M(2, 2);
		point_collection = std::vector<Point>({ N, R, S, M });
		Poligon cross_square;
		for (size_t i = 0; i < point_collection.size(); ++i) {
			cross_square.AddPoint(point_collection[i], i);
		}
		auto outside_poligon = square + cross_square;
		double square_s = square.Space();
		double cross_square_s = cross_square.Space();
		double inside_sq_s = square.HaveCrossPoligon(cross_square).Space();
		assert((outside_poligon.Space() - (square_s + cross_square_s - inside_sq_s)) < epsilon);
	}
	{
		Point A(-2, 0);
		Point B(0, 2);
		Point C(2, 0);
		Point D(0, -2);
		std::vector<Point> point_collection({ A, B, C, D });
		Poligon square;
		for (size_t i = 0; i < 4; ++i) {
			square.AddPoint(point_collection[i], i);
		}
		assert(square.GetPoint(1) == A && square.GetPoint(4) == D);
		Point M(-1, 1);
		Point N(-1, 4);
		Point R(1, 4);
		Point S(1, 1);
		point_collection = std::vector<Point>({ M, N, R, S });
		Poligon cross_square;
		for (size_t i = 0; i < 4; ++i) {
			cross_square.AddPoint(point_collection[i], i);
		}
		auto outside_poligon = square + cross_square;
		assert(outside_poligon.GetSize() == 7);
		double square_s = square.Space();
		double cross_square_s = cross_square.Space();
		double inside_sq_s = square.HaveCrossPoligon(cross_square).Space();
		assert((outside_poligon.Space() - (square_s + cross_square_s - inside_sq_s)) < epsilon);

	}
	{
		Point A(0, 0);
		Point B(0, 4);
		Point C(3, 0);
		std::vector<Point> point_collection({ A, B, C});
		Poligon square;
		for (size_t i = 0; i < point_collection.size(); ++i) {
			square.AddPoint(point_collection[i], i);
		}
		Point M(2, 0);
		Point N(4, 2);
		Point R(4, 0);
		point_collection = std::vector<Point>({ M, N, R });
		Poligon cross_square;
		for (size_t i = 0; i < point_collection.size(); ++i) {
			cross_square.AddPoint(point_collection[i], i);
		}
		auto outside_poligon = square + cross_square;
		assert(outside_poligon.GetSize() == 5);
		double square_s = square.Space();
		double cross_square_s = cross_square.Space();
		double inside_sq_s = square.HaveCrossPoligon(cross_square).Space();
		assert((outside_poligon.Space() - (square_s + cross_square_s - inside_sq_s)) < epsilon);
	}
	{
		Point A(0, 0);
		Point B(0, 4);
		Point C(3, 0);
		std::vector<Point> point_collection({ A, B, C });
		Poligon square;
		for (size_t i = 0; i < point_collection.size(); ++i) {
			square.AddPoint(point_collection[i], i);
		}
		Point M(3, 0);
		Point N(4, 2);
		Point R(4, 0);
		point_collection = std::vector<Point>({ M, N, R });
		Poligon cross_square;
		for (size_t i = 0; i < point_collection.size(); ++i) {
			cross_square.AddPoint(point_collection[i], i);
		}
		auto outside_poligon = square + cross_square;
		assert(outside_poligon.GetSize() == 5);
		double square_s = square.Space();
		double cross_square_s = cross_square.Space();
		double inside_sq_s = square.HaveCrossPoligon(cross_square).Space();
		assert((outside_poligon.Space() - (square_s + cross_square_s - inside_sq_s)) < epsilon);
	}
	{
		//crosser around baser
		Point A(1, 1);
		Point B(1, 2);
		Point C(2, 2);
		Point D(2, 1);
		std::vector<Point> point_collection({ A, B, C, D });
		Poligon square;
		for (size_t i = 0; i < 4; ++i) {
			square.AddPoint(point_collection[i], i);
		}
		Point N(0, 0);
		Point R(0, 3);
		Point S(3, 3);
		Point M(3, 0);
		point_collection = std::vector<Point>({ N, R, S, M });
		Poligon cross_square;
		for (size_t i = 0; i < 4; ++i) {
			cross_square.AddPoint(point_collection[i], i);
		}
		auto outside_poligon = square + cross_square;
		assert(outside_poligon.GetSize() == 4);
		assert((outside_poligon.Space() - cross_square.Space()) < epsilon);
	}
	{
		//baser around crosser
		Point A(0, 0);
		Point B(0, 3);
		Point C(3, 3);
		Point D(3, 0);
		std::vector<Point> point_collection({ A, B, C, D });
		Poligon square;
		for (size_t i = 0; i < 4; ++i) {
			square.AddPoint(point_collection[i], i);
		}
		Point N(1, 1);
		Point R(1, 2);
		Point S(2, 2);
		Point M(2, 1);
		point_collection = std::vector<Point>({ N, R, S, M });
		Poligon cross_square;
		for (size_t i = 0; i < 4; ++i) {
			cross_square.AddPoint(point_collection[i], i);
		}
		auto outside_poligon = square + cross_square;
		assert(outside_poligon.GetSize() == 4);
		assert((outside_poligon.Space() - square.Space()) < epsilon);
	}
	{
		//no cross
		Point A(0, 0);
		Point B(0, 3);
		Point C(3, 3);
		Point D(3, 0);
		std::vector<Point> point_collection({ A, B, C, D });
		Poligon square;
		for (size_t i = 0; i < 4; ++i) {
			square.AddPoint(point_collection[i], i);
		}
		Point N(4, 4);
		Point R(4, 7);
		Point S(7, 7);
		Point M(7, 4);
		point_collection = std::vector<Point>({ N, R, S, M });
		Poligon cross_square;
		for (size_t i = 0; i < 4; ++i) {
			cross_square.AddPoint(point_collection[i], i);
		}
		auto outside_poligon = square + cross_square;
		assert(outside_poligon.GetSize() == 0);
	}
	{
		// test task exmpl
		Point A(0, 0);
		Point B(-5, 0.5);
		Point C(-3, 5);
		Point D(0, 4);
		Point F(1.5, 7);
		Point G(3.5, 0);
		Point H(0, -8);
		std::vector<Point> point_collection({ A, B, C, D, F, G, H });
		Poligon square;
		for (size_t i = 0; i < point_collection.size(); ++i) {
			square.AddPoint(point_collection[i], i);
		}
		Point N(-5, -4);
		Point R(-1, 2);
		Point S(6.5, 4);
		Point M(7, -6);
		Point K(2, -1.5);
		Point L(-2.5, -6.5);
		point_collection = std::vector<Point>({ N, R, S, M, K, L });
		Poligon cross_square;
		for (size_t i = 0; i < point_collection.size(); ++i) {
			cross_square.AddPoint(point_collection[i], i);
		}
		auto outside_poligon = square + cross_square;
		double square_s = square.Space();
		double cross_square_s = cross_square.Space();
		double inside_sq_s = square.HaveCrossPoligon(cross_square).Space();
		assert((outside_poligon.Space() - (square_s + cross_square_s - inside_sq_s)) < epsilon);
	}
}

void PointInPoligon() {
	{
		Point A(-2, 0);
		Point B(0, 2);
		Point C(2, 0);
		Point D(0, -2);
		std::vector<Point> point_collection({ A, B, C, D });
		Poligon square;
		for (size_t i = 0; i < 4; ++i) {
			square.AddPoint(point_collection[i], i);
		}
		assert(square.GetPoint(1) == A && square.GetPoint(4) == D);
		Point M(-1, 1);
		Point N(-1, 4);
		Point R(1, 4);
		Point S(1, 1);
		point_collection = std::vector<Point>({ M, N, R, S });
		Poligon cross_square;
		for (size_t i = 0; i < 4; ++i) {
			cross_square.AddPoint(point_collection[i], i);
		}
		assert(square.PointInPoligon(Point(0,0)));
		assert(!square.PointInPoligon(Point(0,6)));
		assert(!square.PointInPoligon(S));
	}
}

void FullTest() {
	TestRandomLineCut();
	TestDrawLine();
	TestElements();
	PointInPoligon();
	TestSpace();
	TestPoligon();
	TestMergePoligons();
}