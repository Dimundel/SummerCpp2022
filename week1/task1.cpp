#include <vector>
#include <cmath>

struct Point {
    double x;
    double y;
};

std::vector<Point> terribleTrigonometry(unsigned int n) {
    std::vector<Point> res;
    double x, y;
    double a = sin(2 * M_PI / n);
    double b = cos(2 * M_PI / n);
    Point pnt{1.0, 0.0};
    res.push_back(pnt);
    for (int i = 1; i < n; i++) {
        x = res[i - 1].x * b - res[i - 1].y * a;
        y = res[i - 1].y * b + res[i - 1].x * a;
        pnt = {x, y};
        res.push_back(pnt);
    }
    return res;
}