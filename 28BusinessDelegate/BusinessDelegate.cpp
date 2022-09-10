#include <iostream>

//Step 1

struct BusinessService
{
	virtual void doProcessing() = 0;
	virtual ~BusinessService() = 0;
};
BusinessService::~BusinessService(){};

//Step 2
class EJBService: public BusinessService
{
	void doProcessing() override {
		std::cout << "Processing task by invoking EJB Service" << std::endl;
	}
};

class JMSService: public BusinessService
{
	void doProcessing() override {
		std::cout << "Processing task by invoking JMS Service" << std::endl;
	}
};

//Step 3
class BusinessLookUp
{
public:
	BusinessService *getBusinessService(std::string serviceType){
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
	BusinessService *businessService;
	std::string serviceType;

public:
	void setServiceType(std::string serviceType)
	{
		this->serviceType = serviceType;
	}

	void doTask()
	{
		businessService = lookupService.getBusinessService(serviceType);
		businessService->doProcessing();
	}
};

//Step 5
class Client
{
	BusinessDelegate *businessService;

public:
	Client(BusinessDelegate *businessService):businessService(businessService){};

	void doTask()
	{
		businessService->doTask();
	}
};

//Step 6
int main(int argc, char **argv)
{
	BusinessDelegate businessDelegate;
	businessDelegate.setServiceType("EJB");

	Client client(&businessDelegate);
	client.doTask();

	businessDelegate.setServiceType("JMS");
	client.doTask();

	return 0;
}
