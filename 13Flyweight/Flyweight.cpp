#include <iostream>
#include <cstdlib>
#include <unordered_map>

//Step 1
struct Shape {
	virtual void draw() = 0;
	virtual ~Shape() = 0;
};

Shape::~Shape(){}

//Step 2

class Circle: public Shape
{
	std::string color;
	int x = 0;
	int y = 0;
	int radius = 0;

public:
	Circle(std::string color):color(color){};

	void setX(int x){ this->x = x; }

	void setY(int y){ this->y = y; }

	void setRadius(int radius){ this->radius = radius; }

	void draw() {
		std::cout << "Circle: Draw() [Color : " << color
			<< ", x : " << x
			<< ", y : " << y
			<< ", radius: " << radius
			<< std::endl;
	}
};

//Step 3

class ShapeFactory
{
	static std::unordered_map<std::string, Shape *> circleMap;
public:
	static Shape *getCircle(std::string color)
	{
		if(circleMap.find(color) == circleMap.end()){
			circleMap[color] = new Circle(color);

			std::cout << "Creating circle of color : " << color << std::endl;
		}

		Circle *circle = static_cast<Circle *>(circleMap[color]);

		return circle;
	}

	~ShapeFactory()
	{
		//we delete all the pointers from circleMap
		for(auto t : circleMap){
			delete t.second;
		}
	}
};

std::unordered_map<std::string, Shape *> ShapeFactory::circleMap; //we need to do this for the static member

static const std::string colours[] = {"Red", "Green", "Blue", "White", "Black"};

static std::string getRandomColor()
{
	return colours[rand() % 5];
}

static int getRandomNum()
{
	return int(rand() % 100);
}

//Step 4
int main()
{

	for(int i = 0; i < 20; i++){

		Circle* circle = static_cast<Circle *>(ShapeFactory::getCircle(getRandomColor()));

		circle->setX(getRandomNum());
		circle->setY(getRandomNum());
		circle->setRadius(100);
		circle->draw();
	}

	return 0;
}
