#include<iostream>

//Step 1

struct Image
{
	virtual void display() = 0;
	virtual ~Image() = 0;
};

Image::~Image(){};

//Step 2

class RealImage: public Image {
	std::string fileName;

	void loadFromDisk(std::string fileName)
	{
		std::cout << "Loading " << fileName << std::endl;
	}

public:
	RealImage(std::string fileName): fileName(fileName){
		loadFromDisk(fileName);
	}

	void display() override
	{
		std::cout << "Displaying " << fileName << std::endl;
	}
};

class ProxyImage: public Image
{
	RealImage *realImage = nullptr;

	std::string fileName;

public:
	ProxyImage(std::string fileName): fileName(fileName){}

	void display() override {
		if(realImage == nullptr){
			realImage = new RealImage(fileName);
		}

		realImage->display();
	}
};

//Step 3

int main()
{
	Image *image = new ProxyImage("test_10mb.jpg");

	//image will be loaded from disk
	image->display();

	std::cout << std::endl;

	//image will not be loaded from disk
	image->display();

	return 0;
}
