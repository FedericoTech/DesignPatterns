#include <iostream>
#include <vector>

class Animal {
protected:
	int some_value = -1;
public:
	Animal(){};
	Animal(int value):some_value(value){};
	virtual Animal* clone() = 0;
	virtual void make_noise() = 0;
	virtual ~Animal(){};
};

class Factory {
public:
	static Animal* make_animal(int choice);
private:
	static Animal* s_prototypes[4];
};

int main() {
	std::vector<Animal*> animals;
	int choice;

	while(true){
		std::cout << "Horse: 1, Dog: 2, Cat: 3, run: 0" << std::endl;

		std::cin >> choice;

		if(choice == 0){
			break;
		}

		animals.push_back(
			Factory::make_animal(choice)
		);
	}

	for(auto animal : animals){
		animal->make_noise();
	}

	for(auto animal : animals){
		delete animal;
	}
}

class Horse : public Animal{
public:
	Horse(){};
	Horse(int value):Animal(value){};
	Animal* clone() { return new Horse(*this);}
	void make_noise(){
		std::cout << "Horse whines, " << some_value << " address: " << this << std::endl;
	}
};

class Dog : public Animal{
public:
	Dog(){};
	Dog(int value):Animal(value){};
	Animal* clone() { return new Dog(*this);}
	void make_noise(){
		std::cout << "Dog barks, value: " << some_value << " address: " << this <<std::endl;
	}
};

class Cat : public Animal{
public:
	Cat(){};
	Cat(int value):Animal(value){};
	Animal* clone() { return new Cat(*this);}
	void make_noise(){
		std::cout << "Cat mews, value: " << some_value << " address: " << this <<std::endl;
	}
};

Animal* Factory::s_prototypes[] = {
	0, new Horse(1), new Dog(2), new Cat(3)
};

Animal* Factory::make_animal(int choice){
	return s_prototypes[choice]->clone();
}
