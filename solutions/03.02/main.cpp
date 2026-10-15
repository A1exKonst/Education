// Problem 03.02:
/*
Implement a Circle class to represent circles.
Implement a private field of type double in the Circle class to store the
radius.

Implement a Triangle class to represent triangles.
Implement three private fields of type double in the Triangle class to store the
lengths of the three sides.

Implement a Square class to represent squares.
Implement a private field of type double in the Square class to store the length
of one side.

Implement the necessary user-defined constructors and public member functions
perimeter and area in the Circle, Triangle, and Square classes to calculate the
perimeter and area, respectively. Use the standard constant std::numbers::pi in
the perimeter and area member functions of the Circle class.
*/

#include <cassert>
#include <cmath>
#include <numbers> // std::numbers::pi
#include <print>

class Circle {
private:
  double radius;

public:
  Circle(double r) : radius(r) {}
  Circle(const Circle &) = default;
  Circle(Circle &&) = default;
  ~Circle() = default;

  double perimeter() const { return 2 * std::numbers::pi * radius; }

  double area() const { return std::numbers::pi * radius * radius; }
};

class Triangle {
private:
  double a;
  double b;
  double c;

public:
  Triangle(double side1, double side2, double side3)
      : a(side1), b(side2), c(side3) {}
  Triangle(const Triangle &) = default;
  Triangle(Triangle &&) = default;
  ~Triangle() = default;

  double perimeter() const { return a + b + c; }

  double area() const { // Heron's formula is used
    double p = perimeter() / 2.0;
    return std::sqrt(p * (p - a) * (p - b) * (p - c));
  }
};

class Square {
private:
  double side;

public:
  Square(double s) : side(s) {}
  Square(const Square &) = default;
  Square(Square &&) = default;
  ~Square() = default;

  double perimeter() const { return 4 * side; }

  double area() const { return side * side; }
};

int main() {

  // test Circle:
  Circle circle(5.0);
  assert(31.4 < circle.perimeter() && circle.perimeter() < 31.5);
  assert(78.5 < circle.area() && circle.area() < 78.6);

  // test Triangle:
  Triangle triangle(3.0, 4.0, 5.0);
  assert(11.99 < triangle.perimeter() && triangle.perimeter() < 12.01);
  assert(5.99 < triangle.area() && triangle.area() < 6.01);

  // test Square:
  Square square(4.0);
  assert(15.99 < square.perimeter() && square.perimeter() < 16.01);
  assert(15.99 < square.area() && square.area() < 16.01);

  std::print("[ PASSED ]\n");
  return 0;
}
