#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

// 浮点数精度控制
const double EPS = 1e-10;

struct Point {
    double x, y;
};

// 向量叉积 (p1-p0) x (p2-p0)
double crossProduct(Point p0, Point p1, Point p2) {
    return (p1.x - p0.x) * (p2.y - p0.y) - (p2.x - p0.x) * (p1.y - p0.y);
}

// 辅助函数：判断 value 是否在 [min, max] 之间（考虑精度）
bool isBetween(double val, double range1, double range2) {
    double minVal = std::min(range1, range2);
    double maxVal = std::max(range1, range2);
    return val >= minVal - EPS && val <= maxVal + EPS;
}

// 判断点 p 是否在线段 ab 上 (共线的前提下)
bool onSegment(Point p, Point a, Point b) {
    return isBetween(p.x, a.x, b.x) && isBetween(p.y, a.y, b.y);
}

int main(int argc, char* argv[]) {
    // 必须有 8 个坐标参数 + 1 个程序名 = 9 个参数 [cite: 39]
    if (argc != 9) {
        // 题目未明确参数错误的输出，为了健壮性，这里输出 FALSE 或提示，
        // 但根据题目风格，我们假设输入由测试脚本保证，或者直接返回 FALSE。
        // 这里选择输出提示并退出。
        std::cerr << "Usage: ./check x1 y1 x2 y2 x3 y3 x4 y4" << std::endl;
        return 1;
    }

    try {
        Point p1 = {std::stod(argv[1]), std::stod(argv[2])};
        Point p2 = {std::stod(argv[3]), std::stod(argv[4])};
        Point p3 = {std::stod(argv[5]), std::stod(argv[6])};
        Point p4 = {std::stod(argv[7]), std::stod(argv[8])};

        // 1. 快速排斥实验 (Bounding Box Test)
        // 如果矩形不相交，线段一定不相交
        if (std::max(p1.x, p2.x) < std::min(p3.x, p4.x) ||
            std::max(p3.x, p4.x) < std::min(p1.x, p2.x) ||
            std::max(p1.y, p2.y) < std::min(p3.y, p4.y) ||
            std::max(p3.y, p4.y) < std::min(p1.y, p2.y)) {
            std::cout << "FALSE" << std::endl;
            return 0;
        }

        // 2. 跨立实验 (Straddle Test)
        // 计算四个叉积
        double cp1 = crossProduct(p1, p2, p3);
        double cp2 = crossProduct(p1, p2, p4);
        double cp3 = crossProduct(p3, p4, p1);
        double cp4 = crossProduct(p3, p4, p2);

        // 如果 ((p3, p4) 在 (p1, p2) 两侧) 且 ((p1, p2) 在 (p3, p4) 两侧)
        if (((cp1 > EPS && cp2 < -EPS) || (cp1 < -EPS && cp2 > EPS)) &&
            ((cp3 > EPS && cp4 < -EPS) || (cp3 < -EPS && cp4 > EPS))) {
            std::cout << "TRUE" << std::endl;
            return 0;
        }

        // 3. 处理特殊情况：共线且接触 (Collinear and touching/overlapping)
        // 如果叉积为0，说明点在直线上，检查点是否在线段上
        if (std::abs(cp1) <= EPS && onSegment(p3, p1, p2)) { std::cout << "TRUE" << std::endl; return 0; }
        if (std::abs(cp2) <= EPS && onSegment(p4, p1, p2)) { std::cout << "TRUE" << std::endl; return 0; }
        if (std::abs(cp3) <= EPS && onSegment(p1, p3, p4)) { std::cout << "TRUE" << std::endl; return 0; }
        if (std::abs(cp4) <= EPS && onSegment(p2, p3, p4)) { std::cout << "TRUE" << std::endl; return 0; }

        std::cout << "FALSE" << std::endl;

    } catch (...) {
        // 浮点转换失败等
        std::cout << "FALSE" << std::endl;
    }

    return 0;
}