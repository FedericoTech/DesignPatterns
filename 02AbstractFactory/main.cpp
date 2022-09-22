#include <iostream>
#include <memory>
#include "AbstractFactory.hpp"

#define LINUX

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
