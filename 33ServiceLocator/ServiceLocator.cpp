#include <iostream>
#include <list>
#include <algorithm>

//Step 1
struct Service
{
	virtual std::string getName() = 0;
	virtual void execute() = 0;
	virtual ~Service() = 0;
};
Service::~Service(){};

//Step 2
class Service1: public Service
{
	void execute() override
	{
		std::cout << "Executing Service 1" << std::endl;
	}

	std::string getName() override
	{
		return "Service1";
	}
};

class Service2: public Service
{
	void execute() override
	{
		std::cout << "Executing Service 2" << std::endl;
	}

	std::string getName() override
	{
		return "Service2";
	}
};

//Step 3
class InitialContext
{
public:
	Service *lookUp(std::string jndiName)
	{
		if(jndiName.compare("Service1") == 0){
			std::cout << "Looking up and creating a new Service 1 object" << std::endl;
			return new Service1;
		}
		else if(jndiName.compare("Service2") == 0){
			std::cout << "Looking up and creating a new Service 2 object" << std::endl;
			return new Service2;
		}

		return nullptr;
	}
};

//Step 4
class Cache
{
	std::list<Service *> services;
public:
	Service *getService(std::string serviceName)
	{
		for(Service *service: services){
			if(service->getName().compare(serviceName) == 0){
				std::cout << "Returning cached " << serviceName << " object" << std::endl;
				return service;
			}

		}

		return nullptr;
	}

	void addService(Service *newService)
	{

		if(
			std::find_if(
				services.begin(),
				services.end(),
				[=](Service *p){
					return newService->getName().compare(p->getName()) == 0;
				}
			) == std::end(services)
		) {
			services.push_back(newService);
		}

		/*
		if(
			std::find(
				services.begin(),
				services.end(),
				newService
			) == std::end(services)
		) {
			services.push_back(newService);
		}
		*/
	}
};

//Step 5
class ServiceLocator
{
	static Cache cache;
public:
	static Service *getService(std::string jndiName){
		Service *service = cache.getService(jndiName);

		if(service != nullptr){
			return service;
		}

		InitialContext context;
		Service *service1 = static_cast<Service *>(context.lookUp(jndiName));
		cache.addService(service1);

		return service1;
	}
};

Cache ServiceLocator::cache; //to init this static object

//Step 6
int main(int argc, char *argv[])
{
	Service *service = ServiceLocator::getService("Service1");
	service->execute();

	service = ServiceLocator::getService("Service2");
	service->execute();

	service = ServiceLocator::getService("Service1");
	service->execute();

	service = ServiceLocator::getService("Service2");
	service->execute();

	return 0;
}
