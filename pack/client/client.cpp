#include <array>
#include <boost/array.hpp>
#include <boost/asio.hpp>

#include <iostream>
#include <string>
#include <sstream>

#include "Fix.h"
#include "OrderBook.h"

using boost::asio::ip::tcp;
using namespace std;
using namespace Fix4;

const char add_new = 'D';// represent Order-Single
const char new_status = '0';// represent New in tag OrdStatus

OrderBook book;

void Error(const string & s) {
	throw runtime_error(s);
}

string String(int x) {// transfer a int to a string
	stringstream ss;
	ss << x;
	string ans;
	ss >> ans;
	return ans;
}

void menu() {// print operating menu
	cout << "0: quit\n1: add a order\n2: show all the orders in client\n";
}

int checkInt(const string & my_message, int low, int high) { // check if input is avaliable
	stringstream ss;
	ss << my_message;
	int n;
	ss >> n;
	string temp;// save redundant words
	ss >> temp;
	if (my_message[0] < '0' || my_message[0] > '9') Error("Illegal integer format. Try again.");
	if (temp.size()) Error("Illegal integer format. Try again.");
	if (n < low || n > high) Error("N must be " + String(low) + " to " + String(high) + ".");
	return n;
}

double Double(const string & s) {// transfer a string to a double
	stringstream ss;
	ss << s;
	double ans;
	ss >> ans;
	string temp;// save redundant words
	ss >> temp;
	if (s[0] < '0' || s[0] > '9') Error("Illegal integer format. Try again.");
	if (temp.size()) Error("Illegal integer format. Try again.");
	return ans;
}

string sendMessage(char type)// create a Fix message 
{
	switch (type)
	{
	case add_new:
	{
		Fix send;
		send.addTag(Type, add_new);
		// get type
		//get id
		cout << "please enter the side\n1 for buy; 2 for sell" << endl;
		string input;
		cout << "> ";
		getline(cin, input);
		int side = checkInt(input, 1, 2);
		send.addTag(Side, char(side + '0'));
		//get side
		cout << "please enter the price" << endl;
		cout << "> ";
		getline(cin, input);
		double price = Double(input);
		send.addTag(Price, price);
		//get price
		//get time
		book.addNewOrder(Order(price, char(side + '0')));
		return send.str();
	}
	default:
		break;
	}
}

int main(int argc, char* argv[])
{
	boost::asio::io_service io_service;
	tcp::resolver resolver(io_service);
	tcp::resolver::query query("192.168.0.106", "9876");
	tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
	tcp::socket socket(io_service);
	boost::asio::connect(socket, endpoint_iterator);
	boost::system::error_code error;
	// get connected with server
	while (1)
		try {
		menu();
		string input;
		cout << "> ";
		getline(cin, input);
		// get input
		int n = checkInt(input, 0, 2);
		if (n == 0) break;
		switch (n)
		{
		case 1:
		{
			boost::asio::write(socket, boost::asio::buffer(sendMessage(add_new) + "\n"), error);// send message to server
			break;
		}
		case 2:
			cout << book;
			continue;
		default:
			break;
		}
		array<char, 256> input_buffer;
		size_t rsize = socket.read_some(boost::asio::buffer(input_buffer), error);// get message from server
		Fix receive(string(input_buffer.data(), input_buffer.data() + rsize));
	}
	catch (exception& e) {
		cerr << e.what() << "\n";
	}
	catch (...) {
		cerr << "other errors" << "\n";
	}
	return 0;
}
