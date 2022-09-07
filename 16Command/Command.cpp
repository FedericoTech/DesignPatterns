#include <iostream>
#include <list>

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
	Stock * abcStock;
public:
	BuyStock(Stock * abcStock):abcStock(abcStock){};

	void execute()
	{
		abcStock->buy();
	}
};

class SellStock: public Order {
	Stock * abcStock;
public:
	SellStock(Stock *abcStock):abcStock(abcStock){};

	void execute(){
		abcStock->sell();
	}
};

//Step 4
class Broker
{
	std::list<Order *> orderList;

public:
	void takeOrder(Order *order){
		orderList.push_back(order);
	}

	void placeOrders()
	{
		for(Order *order : orderList){
			order->execute();
		}

		orderList.clear();
	}
};


//Step 5
int main()
{
	Stock * abcStok = new Stock;

	BuyStock *buyStockOrder = new BuyStock(abcStok);

	SellStock *sellStockOrder = new SellStock(abcStok);

	Broker broker;
	broker.takeOrder(buyStockOrder);
	broker.takeOrder(sellStockOrder);

	broker.placeOrders();

	return 0;
}
