#include <iostream>

//Step 1

struct BusinessService
{
	virtual void doProcessing() = 0;
	virtual ~BusinessService() = 0;
	virtual std::string getName() = 0;
};
BusinessService::~BusinessService(){};

//Step 2
class EJBService: public BusinessService
{
	void doProcessing() override {
		//Enterprise Java Bean
		std::cout << "Processing task by invoking EJB Service" << std::endl;
	}

	std::string getName(){
		return std::move("EJB");
	}
};

class JMSService: public BusinessService
{
	void doProcessing() override {
		//Java Messaging Services
		std::cout << "Processing task by invoking JMS Service" << std::endl;
	}

	std::string getName(){
		return std::move("JMS");
	}
};

//Step 3
class BusinessLookUp
{
public:
	BusinessService *getBusinessService(std::string serviceType)
	{
		if(serviceType.compare("EJB") == 0){
			return new EJBService;
		} else {
			return new JMSService;
		}
	}
};

//Step 4
class BusinessDelegate
{
	BusinessLookUp lookupService;
	BusinessService *businessService = nullptr;
	std::string serviceType;

public:
	void setServiceType(std::string serviceType)
	{
		this->serviceType = serviceType;
	}

	void doTask()
	{
		if(businessService == nullptr || businessService->getName() != serviceType){
			delete businessService;

			businessService = lookupService.getBusinessService(serviceType);
		}

		businessService->doProcessing();
	}

	~BusinessDelegate()
	{
		delete businessService;
	}
};

//Step 5, it might be like a Java Server Pages, servlet or a java UI
class Client
{
	BusinessDelegate &businessService;

public:
	Client(BusinessDelegate &businessService):businessService(businessService){};

	void doTask()
	{
		businessService.doTask();
	}
};

//Step 6
int main(int argc, char **argv)
{
	BusinessDelegate businessDelegate;
	businessDelegate.setServiceType("EJB");

	Client client(businessDelegate);
	client.doTask();
	client.doTask();

	businessDelegate.setServiceType("JMS");
	client.doTask();
	client.doTask();

	businessDelegate.setServiceType("EJB");
	client.doTask();

	return 0;
}
