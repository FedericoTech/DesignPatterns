#include <iostream>
#include <list>

class Resource
{
	int value;
public:
	Resource(): value(0){}

	void reset(){value = 0;}

	inline int getValue(){
		return value;
	}

	void setValue(int number){
		value = number;
	}
};

//the ObjectPool is a singleton
class ObjectPool
{
private:
	std::list<Resource *> resources;

	static ObjectPool* instance;

	ObjectPool(){}	//make the constructor private

	void operator = (ObjectPool const&) = delete; //we get rid of the copy constructor

public:
	//method to get the singleton instance
	static ObjectPool* getInstance()
	{
		if(instance == NULL){
			instance = new ObjectPool;
		}

		return instance;
	}

	//the instance with which we get the resource
	Resource* getResource()
	{
		//if there is no resource...
		if(resources.empty()){
			std::cout << "Creating new." << std::endl;
			return new Resource;
		} else {
			std::cout << "Reusing existing." << std::endl;
			Resource* resource = resources.front();
			resources.pop_front();
			return resource;
		}
	}

	//method to return the resource to the pool
	void returnResource(Resource* object){
		object->reset();
		resources.push_back(object);
	}
};

//we initialise the instance
ObjectPool* ObjectPool::instance = 0;

int main(){

	ObjectPool* pool = ObjectPool::getInstance();
	Resource* one;
	Resource* two;

	/* Resources will be created.*/
	one = pool->getResource();
	one->setValue(10);

	std::cout << "one = " << one->getValue() << " [" << one << "]" << std::endl;

	two = pool->getResource();
	two->setValue(20);

	std::cout << "two = " << two->getValue() << " [" << two << "]" << std::endl;

	pool->returnResource(one);
	pool->returnResource(two);

	// now we reuse the resources
	one = pool->getResource();
	std::cout << "one = " << one->getValue() << " [" << one << "]" << std::endl;

	two = pool->getResource();
	std::cout << "two = " << two->getValue() << " [" << two << "]" << std::endl;

	return 0;
}
