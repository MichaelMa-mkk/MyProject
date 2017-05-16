#pragma once
#include <vector>
#include <iostream>
using namespace std;

struct Order
{
	double price;
	char side;
	int status;
	Order() {};
	Order(double price, char side, int status = 0) :price(price), side(side), status(status) {}
	bool operator < (const Order & x) const {
		return price < x.price;
	}
};

class OrderBook
{
public:
	OrderBook();
	~OrderBook();
	bool addNewOrder(Order now);
	friend ostream& operator << (ostream& os, const OrderBook & book);

private:
	vector<Order> buy_order, sell_order;

};

