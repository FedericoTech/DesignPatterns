
#include "AbstractFactory.hpp"

Widget::~Widget(){};

//concrete product family 1
void LinuxButton::draw(){
	std::cout << "LinuxButton" << std::endl;
};

void LinuxMenu::draw(){
	std::cout << "LinuxMenu" << std::endl;
};

//concrete product family 2
void WindowsButton::draw() {
	std::cout << "WindowsButton" << std::endl;
};

void WindowsMenu::draw(){
	std::cout << "WindowsMenu" << std::endl;
};

//abstract factory
Factory::~Factory(){}

//concrete factory for Linux
Widget* LinuxFactory::create_button(){
	return new LinuxButton;
}

Widget* LinuxFactory::create_menu(){
	return new LinuxMenu;
};

//concrete factory for windows
Widget* WindowsFactory::create_button(){
	return new WindowsButton;
};

Widget* WindowsFactory::create_menu(){
	return new WindowsMenu;
};

//client class that makes use of the factory that is passed to its constructor.
void Client::draw() {
	Widget *w = factory->create_button();
	w->draw();
	display_windows_one();
	display_windows_two();

	delete w;
}

void Client::display_windows_one(){
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

void Client::display_windows_two(){
	Widget *w[] = {
		factory->create_button(),
		factory->create_menu()
	};

	w[0]->draw();
	w[1]->draw();

	for(auto e: w){
		delete e;
	}
};
