#include "algorithm.hpp"
#include <iostream>
#include <algorithm>

// файл с определениями

namespace itis {
  Point nextToTop(std::stack<Point> &S) {
    Point point = S.top();
    S.pop();
    Point res = S.top();
    S.push(point);
    return res;
  }

  Point p0; // Leftmost lowest point (it is global because we need it in out compare function for qsort)

  int ccw(Point p00, Point p1, Point p2) {
    int val = (p1.y - p00.y) * (p2.x - p1.x) - (p1.x - p00.x) * (p2.y - p1.y);

    if (val == 0) {
      return 0;  // collinear
    }

    return (val > 0) ? 1 : 2; // clock or counterclockwise
  }

  void swap(Point &p1, Point &p2) {
    Point temp = p1;
    p1 = p2;
    p2 = temp;
  }

  int dist_sq(Point p1, Point p2) {
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
  }

  bool compare(const Point &p1, const Point &p2) {
    // Find orientation
    int o = ccw(p0, p1, p2);

    // If points are collinear with p0, then we want to have the farthest point
    // We put the farthest point in the end of the sequence of collinear points, so we can use it later
    if (o == 0) {
      return (dist_sq(p0, p1) < dist_sq(p0, p2));
    }

    // If we make counterclockwise turn (p0->p1->p2), then p1 has smaller polar angle with p0 than p2
    return (o == 2);
  }

  void Graham::add_point(int x, int y) {
    Point p = Point(x, y);
    points.push_back(p);
    size_++;
  }

  void Graham::convex_hull() {
    if (size_ < 3) {
      return;
    }

    int min_index = find_bottom_left();

    // Place the bottom-most point at first position
    swap(points[0], points[min_index]);

    // Sort n-1 points with respect to the first point.  A point p1 comes
    // before p2 in sorted output if p2 has larger polar angle (in
    // counterclockwise direction) than p1
    p0 = points[0];
    sort(points.begin()+1, points.end(), compare);

    // If two or more points make same angle with p0,
    // Remove all but the one that is farthest from p0 (we put it in the end of the sequence of collinear points)
    int m = 1; // Initialize size of modified array
    for (int i=1; i<size_; i++)
    {
      // Keep increasing i while angle of i and i+1 is same with respect to p0 (moving along the line)
      while (i < size_-1 && ccw(p0, points[i], points[i+1]) == 0) {
        i++;
      }
      points[m] = points[i]; // Put the farthest point into modified array
      m++;  // Update size of modified array
    }

    // If modified array of points has less than 3 points,
    // convex hull is not possible
    if (m < 3) {
      return;
    }

    // Create an empty stack and push first three points to it.
    if (!S.empty()) {
      clear_stack();
    }
    S.push(points[0]);
    S.push(points[1]);
    S.push(points[2]);

    // Process remaining n-3 points
    for (int i = 3; i < m; i++) {
      // Keep removing top while the angle formed by points next-to-top,
      // top, and points[i] makes a non-left turn
      while (S.size() > 1 && ccw(nextToTop(S), S.top(), points[i]) != 2) {
        S.pop();
      }
      S.push(points[i]);
    }
    // Now stack has the output points
  }

  void Graham::convex_hull_print() {
    convex_hull();
    print_stack();
  }

  void Graham::print_stack() {
    while (!S.empty()) {
      Point p = S.top();
      std::cout << "(" << p.x << ", " << p.y << ")" << std::endl;
      S.pop();
    }
  }

  void Graham::clear_stack() {
    while (!S.empty()) {
      S.pop();
    }
  }

  int Graham::find_bottom_left() {
    int ymin = points[0].y;
    int min = 0;
    for (int i = 1; i < size_; i++) {
      int y = points[i].y;

      // Pick the bottom-most or chose the left most point in case of tie
      if ((y < ymin) || (ymin == y && points[i].x < points[min].x)) {
        ymin = points[i].y, min = i;
      }
    }

    return min;
  }
}  // namespace itis