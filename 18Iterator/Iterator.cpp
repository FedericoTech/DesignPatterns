#include <iostream>
#include <algorithm>

//Step 1

template<typename T>
struct Iterator {
	virtual bool hasNext() = 0;
	virtual T* next() = 0;
	virtual ~Iterator() = 0;
};

template<typename T>
Iterator<T>::~Iterator(){};

template<typename T>
struct Container {
	virtual Iterator<T> *getIterator() = 0;
	virtual ~Container() = 0;
};

template<typename T>
Container<T>::~Container(){};

//Step 2
class NameRepository: public Container<std::string>
{
public:
	std::string names[4] = {"Robert", "John", "Julie", "Lora"};

	class NameIterator: public Iterator<std::string>
	{
		int index = 0;
		NameRepository &parent;
	public:

		NameIterator(NameRepository &parent):parent(parent){};

		bool hasNext()
		{
			return index < std::end(parent.names) - std::begin(parent.names);
		}

		std::string* next()
		{
			if(hasNext()){
				return &parent.names[index++];
			}

			return nullptr;
		}
	};

	Iterator<std::string> *getIterator()
	{
		return new NameIterator(*this);
	}
};

//Step 3
int main()
{
	NameRepository namesRespository;

	for(Iterator<std::string> *iter = namesRespository.getIterator(); iter->hasNext();){
		std::string *name = iter->next();
		std::cout << "Name : " << *name << std::endl;
	}

	return 0;
}
