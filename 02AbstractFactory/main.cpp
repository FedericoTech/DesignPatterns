
#include <iostream>

#define LINUX

//abstract class
class Widget {
public:
	virtual void draw() = 0;
};


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
};


//concrete factory for linux
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
private:
	Factory *factory;
public:

	Client(Factory *f): factory(f){}

	void draw() {
		Widget *w = factory->create_button();
		w->draw();
		display_windows_one();
		display_windows_two();
	}

	void display_windows_one(){
		Widget *w[] = {
			factory->create_button(),
			factory->create_menu()
		};

		w[0]->draw();
		w[1]->draw();
	}

	void display_windows_two(){
		Widget *w[] = {
			factory->create_button(),
			factory->create_menu()
		};

		w[0]->draw();
		w[1]->draw();
	}
};

int main() {
	Factory *factory;

#ifdef LINUX
	factory = new LinuxFactory;
#else
	factory = new WindowsFactory;
#endif

	Client *c = new Client(factory);

	c->draw();

	return 0;
}
