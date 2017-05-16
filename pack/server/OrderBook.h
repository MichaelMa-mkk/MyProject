#pragma once
#include <vector>
#include <iostream>
using namespace std;

struct Order
{
	double price;
	char side;
	Order() {};
	Order(double price_, char side_) :price(price_), side(side_) {}
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

