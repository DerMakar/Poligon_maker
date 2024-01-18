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
		assert(inside_poligon_s - std::abs(cross_square_s - square_s) < epsilon);
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
		assert(inside_poligon_s - std::abs(cross_square_s - square_s) < epsilon);
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
		assert(inside_poligon_s - std::abs(cross_square_s - square_s) < epsilon);
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
		assert(inside_poligon_s - std::abs(cross_square_s - square_s) < epsilon);
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
		assert(inside_poligon_s - std::abs(cross_square_s - square_s) < epsilon);
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
		assert(inside_poligon_s - std::abs(cross_square_s - square_s) < epsilon);
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
		assert(inside_poligon_s - std::abs(cross_square_s - square_s) < epsilon);
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
		assert(inside_poligon_s - std::abs(cross_square_s - square_s) < epsilon);
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
		assert(inside_poligon_s - std::abs(cross_square_s - square_s) < epsilon);
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
		assert(inside_poligon_s - std::abs(cross_square_s - square_s) < epsilon);
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
		assert(inside_poligon_s - std::abs(cross_square_s - square_s) < epsilon);
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
	TestElements();
	PointInPoligon();
	TestSpace();
	TestPoligon();
	TestMergePoligons();
}