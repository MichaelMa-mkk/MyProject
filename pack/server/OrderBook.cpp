#include "OrderBook.h"
#include <vector>
#include <algorithm>


OrderBook::OrderBook()
{
}


OrderBook::~OrderBook()
{
}

bool OrderBook::addNewOrder(Order now)// add a new order to order_list
{
	if (now.side == '1') {
		auto it = upper_bound(buy_order.begin(), buy_order.end(), now);
		buy_order.insert(it, now);
	}
	if (now.side == '2') {
		auto it = upper_bound(sell_order.begin(), sell_order.end(), now);
		sell_order.insert(it, now);
	}
	return false;
}

ostream & operator << (ostream& os, const Order & order) {
	return os << "price: " << order.price << endl << "side: " << order.side << endl << "status: " << order.status << endl;
}

ostream & operator<< (ostream & os, const OrderBook & book)
{
	for (auto x : book.buy_order) {
		os << x << endl;
	}
	for (auto x : book.sell_order) {
		os << x << endl;
	}
	return os;
}
