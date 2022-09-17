#include <iostream>
#include <algorithm>

//Step 1
//we create the abstract iterator template
template<typename T>
struct Iterator {
	virtual bool hasNext() = 0;
	virtual T* next() = 0;
	virtual ~Iterator() = 0;
};

template<typename T>
Iterator<T>::~Iterator(){};

//we declare the container template
template<typename T, std::size_t N>
struct Container {
	T data[N];

	//we create an inner implementation of the iterator
	template<class U>
	class  ContainerIterator : public Iterator<U> {
		int index = 0;
		Container<U, N> &parent;

		bool hasNext()
		{
			return index < std::end(parent.data) - std::begin(parent.data);
		}

		U* next()
		{
			if(hasNext()){
				return &parent.data[index++];
			}

			return nullptr;
		}

	public:
		ContainerIterator(Container<U, N> &parent): parent(parent) {}
	};

	Iterator<T> *getIterator()
	{
		return new ContainerIterator<T>(*this);
	}
};

//Step 2
//now we create a couple implementations of container

class NameRepository: public Container<std::string, 4>
{
public:
	NameRepository(){
		data[0] = "Robert";
		data[1] = "John";
		data[2] = "Julie";
		data[3] = "Lora";
	}
};

class NumberRepository: public Container<int, 7>
{
public:
	NumberRepository(){
		data[0] = 30;
		data[1] = 23;
		data[2] = 78;
		data[3] = 1;
		data[4] = -45;
		data[5] = -3;
		data[6] = 16;
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

	std::cout << std::endl << std::endl;

	NumberRepository numbersRespository;

	for(Iterator<int> *iter = numbersRespository.getIterator(); iter->hasNext();){
		int num = *iter->next();
		std::cout << "Number : " << num << std::endl;
	}

	return 0;
}
