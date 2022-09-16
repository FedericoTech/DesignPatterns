#include "FactoryMethod.hpp"
#include <iostream>

Animal::~Animal(){};

class Horse : public Animal
{
public:
	void make_a_noise()
	{
		std::cout << "Horse whines" << std::endl;
	}
};

class Dog : public Animal
{
public:
	void make_a_noise()
	{
		std::cout << "Dog barks" << std::endl;
	}
};

class Cat : public Animal
{
public:
	void make_a_noise()
	{
		std::cout << "Cat mews" << std::endl;
	}
};

//this is the factory function
Animal* Animal::make_animal(AnimalTypes st)
{
	switch (st) {
	
	case AnimalTypes::Horse:
		return new Horse;

	case AnimalTypes::Dog:
		return new Dog;
	
	case AnimalTypes::Cat:
		return new Cat;
	default:
		return nullptr;
	}
}
