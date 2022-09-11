#include <iostream>
#include <array>

//Step 1
class DependentObject1
{
	std::string data;

public:
	void setData(std::string data)
	{
		this->data = data;
	}

	std::string getData()
	{
		return data;
	}
};

class DependentObject2
{
	std::string data;

public:
	void setData(std::string data)
	{
		this->data = data;
	}

	std::string getData()
	{
		return data;
	}
};

//Step 2
class CoarseGrainedObject
{
	DependentObject1 do1;
	DependentObject2 do2;

public:
	void setData(std::string data1, std::string data2)
	{
		do1.setData(data1);
		do2.setData(data2);
	}

	std::array<std::string, 2> getData()
	{
		return std::array<std::string, 2>{do1.getData(), do2.getData()};
	}
};

//Step 3
class CompositeEntity
{
	CoarseGrainedObject cgo;

public:
	void setData(std::string data1, std::string data2)
	{
		cgo.setData(data1, data2);
	}

	std::array<std::string, 2> getData()
	{
		return cgo.getData();
	}
};

//Step 4
class Client
{
	CompositeEntity compositeEntity;

public:
	void printData()
	{
		for(std::string data : compositeEntity.getData()){
			std::cout << "Data: " << data << std::endl;
		}
	}

	void setData(std::string data1, std::string data2)
	{
		compositeEntity.setData(data1, data2);
	}
};

//Step 5
int main(int argc, char *argv[])
{
	Client client;

	client.setData("Test", "Data");
	client.printData();

	client.setData("Second Test", "Data1");
	client.printData();

	return 0;
}
