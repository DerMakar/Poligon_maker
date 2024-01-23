#include "objects.h"

Poligon::Poligon(const Poligon& other) : poligon(other.poligon) {}
	
Poligon::Poligon(Poligon&& other) noexcept : poligon(std::move(other.poligon)) {}
	
void Poligon::operator=(const Poligon& other) {
	poligon = other.poligon;
}
	
void Poligon::operator=(Poligon&& other) noexcept {
	poligon = std::move(other.poligon);
}

const std::deque<Point>& Poligon::GetPoligon() const {
	return poligon;
}

size_t Poligon::GetSize() const {
	return poligon.size();
}

Point Poligon::GetPoint(size_t point_num) const {
	assert(point_num > 0 && point_num <= poligon.size());
	return poligon[point_num - 1];
}

void Poligon::AddPoint(Point new_point, size_t after_pos) {
	assert(after_pos >= 0 && after_pos <= poligon.size());
	poligon.insert(poligon.begin() + after_pos, new_point);
}

double Poligon::Space() const {
	size_t j = poligon.size() - 1;
	double space = 0.;
	if (poligon.size() > 2) {
		for (size_t i = 0; i < poligon.size(); ++i) {
			space += poligon[j].x * poligon[i].y - poligon[i].x * poligon[j].y;
			j = i;
		}
		space *= 0.5;
	}
	return std::abs(space);
}

void Poligon::Optimize() {
	if (GetSize() < 3) return;
	size_t j = GetSize() - 1;
	size_t prev_point = j - 1;
	for (size_t i = 0; i < GetSize(); ++i) {
		if (PointOnLineSegm(poligon[prev_point], poligon[i], poligon[j])) poligon.erase(poligon.begin() + j);
		prev_point = j;
		j = i;
	}
}

bool Poligon::PointInPoligon(const Point& point) const {
	bool ans = false;
	size_t j = GetSize() - 1;
	for (size_t i = 0; i < GetSize(); i++) {
		if (((poligon[i].y > point.y) != (poligon[j].y > point.y))
			&& (point.x < (poligon[j].x - poligon[i].x) * (point.y - poligon[i].y) / (poligon[j].y - poligon[i].y) + poligon[i].x)) {
			ans = !ans;
		}
		j = i;
	}
	return ans;
}

int Poligon::PointOnPoligonEdge(const Point& point) const {
	bool ans = false;
	size_t j = GetSize() - 1;
	for (size_t i = 0; i < GetSize(); i++) {
		if (PointOnLineSegm(poligon[j], poligon[i], point)) return i;
		j = i;
	}
	return -1;
}

Poligon Poligon::HaveCrossPoligon(const Poligon& other) const {
	Poligon cross_poligon;
	size_t cross_pol_size = 0;
	size_t prev_i = other.GetSize();
	size_t prev_j = GetSize() - 1;
	std::vector<Point> seved_points;
	seved_points.reserve(other.GetSize());
	for (size_t i = 1; i <= other.GetSize(); ++i) {
		Point A(other.GetPoint(prev_i).x, other.GetPoint(prev_i).y);
		Point B(other.GetPoint(i).x, other.GetPoint(i).y);
		std::map<double, Point> distance_cont;
		for (size_t j = 0; j < GetSize(); ++j) {
			Point C(poligon[prev_j].x, poligon[prev_j].y);
			Point D(poligon[j].x, poligon[j].y);
			std::optional<Point> cross_point = LineCrossingPoint(A, B, C, D);
			if (!cross_point.has_value()) {
				prev_j = j;
				continue;
			}
			if (cross_point != A) {
				if (std::find(seved_points.begin(), seved_points.end(), cross_point.value()) == seved_points.end()) {
					double distance = PtoPDistance(A, cross_point.value());
					distance_cont[distance] = cross_point.value();
					seved_points.push_back(cross_point.value());
				}
			}
			if (cross_point != B
				&& std::find(seved_points.begin(), seved_points.end(), B) == seved_points.end()
				&& PointInPoligon(B)) {
				double distance = PtoPDistance(B, A);
				distance_cont[distance] = B;
				seved_points.push_back(B);
			}
			if (cross_point != C
				&& std::find(seved_points.begin(), seved_points.end(), C) == seved_points.end()
				&& other.PointInPoligon(C)) {
				double distance = PtoPDistance(cross_point.value(), A) + PtoPDistance(cross_point.value(), C);
				distance_cont[distance] = C;
				seved_points.push_back(C);
			}
			if (cross_point != D
				&& std::find(seved_points.begin(), seved_points.end(), D) == seved_points.end()
				&& other.PointInPoligon(D)) {
				double distance = PtoPDistance(cross_point.value(), A) + PtoPDistance(cross_point.value(), D);
				distance_cont[distance] = D;
				seved_points.push_back(D);
			}

			prev_j = j;
		}
		for (const auto& [dist, point] : distance_cont) {
			cross_poligon.AddPoint(point, cross_pol_size++);
		}
		prev_i = i;
		prev_j = GetSize() - 1;
	}
	if (cross_poligon.GetSize() == 0) {
		if (PointInPoligon(other.GetPoint(1))) return other;
		if (other.PointInPoligon(poligon[0])) return *this;
	}
	return cross_poligon;
}

Poligon Poligon::Union(const Poligon& other) const {
	Poligon result;
	// add MacroCollision check to return empty if two poligons are far away from each other
	size_t cross_pol_size = 0;
	size_t prev_crosser_id = other.GetSize();
	size_t prev_baser_id = GetSize();
	size_t crosser_id = 1;
	const Poligon* crosser_ptr = &other;
	const Poligon* baser_ptr = this;
	while (crosser_id <= other.GetSize()
		&& (PointInPoligon(other.GetPoint(prev_crosser_id)) == true
		|| PointOnPoligonEdge(other.GetPoint(prev_crosser_id)) != -1)) {
		prev_crosser_id = crosser_id++;
	}
	if (crosser_id > other.GetSize()) {
		return *this;
	}
	double random = 1'000'000'007;
	bool has_cross = false;
	Point finisher = crosser_ptr->GetPoint(prev_crosser_id);
	while (true) {
		Point A(crosser_ptr->GetPoint(prev_crosser_id).x, crosser_ptr->GetPoint(prev_crosser_id).y);
		Point B(crosser_ptr->GetPoint(crosser_id).x, crosser_ptr->GetPoint(crosser_id).y);
		Point min(-random, random);
		double min_dist = random;
		size_t min_baser_id = baser_ptr->GetSize() + 1;
		for (size_t j = 1; j <= baser_ptr->GetSize(); ++j) {
			Point C(baser_ptr->GetPoint(prev_baser_id).x, baser_ptr->GetPoint(prev_baser_id).y);
			Point D(baser_ptr->GetPoint(j).x, baser_ptr->GetPoint(j).y);
			std::optional<Point> cross_point = LineCrossingPoint(A, B, C, D);
			if (cross_point.has_value()
				&& cross_point.value() != D) {
				has_cross = true;
				double distance = PtoPDistance(cross_point.value(), A);
				if (distance < min_dist) {
					min_dist = distance;
					min = cross_point.value();
					min_baser_id = j;
				}
			}
			prev_baser_id = j;
		}
		if (min_dist == random) {
			result.AddPoint(B, cross_pol_size++);
			prev_crosser_id = crosser_id++;
			if (crosser_id > crosser_ptr->GetSize()) crosser_id = 1;
		}
		else {
			result.AddPoint(min, cross_pol_size++);
			result.AddPoint(baser_ptr->GetPoint(min_baser_id), cross_pol_size++);
			std::swap(crosser_ptr, baser_ptr);
			prev_crosser_id = min_baser_id;
			min_baser_id + 1 > crosser_ptr->GetSize() ? crosser_id = 1 : crosser_id = min_baser_id + 1;
			prev_baser_id = baser_ptr->GetSize();
		}
		if (result.GetPoint(result.GetSize()) == finisher) break;
	}
	if (!has_cross) {
		if(other.PointInPoligon(poligon[0])) return other;
		return Poligon();
	}
	result.Optimize();
	return result;
}

void Poligon::Print(std::ostream& out) const {
	out << "{ ";
	bool IsFirst = true;
	for (const auto& point : poligon) {
		if (!IsFirst) {
			out << ", ";
		}
		else {
			IsFirst = false;
		}
		out << "( ";
		out << point.x;
		out << ", ";
		out << point.y;
		out << " )";
	}
	out << " }";
}

Poligon operator+(const Poligon& P_1, const Poligon& P_2) {
	return P_1.Union(P_2);
}