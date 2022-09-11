#include <iostream>

//Step 1

class HomeView
{
public:
	void show()
	{
		std::cout << "Displaying Home Page" << std::endl;
	}
};

class StudentView
{
public:
	void show()
	{
		std::cout << "Displaying Student Page" << std::endl;
	}
};

//Step 2
class Dispatcher
{
	StudentView studentView;
	HomeView homeView;

public:
	void dispatch(std::string request)
	{
		if(request.compare("STUDENT") == 0){
			studentView.show();
		} else {
			homeView.show();
		}
	}
};

//Step 3
class FrontController
{
	Dispatcher dispatcher;

	bool isAuthenticUser()
	{
		std::cout << "User is authenticated successfully" << std::endl;
		return true;
	}

	void trackRequest(std::string request)
	{
		std::cout << "Page requested: " << request << std::endl;
	}

public:
	void dispatchRequest(std::string request)
	{
		//log each request
		trackRequest(request);

		//Authenticate the user
		if(isAuthenticUser()){
			dispatcher.dispatch(request);
		}
	}
};

//Step 4
int main(int argc, char *argv[]){
	FrontController frontController;

	frontController.dispatchRequest("HOME");
	frontController.dispatchRequest("STUDENT");

	return 0;
}
