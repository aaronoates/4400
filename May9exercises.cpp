#include <cmath>
#include <iostream>
using namespace std;


class Shape
{
	public:
	double area() const { return 0; }
};

class Circle
{
	public:
	Circle(double radius)
		: radius_(radius)
	{
	}

	double area() const { return M_PI * radius_ * radius_; }

	private:
	const double radius_;
};

class Rectangle
{
	public:
	Rectangle(double height, double width)
		: height_(height) , width_(width)
	{
		
	}

	double area() const { return height_ * width_; }

	private:
	const double height_;
	const double width_;
};


int main()
{
	Shape generic;
	Circle c1(5);
	Circle c2(10);
	Rectangle r1(5, 10);
	Rectangle r2(123, 2);

	cout << "generic @ " << &generic << ": " << generic.area() << endl;
	cout << "c1 @ " << &c1 << ": " << c1.area() << endl;
	cout << "c2 @ " << &c2 << ": " << c2.area() << endl;
	cout << "r1 @ " << &r1 << ": " << r1.area() << endl;
	cout << "r2 @ " << &r2 << ": " << r2.area() << endl;

	Shape *couldBeAnything = &r1;
	cout << "Final area: " << couldBeAnything->area() << endl;

	return 0;
}