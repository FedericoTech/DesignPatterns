#include<iostream>
#include<list>

//Step 1
struct Filter
{
	virtual void execute(std::string) = 0;
	virtual ~Filter() = 0;
};
Filter::~Filter(){};

//Step 2
class AuthenticationFilter: public Filter
{
	void execute(std::string request)
	{
		std::cout << "Authenticating request: " << request << std::endl;
	}
};

class DebugFilter: public Filter
{
	void execute(std::string request)
	{
		std::cout << "request log: " << request << std::endl;
	}
};

//Step 3
class Target
{
public:
	void execute(std::string request)
	{
		std::cout << "Executing request: " << request << std::endl;
	}
};

//Step 4
class FilterChain
{
	std::list<Filter *> filters;
	Target *target = nullptr;
public:
	void addFilter(Filter *filter)
	{
		filters.push_back(filter);
	}

	void execute(std::string request)
	{
		for(auto filter : filters){
			filter->execute(request);
		}

		target->execute(request);
	}

	void setTarget(Target *target)
	{
		delete this->target;
		this->target = target;
	}

	~FilterChain()
	{
		for(Filter * f : filters){
			delete f;
		}

		delete target;

	}
};

//Step 5
class FilterManager
{
	FilterChain filterChain;

public:
	FilterManager(Target *target)
	{
		filterChain.setTarget(target);
	}

	void setFilter(Filter *filter)
	{
		filterChain.addFilter(filter);
	}

	void filterRequest(std::string request)
	{
		filterChain.execute(request);
	}
};

//Step 6
class Client
{
	FilterManager *filterManager;

public:
	void setFilterManager(FilterManager &filterManager)
	{
		this->filterManager = &filterManager;
	}

	void setRequest(std::string request)
	{
		filterManager->filterRequest(request);
	}
};

//Step 7
int main(int argc, char *argv[])
{
	FilterManager filterManager(new Target);

	filterManager.setFilter(new AuthenticationFilter);
	filterManager.setFilter(new DebugFilter);

	Client client;
	client.setFilterManager(filterManager);
	client.setRequest("HOME");

	return 0;
}
