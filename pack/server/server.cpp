#include <array>
#include <boost/asio.hpp>

#include <iostream>
#include <string>

#include "Fix.h"
#include "OrderBook.h"

using namespace std;
using boost::asio::ip::tcp;
using namespace Fix4;

const char report = '8'; // represent Execution Report
const char new_status = '0';// represent New in tag OrdStatus

OrderBook book;

string sendMessage(char type, char status)// create a Fix message 
{
	switch (type)
	{
	case report:
	{
		Fix send;
		send.addTag(Type, report);
		//add type
		send.addTag(Status, status);
		send.addTag(ExecType, status);
		//add status
		//add time
		return send.str();
	}
	default:
		break;
	}
}

int main()
{
	boost::asio::io_service io_service;
	tcp::acceptor acc(io_service, tcp::endpoint(tcp::v6(), 9876));
	// open server on LAN
	while (1) {
		boost::system::error_code ignored;
		tcp::socket socket(io_service);
		acc.accept(socket);
		// get ready to get message
		while (1) {
			array<char, 256> input_buffer;
			size_t input_size = socket.read_some(boost::asio::buffer(input_buffer), ignored);//get meesage from client
			string client_message(input_buffer.data(), input_buffer.data() + input_size);// transfer the message to string
			Fix now(client_message);
			switch (now.getTag(Type))
			{
			case 'D':
				book.addNewOrder(Order(now.getPrice(), now.getTag(Side)));
				boost::asio::write(socket, boost::asio::buffer(sendMessage(report, new_status)), ignored);// send message to client
				break;
			default:
				break;
			}
			cout << socket.remote_endpoint().address().to_string() + ": " << client_message << endl;
			if (client_message == "") break;
			cout << book;
		}

		socket.shutdown(tcp::socket::shutdown_both, ignored);
		socket.close();
	}
	return 0;
}
