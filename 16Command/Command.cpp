#include <iostream>
#include <list>
#include <memory>

//Step 1
struct Order {
	virtual void execute() = 0;
	virtual ~Order() = 0;
};

Order::~Order(){}

//Step 2
class Stock {
	std::string name = "ABC";
	int quantity = 10;

public:
	void buy()
	{
		std::cout << "Stock [ Name: " << name
			<< ", Quantity: " << quantity
			<< " ] bought" << std::endl;
	}

	void sell()
	{
		std::cout << "Stock [ Name: " << name
					<< ", Quantity: " << quantity
					<< " ] sold" << std::endl;
	}
};

//Step 3
class BuyStock: public Order{
	std::shared_ptr<Stock> abcStock;
public:
	BuyStock(std::shared_ptr<Stock> abcStock):abcStock(abcStock){};

	void execute()
	{
		abcStock->buy();
	}
};

class SellStock: public Order {
	std::shared_ptr<Stock> abcStock;
public:
	SellStock(std::shared_ptr<Stock> abcStock):abcStock(abcStock){};

	void execute(){
		abcStock->sell();
	}
};

//Step 4
class Broker
{
	std::list<std::shared_ptr<Order>> orderList;

public:
	void takeOrder(std::shared_ptr<Order> order){
		orderList.push_back(order);
	}

	void placeOrders()
	{
		for(auto order : orderList){
			order->execute();
		}

		orderList.clear();
	}
};


//Step 5
int main()
{
	std::shared_ptr<Stock> abcStok = std::make_shared<Stock>();

	std::shared_ptr<BuyStock> buyStockOrder = std::make_shared<BuyStock>(abcStok);

	std::shared_ptr<SellStock> sellStockOrder = std::make_shared<SellStock>(abcStok);

	Broker broker;
	broker.takeOrder(buyStockOrder);
	broker.takeOrder(sellStockOrder);

	broker.placeOrders();

	return 0;
}
