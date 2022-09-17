#include <iostream>
#include <algorithm>
#include<type_traits>

//Step 1
//we create the abstract iterator template
template<typename T>
struct Iterator {
	virtual bool hasNext() const = 0;	//for both const and non-const
	virtual T* next() = 0;	//next non-const
	virtual const T* next() const = 0; //next const
	virtual ~Iterator() = 0;
};

template<typename T>
Iterator<T>::~Iterator(){};

//we declare the container template
template<typename T, std::size_t N>
struct Container {


	//we create an inner implementation of the iterator
	template<class U>
	class  ContainerIterator : public Iterator<U> {
		mutable int index = 0;

		const Container<U, N> &parent;

		bool hasNext() const
		{
			return index < std::end(parent.data) - std::begin(parent.data);
		}

		U* next()
		{
			if(hasNext()){
				return const_cast<U*>(&parent.data[index++]);
			}

			return nullptr;
		}

		const U* next() const
		{
			if(hasNext()){
				return &parent.data[index++];
			}

			return nullptr;
		}

	public:
		//ContainerIterator(Container<U, N> &parent): parent(parent) {}
		ContainerIterator(const Container<U, N> &parent): parent(parent) {}
	};

	Container() = default;

	//Initialiser list constructor.
	Container(std::initializer_list<T> list)
	{
		size_t size = list.size();
		//if the list has less elements
		if(size <= N){
			//we copy up to it gets
			std::copy(
				list.begin(), list.end(), //from the beginning to the end of the list
				std::begin(data)
			);
		//if the list has the same number or more than the container...
		} else {
			//we copy up to the max
			std::copy(
				list.begin(), list.begin() + N, //from the beginning to the beginning plus the max.
				std::begin(data)
			);
		}
	};

	Iterator<T> *getIterator()
	{
		return new ContainerIterator<T>(*this);
	}

	const Iterator<T> *getIterator() const
	{
		return new ContainerIterator<T>(*this);
	}

	//Getter
	const T &operator[](size_t index) const {
		return data[index];
	}

	//Setter
	T &operator[](size_t index) {
		return data[index];
	}

	size_t size() const {
		return N;
	}

protected:
	T data[N];
};

//Step 2
//we can do this kind of initialisation

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
	const Container<int, 4> c  = {1,2,3,4};

	//c[1] = 50; //it wouldn't compile as it's const

	for(const Iterator<int> *iter = c.getIterator(); iter->hasNext();){
		int num = *iter->next();
		std::cout << "Number : " << num << std::endl;
	}

	std::cout << std::endl << std::endl;

	Container<std::string, 4>  c2 {{"Robert", "John", "Julie", "Lora"}};

	c2[1] = "changed <-";
	std::cout << c2[1] << std::endl << std::endl;

	for(Iterator<std::string> *iter = c2.getIterator(); iter->hasNext();){
		std::string name  = *iter->next();
		std::cout << "Name : " << name << std::endl;
	}

	std::cout << std::endl << std::endl;

	NameRepository namesRespository;

	for(Iterator<std::string> *iter = namesRespository.getIterator(); iter->hasNext();){
		std::string name = *iter->next();
		std::cout << "Name : " << name << std::endl;
	}

	std::cout << std::endl << std::endl;

	NumberRepository numbersRespository;

	for(Iterator<int> *iter = numbersRespository.getIterator(); iter->hasNext();){
		int num = *iter->next();
		std::cout << "Number : " << num << std::endl;
	}

	return 0;
}
