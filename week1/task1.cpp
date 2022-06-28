#include <vector>
#include <cmath>

struct Point {
    double x;
    double y;
};

std::vector<Point> terribleTrigonometry(unsigned int n) {
    std::vector<Point> res;
    double x, y;
    Point pnt{};
    double step = 2 * M_PI / n;
    for (int i = 0; i < n; i++) {
        x = std::cos(0 + step * i);
        y = std::sin(0 + step * i);
        pnt = {x, y};
        res.push_back(pnt);
    }
    return res;
}