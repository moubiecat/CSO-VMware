#include <print>
#include <magic_args/magic_args.hpp>
#include "cli.h"
#include "client.h"

int main(int argc, char** argv) {
	//
	// Parse command-line arguments
	//
	const auto args = magic_args::parse<cli::cmd_args>(argc, argv);
	//
	// Create a server instance listening on localhost:8080
	//
	cat::client client(args->host, args->port);
	std::println("- Client listening on {}", client.ipaddress().c_str());
	//
	// Connect the server
	//
	client.connect();
	std::println("- Client connected");
	//
	// Main server loop
	//
	while (cat::is_connect()) {
		//
		// Poll for incoming events
		//
		client.flush();
	}
	//
	// Disconnect the server
	//
	client.disconnect();
	std::println("- Client disconnected\n");
	return 0;
}