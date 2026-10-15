// Problem 03.01
/*
Implement the Rectangle structure to represent rectangles with sides parallel to
the coordinate axes. Implement four int fields in the Rectangle structure to
store the coordinates of the top-left and bottom-right corners of the rectangle.
Use a coordinate system where the x-axis points to the right and the y-axis
points down. Implement an algorithm to calculate the intersection area of
several rectangles. Consider the cases of empty and degenerate rectangle
intersections. Implement an algorithm to calculate the minimum bounding
rectangle for several rectangles. Use the standard container std::vector to
store instances of the Rectangle structure.
*/

#include <algorithm>
#include <cassert>
#include <optional>
#include <print>
#include <vector>

struct Rectangle;

auto intersectTwo(const Rectangle &r1,
                  const Rectangle &r2) -> std::optional<Rectangle>;

auto getIntersection(const std::vector<Rectangle> &rectangles)
    -> std::optional<Rectangle>;

auto getIntersectionArea(const std::vector<Rectangle> &rectangles) -> long long;

auto getMinimumBoundingRectangle(const std::vector<Rectangle> &rectangles)
    -> std::optional<Rectangle>;

struct Rectangle {
public:
  int x1; // upper left X
  int y1; // upper left Y
  int x2; // down right X
  int y2; // down right Y

  bool isValid() const { // not inverted coordinates
    return x1 <= x2 && y1 <= y2;
  }

  long long area() const {
    if (x1 >= x2 || y1 >= y2) {
      return 0;
    }
    return static_cast<long long>(x2 - x1) * (y2 - y1);
  }
};

auto intersectTwo(const Rectangle &r1,
                  const Rectangle &r2) -> std::optional<Rectangle> {
  int intersect_x1 = std::max(r1.x1, r2.x1);
  int intersect_y1 = std::max(r1.y1, r2.y1);
  int intersect_x2 = std::min(r1.x2, r2.x2);
  int intersect_y2 = std::min(r1.y2, r2.y2);

  if (intersect_x1 > intersect_x2 || intersect_y1 > intersect_y2) {
    return std::nullopt;
  }

  return Rectangle{intersect_x1, intersect_y1, intersect_x2, intersect_y2};
}

auto getIntersection(const std::vector<Rectangle> &rectangles)
    -> std::optional<Rectangle> {

  if (rectangles.empty())
    return std::nullopt;
  Rectangle current_intersect = rectangles[0];

  for (size_t i = 1; i < rectangles.size(); ++i) {
    auto next_intersect = intersectTwo(current_intersect, rectangles[i]);
    if (!next_intersect.has_value()) {
      return std::nullopt;
    }
    current_intersect = *next_intersect;
  }

  return current_intersect;
}

auto getIntersectionArea(const std::vector<Rectangle> &rectangles)
    -> long long {
  auto intersection = getIntersection(rectangles);
  if (!intersection.has_value())
    return 0;
  return intersection.value().area();
}

// Algorithm to find least rectangle, bounding given rectangles:
auto getMinimumBoundingRectangle(const std::vector<Rectangle> &rectangles)
    -> std::optional<Rectangle> {
  if (rectangles.empty())
    return std::nullopt;

  int min_x = rectangles[0].x1;
  int min_y = rectangles[0].y1;
  int max_x = rectangles[0].x2;
  int max_y = rectangles[0].y2;

  for (size_t i = 1; i < rectangles.size(); ++i) {
    min_x = std::min(min_x, rectangles[i].x1);
    min_y = std::min(min_y, rectangles[i].y1);
    max_x = std::max(max_x, rectangles[i].x2);
    max_y = std::max(max_y, rectangles[i].y2);
  }

  return Rectangle{min_x, min_y, max_x, max_y};
}

int main() {

  // test data:
  std::vector<Rectangle> rects = {{0, 0, 3, 4}, {2, 2, 6, 6}, {1, 1, 3, 5}};

  // test Rectangle::area()
  assert(rects[0].area() == 12);
  assert(rects[1].area() == 16);
  assert(rects[2].area() == 8);

  // test getIntersection(...)
  std::optional<Rectangle> inter_opt = getIntersection(rects);
  assert(inter_opt.has_value());
  Rectangle inter = inter_opt.value();
  assert(inter.x1 == 2 && inter.y1 == 2 && inter.x2 == 3 && inter.y2 == 4);

  // test getIntersectionArea(...)
  assert(getIntersectionArea(rects) == 2);

  // test getMinimumBoundingRectangle(...)
  auto bound_rect = getMinimumBoundingRectangle(rects);
  assert(bound_rect);
  assert(bound_rect->x1 == 0 && bound_rect->y1 == 0 && bound_rect->x2 == 6 &&
         bound_rect->y2 == 6);

  // Example with no intersection:
  std::vector<Rectangle> degenerate_rects = {{0, 0, 2, 2}, {2, 0, 4, 2}};
  assert(getIntersectionArea(degenerate_rects) == 0);

  std::print("[ PASSED ]\n");
  return 0;
}
