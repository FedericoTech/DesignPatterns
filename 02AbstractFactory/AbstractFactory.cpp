
#include <iostream>
#include <memory>

#define LINUX

//abstract class
struct Widget {
	virtual void draw() = 0;
	virtual ~Widget() = 0;
};
Widget::~Widget(){};


//concrete product family 1
class LinuxButton: public Widget {
public:
	void draw(){
		std::cout << "LinuxButton" << std::endl;
	}
};

class LinuxMenu : public Widget {
public:
	void draw(){
		std::cout << "LinuxMenu" << std::endl;
	}
};

//concrete product family 2
class WindowsButton : public Widget{
public:
	void draw() {
		std::cout << "WindowsButton" << std::endl;
	}
};

class WindowsMenu : public Widget {
public:
	void draw(){
		std::cout << "WindowsMenu" << std::endl;
	}
};

//abstract factory
class Factory {
public:
	virtual Widget* create_button() = 0;
	virtual Widget* create_menu() = 0;
	virtual ~Factory() = 0;
};
Factory::~Factory(){}

//concrete factory for Linux
class LinuxFactory : public Factory{
public:
	Widget* create_button(){
		return new LinuxButton;
	}

	Widget* create_menu(){
		return new LinuxMenu;
	}
};

//concrete factory for windows
class WindowsFactory : public Factory{
public:
	Widget* create_button(){
		return new WindowsButton;
	}

	Widget* create_menu(){
		return new WindowsMenu;
	}
};

//client class that makes use of the factory that is passed to its constructor.
class Client {
	std::unique_ptr<Factory> factory;
public:

	Client(std::unique_ptr<Factory> f): factory(std::move(f)){}

	void draw() {
		Widget *w = factory->create_button();
		w->draw();
		display_windows_one();
		display_windows_two();

		delete w;
	}

	void display_windows_one(){
		Widget *w[] = {
			factory->create_button(),
			factory->create_menu()
		};

		w[0]->draw();
		w[1]->draw();

		for(auto e: w){
			delete e;
		}
	}

	void display_windows_two(){
		Widget *w[] = {
			factory->create_button(),
			factory->create_menu()
		};

		w[0]->draw();
		w[1]->draw();

		for(auto e: w){
			delete e;
		}
	}
};

int main() {
	std::unique_ptr<Factory> factory;

#ifdef LINUX
	factory = std::make_unique<LinuxFactory>();
#else
	factory = std::make_unique<WindowsFactory>();
#endif

	Client c(std::move(factory));

	c.draw();

	return 0;
}
