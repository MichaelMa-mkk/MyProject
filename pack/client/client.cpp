#include <array>
#include <boost/array.hpp>
#include <boost/asio.hpp>

#include <iostream>
#include <string>
#include <sstream>
#include <thread>
#include <ctime>

#include "Fix.h"
#include "OrderBook.h"
#include "transfer.hpp"

using boost::asio::ip::tcp;
using namespace std;
using namespace Fix4;

const char add_new = 'D';// represent Order-Single
const char cancel = 'F';// represent Order Cancel Request

OrderBook book;

// get connected with server
boost::asio::io_service io_service;
tcp::resolver resolver(io_service);
/***************************************************change IP here*******************************************************************/
tcp::resolver::query query("108.179.131.29", "9876");
tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
boost::system::error_code error;

string client_id;

void menu() {// print operating menu
	cout << endl;
	cout << "0: quit\n1: add an order\n2: show all the orders in client\n3: cancel an order\n";
}

string sendMessage(char type)// create a Fix message 
{
	switch (type)
	{
	case add_new:
	{
		Fix send;
		//add type
		send.addTag(Type, add_new);
		//get stock
		//get id
		const time_t t = time(NULL);
		send.addTag(OrdID, String(t) + client_id);
		//get side
		cout << "please enter the side\n1 for buy; 2 for sell" << endl;
		string input;
		cout << "> ";
		getline(cin, input);
		int side = checkInt(input, 1, 2);
		send.addTag(Side, char(side + '0'));
		//get price
		cout << "please enter the price" << endl;
		cout << "> ";
		getline(cin, input);
		double price = Double(input);
		send.addTag(Price, price);
		//get quantity
		cout << "please enter the quantity" << endl;
		cout << "> ";
		getline(cin, input);
		int quantity = checkInt(input, 1, 2000);
		send.addTag(Qty, quantity);
		return send.str();
	}
	case cancel:
	{
		Fix send;
		// add type
		send.addTag(Type, cancel);
		// get id
		cout << "please enter the order id you want to cancel" << endl;
		cout << "> ";
		string input;
		getline(cin, input);
		send.addTag(cancelID, input);
		return send.str();
	}
	default:
		return string();
		break;
	}
}

void keepGetMessage(tcp::socket* socket) {
	while (1) {
		array<char, 256> input_buffer;
		size_t rsize = socket->read_some(boost::asio::buffer(input_buffer), error);// get message from server
		Fix receive(string(input_buffer.data(), input_buffer.data() + rsize));
		switch (receive.getTag(Type))
		{
		case '8':
			switch (receive.getTag(Status)) {
			case '0':// add new
				book.addNewOrder(Order(receive.getPrice(), receive.getTag(Side), receive.getQuantity(), receive.getID(), receive.getTag(Status) - '0'));
				cout << "add new order successfully\n";
				cout << "\n> ";
				break;
			case '1': // order partial fill
				book.update(Order(receive.getPrice(), receive.getTag(Side), receive.getQuantity(), receive.getID(), receive.getTag(Status) - '0'));
				cout << "the order was partially filled" << endl;
				cout << Order(receive.getPrice(), receive.getTag(Side), receive.getQuantity(), receive.getID(), receive.getTag(Status) - '0');
				cout << "\n> ";
				break;
			case '2':// order full fill
				book.update(Order(receive.getPrice(), receive.getTag(Side), receive.getQuantity(), receive.getID(), receive.getTag(Status) - '0'));
				cout << "the order was filled" << endl;
				cout << Order(receive.getPrice(), receive.getTag(Side), receive.getQuantity(), receive.getID(), receive.getTag(Status) - '0');
				cout << "\n> ";
				break;
			case '4':// order cancel
				book.delOrder(receive.getID());
				cout << "the order " + receive.getID() + " has been cancelled successfully\n";
				cout << "\n> ";
				break;
			case '8':
				cout << "the request has been rejected\n";
				cout << "\n> ";
				break;
			default:
				break;
			}
			break;

		case '9': // request rejected
			cout << "the cancel request is rejected\n";
			cout << "\n> ";
			break;
		default:
			break;
		}
	}
}

bool session() {// check if time is in session
	return 1;
	time_t t = time(NULL);
	tm timeinfo;
	localtime_s(&timeinfo, &t);
	if (timeinfo.tm_wday >= 1 && timeinfo.tm_wday <= 5)// Monday to Friday
		if ((timeinfo.tm_hour >= 9 && timeinfo.tm_hour <= 11) || (timeinfo.tm_hour >= 13 && timeinfo.tm_hour <= 16))// 9:00 to 11:00 or 13:00 to 16:00
			return true;
	return false;
}

int main(int argc, char* argv[])
{
	tcp::socket socket(io_service);
	boost::asio::connect(socket, endpoint_iterator);
	// thread to read message from server
	thread ReadMessage(keepGetMessage, &socket);
	ReadMessage.detach();
	while (1)
		try {
		menu();
		string input;
		cout << "\n> ";
		// get input
		getline(cin, input);
		int n = checkInt(input, 0, 3);
		switch (n)
		{
		case 0:
			boost::asio::write(socket, boost::asio::buffer("quit"), error);// send quit message to server
			goto exit;
			break;
		case 1:
			if (session())
				boost::asio::write(socket, boost::asio::buffer(sendMessage(add_new)), error);// send message to server
			else cout << "local time is not in session." << endl;
			break;
		case 2:
			cout << book;
			break;
		case 3:
			if (session())
				boost::asio::write(socket, boost::asio::buffer(sendMessage(cancel)), error);// send message to server
			else cout << "local time is not in session." << endl;
			break;
		default:
			break;
		}
	}
	catch (exception& e) {
		cerr << e.what() << "\n";
	}
	catch (...) {
		cerr << "other errors" << "\n";
	}
exit:
	return 0;
}
