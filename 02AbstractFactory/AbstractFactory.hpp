/*
 * AbstractFactory.hpp
 *
 *  Created on: 22 Sept 2022
 *      Author: david
 */

#ifndef ABSTRACTFACTORY_HPP_
#define ABSTRACTFACTORY_HPP_

#include <iostream>
#include <memory>

//abstract class
struct Widget {
	virtual void draw() = 0;
	virtual ~Widget() = 0;
};

//concrete product family 1
class LinuxButton: public Widget {
public:
	void draw();
};

class LinuxMenu : public Widget {
public:
	void draw();
};

//concrete product family 2
class WindowsButton : public Widget{
public:
	void draw();
};

class WindowsMenu : public Widget {
public:
	void draw();
};

//abstract factory
class Factory {
public:
	virtual Widget* create_button() = 0;
	virtual Widget* create_menu() = 0;
	virtual ~Factory() = 0;
};

//concrete factory for Linux
class LinuxFactory : public Factory{
public:
	Widget* create_button();

	Widget* create_menu();
};

//concrete factory for windows
class WindowsFactory : public Factory{
public:
	Widget* create_button();

	Widget* create_menu();
};

//client class that makes use of the factory that is passed to its constructor.
class Client {
	std::unique_ptr<Factory> factory;
public:

	Client(std::unique_ptr<Factory> f): factory(std::move(f)){}

	void draw();

	void display_windows_one();

	void display_windows_two();
};


#endif /* ABSTRACTFACTORY_HPP_ */
