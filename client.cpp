#include <boost/asio.hpp>
#include <iostream>

using namespace boost;

void writeToSocket(asio::ip::tcp::socket& sock) 
{
	// Step 2. Allocating and filling the buffer.
	std::string buf = "1";
	std::size_t total_bytes_written = 0;
	
	// Step 3. Run the loop until all data is written
	// to the socket.
	while (total_bytes_written != buf.length()) {
		total_bytes_written += sock.write_some(
		asio::buffer(buf.c_str() +
		total_bytes_written,
		buf.length() - total_bytes_written));
	}
}

int main()
{
	std::string raw_ip_address = "192.168.1.6"; // Please change to your ESP8266 IP Address.
	
	unsigned short port_num = 4551; // Please change too your ESP8600 port.
	
	try {
		asio::ip::tcp::endpoint
		ep(asio::ip::address::from_string(raw_ip_address),
		port_num);
		asio::io_service ios;
		// Step 1. Allocating and opening the socket.
		asio::ip::tcp::socket sock(ios, ep.protocol());
		sock.connect(ep);
		writeToSocket(sock);
	}
	catch (system::system_error &e) {
		std::cout << "Error occured! Error code = " << e.code()
		<< ". Message: " << e.what();
		return e.code().value();
	}
	return 0;
}