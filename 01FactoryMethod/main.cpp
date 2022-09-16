#include <iostream>
#include <vector>

#include "FactoryMethod.hpp"


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
				static_cast<Animal::AnimalTypes>(choice) //casting the entry to the animal type.
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
