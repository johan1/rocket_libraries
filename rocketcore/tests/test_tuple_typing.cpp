#include "../src/TupleTyping.h"
#include <iostream>

DEFINE_TUPLE_WRAPPER(Point2d, x, double, y, double);
DEFINE_TUPLE_WRAPPER(Point3d, x, double, y, double, z, double);
DEFINE_TUPLE_WRAPPER(Point4d, x, double, y, double, z, double, w, double);

DEFINE_TUPLE_WRAPPER(Point6d, x, double, y, double, z, double, w, double, s, double, t, double);
/* Expands to...
struct Point6d : std::tuple<double, double, double, double, double, double> {
    typedef std::tuple<double, double, double, double, double, double> inherit_type;

    Point6d() = default;
    Point6d(Point6d const&) = default;
    Point6d(Point6d &&) = default;
    explicit Point6d(inherit_type const& values) : inherit_type(values) {}
    explicit Point6d(inherit_type && values) : inherit_type(std::move(values)) {}
    ~Point6d() = default;
    Point6d& operator=(Point6d const&) = default;
    Point6d& operator=(Point6d &&) = default;

    friend bool operator==(Point6d const& p1, Point6d const& p2) {
        return operator==(static_cast<inherit_type const&>(p1),
                static_cast<inherit_type const&>(p2));
    }

    friend bool operator!=(Point6d const& p1, Point6d const& p2) {
        return !operator==(p1, p2);
    }

    friend bool operator<(Point6d const& p1, Point6d const& p2) {
        return operator<(static_cast<inherit_type const&>(p1),
                static_cast<inherit_type const&>(p2));
    }

    friend bool operator>=(Point6d const& p1, Point6d const& p2) {
        return !operator<(p1, p2);
    }

    friend bool operator>(Point6d const& p1, Point6d const& p2) {
        return operator<(p2, p1);
    }

    friend bool operator<=(Point6d const& p1, Point6d const& p2) {
        return !operator<(p2, p1);
    }

    double& x() { return std::get<0>(*this); }
    double const& x() const { return std::get<0>(*this); }
    double& y() { return std::get<1>(*this); }
    double const& y() const { return std::get<1>(*this); }
    double& z() { return std::get<2>(*this); }
    double const& z() const { return std::get<2>(*this); }
    double& w() { return std::get<3>(*this); }
    double const& w() const { return std::get<3>(*this); }
    double& s() { return std::get<4>(*this); }
    double const& s() const { return std::get<4>(*this); }
    double& t() { return std::get<5>(*this); }
    double const& t() const { return std::get<5>(*this); }
};
*/

int main() {
    Point2d p;
    p.x() = 1.0f;
    p.y() = 2.0f;
    Point2d p2 = p;
    p2 = p;

    Point6d p3;
    p3.t() = p3.s() = 2;

	Point2d p4 {std::make_tuple(1.0, 2.0)};
	p4 = std::make_tuple(2.0, 3.0);

    std::cout << "x=" << p.x() << ", y=" << p.y() << std::endl;
    std::cout << "x=" << p2.x() << ", y=" << p2.y() << std::endl;

    p2.x() += 1.0;
    p2.y() += 1.0;

    std::cout << "x=" << p.x() << ", y=" << p.y() << std::endl;
    std::cout << "x=" << p2.x() << ", y=" << p2.y() << std::endl;
    std::cout << "s=" << p3.s() << ", t=" << p3.t() << std::endl;

	// TODO: I want to be able to write, v is a iterable list of point6d
	// std::sort(begin(v), end(v), compose(Point6d::s, std::less()));

    return 0;
}
