#include <array>
#include <iostream>
#include <string>
#include "Fix.h"
#include "OrderBook.h"
#include <boost/asio.hpp>

using namespace std;
using boost::asio::ip::tcp;
using namespace Fix4;

int main()
{
	boost::asio::io_service io_service;
	tcp::acceptor acc(io_service, tcp::endpoint(tcp::v6(), 9876));
	// open server on LAN
	OrderBook book;
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
				book.addNewOrder(Order(now.getPrice(),now.getTag(Side)));
				break;
			default:
				break;
			}
			cout << socket.remote_endpoint().address().to_string() + ": " << client_message << endl;
			cout << book;

			string my_message;
			cout << "> ";
			getline(cin, my_message);
			boost::asio::write(socket, boost::asio::buffer(my_message), ignored);
		}

		socket.shutdown(tcp::socket::shutdown_both, ignored);
		socket.close();
	}
	return 0;
}
