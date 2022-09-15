#include <iostream>
#include <memory>

//Step 1
struct DrawAPI{
	virtual void drawCircle(int radius, int x, int y) = 0;
	virtual ~DrawAPI() = 0;
};

DrawAPI::~DrawAPI(){}

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
	virtual ~Shape() = 0;

	protected:
		DrawAPI *drawAPI;
		Shape(DrawAPI *drawAPI): drawAPI(drawAPI) {};
};

Shape::~Shape()
{
	delete drawAPI;
};

//Step 4
class Circle: public Shape {
	int x, y, radius;

public:
	Circle(DrawAPI *drawAPI, int x, int y, int radius): Shape(drawAPI), x(x), y(y), radius(radius){};

	void draw(){
		this->drawAPI->drawCircle(radius, x, y);
	}
};

//Step 5
int main()
{
	//abstract classes have to be pointed to
	std::unique_ptr<Shape> redCircle = std::make_unique<Circle>(new RedCircle, 100, 100, 10);

	std::unique_ptr<Shape> greenCircle = std::make_unique<Circle>(new GreenCircle, 100, 100, 10);

	redCircle->draw();

	greenCircle->draw();

	return 0;
}
