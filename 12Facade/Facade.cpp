#include <iostream>

//Step 1
struct Shape{
	virtual void draw() = 0;
	virtual ~Shape() = 0;
};
Shape::~Shape(){}

//Step 2
class Rectangle: public Shape
{
	void draw()
	{
		std::cout << "Rectangle::draw()" << std::endl;
	}
};

class Square: public Shape
{
	void draw()
	{
		std::cout << "Square::draw()" << std::endl;
	}
};

class Circle: public Shape
{
	void draw()
	{
		std::cout << "Circle::draw()" << std::endl;
	}
};

//Step 3
class ShapeMaker{

	Shape *circle;
	Shape *rectangle;
	Shape *square;

public:
	ShapeMaker(): circle(new Circle()), rectangle(new Rectangle), square(new Square()){};

	void drawCircle(){
		circle->draw();
	}

	void drawRectangle(){
		rectangle->draw();
	}

	void drawSquare(){
		square->draw();
	}
};

//Step 4
int main()
{
	ShapeMaker shapeMaker;

	shapeMaker.drawCircle();
	shapeMaker.drawRectangle();
	shapeMaker.drawSquare();

	return 0;
}
