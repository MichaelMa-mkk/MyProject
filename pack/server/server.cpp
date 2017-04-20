#include <array>
#include <iostream>
#include <string>

#include <boost/asio.hpp>

using namespace std;
using boost::asio::ip::tcp;

int main()
{
	boost::asio::io_service io_service;
	tcp::acceptor acc(io_service, tcp::endpoint(tcp::v6(), 9876));

	while (1) {
		boost::system::error_code ignored;

		tcp::socket socket(io_service);
		acc.accept(socket);
		while (1) {
			std::array<char, 256> input_buffer;
			std::size_t input_size = socket.read_some(
				boost::asio::buffer(input_buffer),
				ignored);
			std::string client_message(input_buffer.data(),
				input_buffer.data() + input_size);

			cout << socket.remote_endpoint().address().to_string() + ": "
				<< client_message << endl;

			std::string my_message;
			cout << "> ";
			getline(cin, my_message);
			boost::asio::write(socket, boost::asio::buffer(my_message), ignored);
		}

		socket.shutdown(tcp::socket::shutdown_both, ignored);
		socket.close();
	}
	return 0;
}
