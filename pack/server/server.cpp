#include <array>
#include <boost/asio.hpp>

#include <iostream>
#include <string>
#include <thread>
#include <chrono>

#include "Fix.h"
#include "OrderBook.h"

using namespace std;
using boost::asio::ip::tcp;
using namespace Fix4;

const char report = '8'; // represent Execution Report
const int notFound = -2;// represent can't find cancelling order

OrderBook book;
Order send_buffer;

// open server on LAN
boost::asio::io_service io_service;
tcp::acceptor acc(io_service, tcp::endpoint(tcp::v6(), 9876));
boost::system::error_code ignored;

string sendMessage(char type, const Order& order)// create a Fix message 
{
	switch (type)
	{
	case report:
	{
		if (order.status == notFound) return string("35=9;39=8;");
		Fix send;
		//add type
		send.addTag(Type, report);
		//add status
		send.addTag(Status, char(order.status + '0'));
		send.addTag(ExecType, char(order.status + '0'));
		//add side
		send.addTag(Side, order.side);
		//add price
		send.addTag(Price, order.price);
		//add quantity
		send.addTag(LeavesQty, order.quantity);
		//add id
		send.addTag(OrdID, order.id);
		return send.str();
	}
	default:
		return string();
		break;
	}
}

void work(tcp::socket* socketClient)// fill the order if possible
{
	while (1) {
		this_thread::sleep_for(chrono::seconds(1));// too fast is not proper :)
		if (send_buffer.status != -1) {
			cout << "send message\n" + sendMessage(report, send_buffer) << endl;
			boost::asio::write(*socketClient, boost::asio::buffer(sendMessage(report, send_buffer)), ignored);// send message to client
			send_buffer = Order();
		}
		pair<Order, Order> result = book.fill();
		if (result.first.status == -1) continue;
		cout << "send message\n" + sendMessage(report, result.second) << endl;
		boost::asio::write(*socketClient, boost::asio::buffer(sendMessage(report, result.second)), ignored);// send message to client
		cout << "send message\n" + sendMessage(report, result.first) << endl;
		boost::asio::write(*socketClient, boost::asio::buffer(sendMessage(report, result.first)), ignored);// send message to client
	}
}

void monitoring() {
	tcp::socket socketMonitor(io_service);
	acc.accept(socketMonitor);
	while (1) {
		this_thread::sleep_for(chrono::seconds(1));
		boost::asio::write(socketMonitor, boost::asio::buffer(book.show()), ignored);// send message to client
	}
}

int main()
{
	while (1) {
		// get ready to get message
		tcp::socket socketClient(io_service);
		acc.accept(socketClient);
		// fill order thread
		thread orderFilling(work, &socketClient);
		orderFilling.detach();
		// monitor client thread
		thread monitorClient(monitoring);
		monitorClient.detach();
		while (1) {
			array<char, 256> input_buffer;
			size_t input_size = socketClient.read_some(boost::asio::buffer(input_buffer), ignored);//get meesage from client
			string client_message(input_buffer.data(), input_buffer.data() + input_size);// transfer the message to string
			Fix now(client_message);
			switch (now.getTag(Type))
			{
			case 'D':
				book.addNewOrder(Order(now.getPrice(), now.getTag(Side), now.getQuantity(), now.getID()));
				send_buffer = Order(now.getPrice(), now.getTag(Side), now.getQuantity(), now.getID());
				break;
			case 'F':
				send_buffer = book.delOrder(now.getID());
				break;
			default:
				break;
			}
			cout << socketClient.remote_endpoint().address().to_string() + ": " << client_message << endl;
			if (client_message == "quit") break;
			if (client_message == "") break;
			cout << book;
		}

		socketClient.shutdown(tcp::socket::shutdown_both, ignored);
		socketClient.close();
	}
	return 0;
}
