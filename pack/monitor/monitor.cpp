#include <array>
#include <boost/array.hpp>
#include <boost/asio.hpp>

#include <iostream>
#include <string>

using boost::asio::ip::tcp;

int main() {
	// get ready to connect server
	boost::asio::io_service io_service;
	tcp::resolver resolver(io_service);
	tcp::resolver::query query("10.154.40.68", "9876");
	tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
	boost::system::error_code error;
	tcp::socket socket(io_service);
	boost::asio::connect(socket, endpoint_iterator);

	while (1) {
		std::array<char, 256> input_buffer;
		size_t rsize = socket.read_some(boost::asio::buffer(input_buffer), error);// get message from server
		std::cout << std::string(input_buffer.data(), input_buffer.data() + rsize);
	}
}