#include <iostream>

//Step 1
struct Shape {
	virtual void draw() = 0;
	virtual ~Shape() = 0;
};

Shape::~Shape(){};

//Step 2
class Rectangle: public Shape {
	void draw() {
		std::cout << "Shape: Rectangle" << std::endl;
	}
};

class Circle: public Shape {
	void draw() {
		std::cout << "Shape: Circle" << std::endl;
	}
};

//Step 3

struct ShapeDecorator: public Shape {
	ShapeDecorator(Shape *decoratedShape):decoratedShape(decoratedShape) {};
	void draw(){
		decoratedShape->draw();
	}
	virtual ~ShapeDecorator() = 0; //to keep this class abstract as well
protected:
	Shape *decoratedShape;
};

ShapeDecorator::~ShapeDecorator(){}; //to keep this class abstract as well


//Step 4

class RedShapeDecorator: public ShapeDecorator {
	void setRedBorder(Shape *decoratedShape){
		std::cout << "Border Color: Red" << std::endl;
	}
public:
	RedShapeDecorator(Shape *decoratedShape):ShapeDecorator(decoratedShape){};

	void draw() {
		decoratedShape->draw();
		setRedBorder(decoratedShape);
	}
};

//Step 5

int main(){

	Shape *circle = new Circle();

	Shape *redCircle = new RedShapeDecorator(new Circle());

	Shape *redRectangle = new RedShapeDecorator(new Rectangle());
	std::cout << "Circle with normal border" << std::endl;
	circle->draw();

	std::cout << std::endl;

	std::cout << "Circle of red border" << std::endl;
	redCircle->draw();

	std::cout << std::endl;

	std::cout << "Rectangle of red border" << std::endl;
	redRectangle->draw();

	return 0;
}
