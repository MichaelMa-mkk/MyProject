#pragma once
#include <vector>
#include <iostream>
#include <string>
using namespace std;

struct Order
{
	double price;
	char side;
	int status, quantity;
	string id;
	Order() :status(-1) {}// represent null
	Order(double price, char side, int quantity, string id, int status = 0)
		:price(price), side(side), quantity(quantity), id(id), status(status) {}
	bool operator < (const Order & x) const {
		return price == x.price ? (quantity < x.quantity) : price < x.price;
	}
};
ostream & operator << (ostream & os, const Order & order);

class OrderBook
{
public:
	OrderBook();
	~OrderBook();
	bool addNewOrder(Order now);
	Order delOrder(string id);
	void update(Order now);
	pair<Order, Order> fill();
	int getBuySize()const;
	int getSellSize()const;
	friend ostream& operator << (ostream& os, const OrderBook & book);

private:
	vector<Order> buy_order, sell_order;

};

