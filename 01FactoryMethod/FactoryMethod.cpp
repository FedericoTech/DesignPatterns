#include <iostream>
#include <vector>

//forward declaration of this enum class
enum class AnimalTypes : char;

//abstract class Animal
struct Animal
{
	static Animal* make_animal(AnimalTypes st); //Factory Method

	virtual void make_a_noise() = 0; //pure virtual member function

	virtual ~Animal() = 0;
};

Animal::~Animal(){};

int main()
{
	std::vector<Animal*> animals;

	int choice;

	//repeat till break
	while (true) {
		std::cout << "Horse: 1, Dog: 2, Cat: 3, run: 0" << std::endl;
		std::cin >> choice;

		if (choice == 0) {
			break;
		}

		animals.push_back(
			Animal::make_animal(
				static_cast<AnimalTypes>(choice) //casting the entry to the animal type.
			)
		);
	}

	//we run the vector to do the action
	for (auto animal : animals) {
		animal->make_a_noise();
	}

	//we delete all animals.
	for (size_t i = 0; i < animals.size(); i++) {
		delete animals[i];
	}

	return 0;
}

class Horse : public Animal
{
public:
	void make_a_noise()
	{
		std::cout << "Horse whinnys" << std::endl;
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

enum class AnimalTypes : char {
	Horse = 1, Dog = 2, Cat = 3
};

//this is the factory function
Animal* Animal::make_animal(AnimalTypes st)
{
	switch (st) {
	
	case AnimalTypes::Horse:
		return new Horse;

	case AnimalTypes::Dog:
		return new Dog;
	
	default:
		return new Cat;
	}
}
