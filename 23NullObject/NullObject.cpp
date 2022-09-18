#include <iostream>
#include <algorithm>
#include <memory>

//Step 1
struct AbstractCustomer
{
protected:
	std::string name;
public:
	//AbstractCustomer(std::string name):name(name){};
	virtual bool isNil() = 0;
	virtual std::string getName() = 0;
	virtual ~AbstractCustomer() = 0;
};

AbstractCustomer::~AbstractCustomer(){};

//Step 2
class RealCustomer: public AbstractCustomer
{
public:
	RealCustomer(std::string name)
	{
		this->name = name;
	};

	std::string getName() override {
		return name;
	}

	bool isNil() override {
		return false;
	}
};


class NullCustomer: public AbstractCustomer
{
public:
	std::string getName() override {
		return "Not Available in Customer Database";
	}

	bool isNil() override {
		return true;
	}
};

//Step 3
class CustomerFactory
{
	static const std::string names[3];

	CustomerFactory() = delete;

	CustomerFactory(CustomerFactory const &) = delete; //we get rid of the copy constructor

	CustomerFactory& operator=(CustomerFactory const &) = delete;	//we get rid of the copy assignation

public:
	static AbstractCustomer *getCustomer(std::string name)
	{
		auto e = std::find(
			std::begin(names),
			std::end(names),
			name
		);

		if(e == std::end(names)){
			return new NullCustomer();
		}

		return new RealCustomer(*e);
	}
};

const std::string CustomerFactory::names[] = {"Rob", "Joe", "Julie"};

int main(int argc, char *argv[])
{
	std::unique_ptr<AbstractCustomer> customer1(CustomerFactory::getCustomer("Rob"));
	std::unique_ptr<AbstractCustomer> customer2(CustomerFactory::getCustomer("Bob"));
	std::unique_ptr<AbstractCustomer> customer3(CustomerFactory::getCustomer("Julie"));
	std::unique_ptr<AbstractCustomer> customer4(CustomerFactory::getCustomer("Laura"));

	std::cout << "Customers" << std::endl;
	std::cout << customer1->getName() << std::endl;
	std::cout << customer2->getName() << std::endl;
	std::cout << customer3->getName() << std::endl;
	std::cout << customer4->getName() << std::endl;

	return 0;
}
