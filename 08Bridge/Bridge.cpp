#include <iostream>

//Step 1
struct DrawAPI{
	virtual void drawCircle(int radius, int x, int y) = 0;
	virtual ~DrawAPI() {};
};

//Step 2
class RedCircle: public DrawAPI{
	void drawCircle(int radius, int x, int y) {
		std::cout << "Drawing Circle[ color: red, radius: " << radius << ", x: " << x << ", y: " << y << "]" << std::endl;
	}
};

class GreenCircle: public DrawAPI {
	void drawCircle(int radius, int x, int y) {
		std::cout << "Drawing Circle[ color: green, radius: " << radius << ", x: " << x << ", y: " << y << "]" << std::endl;
	}
};

//Step 3
struct Shape {
	virtual void draw() = 0;
	virtual ~Shape(){};

	protected:
		DrawAPI *drawAPI;
		Shape(DrawAPI &drawAPI): drawAPI(&drawAPI) {};
};

//Step 4
class Circle: public Shape {
	int x, y, radius;

public:
	Circle(DrawAPI &drawAPI, int x, int y, int radius): Shape(drawAPI), x(x), y(y), radius(radius){};

	void draw(){
		this->drawAPI->drawCircle(radius, x, y);
	}
};

//Step 5
int main(){

	RedCircle rc;

	//abstract classes have to be pointed to
	Shape *redCircle = new Circle(rc, 100, 100, 10);

	GreenCircle gc;

	Shape *greenCircle = new Circle(gc, 100, 100, 10);

	redCircle->draw();

	greenCircle->draw();

	return 0;


}
