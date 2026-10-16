// Problem 03.06
/*
Refine your previous solution to problem 03.02
        so that the implementation uses a class hierarchy for geometric shapes
instead of separate classes. Implement an abstract base class Shape to represent
the interface for geometric shapes. Implement a virtual destructor and public
pure virtual member functions perimeter and area in the Shape class to calculate
the perimeter and area, respectively. Implement a derived class Circle to
represent circles, which inherits from the Shape class interface. Implement a
derived abstract base class Polygon to represent polygons, which inherits from
the Shape class interface. Implement derived classes Triangle and Rectangle to
represent triangles and rectangles, respectively, which inherit from the Polygon
class interface. Implement a derived class Square to represent squares, which
inherits from the Rectangle class interface. Do not create a field in the Square
class to store the side length of the square. Implement only a user-defined
constructor in the Square class that passes arguments to the Rectangle class
constructor. Use the override specifier when overriding the inherited virtual
member functions perimeter and area in the Circle, Triangle, and Rectangle
classes. Use the final specifier to prohibit inheritance from the Circle and
Square classes, and to prohibit overriding the inherited virtual member
functions perimeter and area in the descendants of the Rectangle class. Use the
standard container std::vector to store instances of the Circle, Triangle, and
Square classes via pointers to the Shape class. Demonstrate the operation of
dynamic polymorphism.
*/

/*
NOTE: Liskov Substitution Problem:

A task requires a Square to inherit from Rectangle.
It makes mathematical sense.

But speaking about interfaces and classes it is incorrect:
Square narrows down the interface of a Rectangle.
In this sense when Rectangle::width is changed, Rectangle::height is not
expected to be changed.

Nevertheless, inheritance is performed as was required in task (Square: public
Rectangle).
*/

#include <cmath>
#include <numbers>
#include <print>
#include <vector>

class Shape;
class Polygon;
class Circle;
class Triangle;
class Rectangle;
class Square;

// Abstract base class
class Shape {
public:
  virtual ~Shape() = default;

  [[nodiscard]] virtual auto perimeter() const -> double = 0;
  [[nodiscard]] virtual auto area() const -> double = 0;
};

// Abstract base class for derived Triangle and Rectangle
class Polygon : public Shape {};

class Circle final : public Shape {
private:
  double radius;

public:
  explicit Circle(double r) : radius(r) {
    if (radius < 0.0) {
      throw std::invalid_argument("Circle::radius cannot be negative");
    }
  }

  [[nodiscard]] auto perimeter() const -> double override {
    return 2 * std::numbers::pi * radius;
  }

  [[nodiscard]] auto area() const -> double override {
    return std::numbers::pi * radius * radius;
  }
};

class Triangle : public Polygon {
private:
  double a, b, c;

public:
  Triangle(double side1, double side2, double side3)
      : a(side1), b(side2), c(side3) {}

  [[nodiscard]] auto perimeter() const -> double override { return a + b + c; }

  [[nodiscard]] auto area() const -> double override {
    // Heron's formula
    double p = perimeter() / 2.0;
    return std::sqrt(p * (p - a) * (p - b) * (p - c));
  }
};

class Rectangle : public Polygon {
private:
  double width;
  double height;

public:
  Rectangle(double w, double h) : width(w), height(h) {}

  [[nodiscard]] auto perimeter() const -> double final {
    return 2 * (width + height);
  }

  [[nodiscard]] auto area() const -> double final { return width * height; }
};

class Square final : public Rectangle {
public:
  explicit Square(double side) : Rectangle(side, side) {}
};

auto main() -> int {

  // init tests
  std::vector<Shape *> shapes = {new Circle(5.0), new Triangle(3.0, 4.0, 5.0),
                                 new Rectangle(4.0, 6.0), new Square(4.0)};

  for (const auto &shape : shapes) {
    std::print("Perimeter: {}, Area: {}\n", shape->perimeter(), shape->area());
  }

  // free alloc from tests
  for (auto &shape : shapes) {
    delete shape;
  }

  return 0;
}
