#include <iostream>
#include <memory>
#include <list>

class Resource
{
	int value;
public:
	Resource(): value(0){}

	void reset(){value = 0;}

	inline int getValue() const
	{
		return value;
	}

	void setValue(int number){
		value = number;
	}
};

//the ObjectPool is a singleton
class ObjectPool
{
	std::list<Resource *> resources;

	static std::shared_ptr<ObjectPool> instance;

	ObjectPool() = default;	//make the constructor private

	ObjectPool(ObjectPool const &) = delete; //we get rid of the copy constructor

	ObjectPool& operator=(ObjectPool const &) = delete;	//we get rid of the copy assignation

public:

	//method to get the singleton instance
	static std::shared_ptr<ObjectPool> getInstance()
	{
		if(instance == nullptr){
			instance = std::move(std::shared_ptr<ObjectPool>(new ObjectPool));
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

	~ObjectPool()
	{
		for(Resource *r: resources)
		{
			delete r;
		}
	}
};

//we initialise the inner instance
std::shared_ptr<ObjectPool> ObjectPool::instance = nullptr;

int main()
{
	std::shared_ptr<ObjectPool> pool = ObjectPool::getInstance();
	std::shared_ptr<ObjectPool> pool2 = ObjectPool::getInstance();

	std::cout << "is pool == pool2 ? " << (pool == pool2) << std::endl;
	std::cout << "pool has " << pool.use_count() << " elements " << std::endl;

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
