/*
 * FactoryMethod.hpp
 *
 *  Created on: 16 Sept 2022
 *      Author: david
 */

#ifndef FACTORYMETHOD_HPP_
#define FACTORYMETHOD_HPP_



//abstract class Animal
struct Animal
{
	//forward declaration of this enum class
	enum class AnimalTypes : char {
		Horse = 1, Dog = 2, Cat = 3
	};

	static Animal* make_animal(AnimalTypes st); //Factory Method

	virtual void make_a_noise() = 0; //pure virtual member function

	virtual ~Animal() = 0;
};

//fore declaration of the derived classes

class Horse;

class Dog;

class Cat;

#endif /* FACTORYMETHOD_HPP_ */
