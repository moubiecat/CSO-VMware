#include <print>
#include <magic_args/magic_args.hpp>
#include "cli.h"
#include "server.h"

int main(int argc, char* argv[]) {
	//
	// Parse command-line arguments
	//
	const auto args = magic_args::parse<cli::cmd_args>(argc, argv);
	//
	// Create a server instance listening on localhost:8080
	//
	cat::server srv(args->host, args->port);
	std::println("- Server listening on {}", srv.ipaddress().c_str());
	//
	// Connect the server
	//
	srv.connect();
	std::println("- Server connected");
	//
	// Main server loop
	//
	while (cat::is_connect()) {
		//
		// Poll for incoming events
		//
		srv.poll();
	}
	//
	// Disconnect the server
	//
	srv.disconnect();
	std::println("- Server disconnected\n");
	return 0;
}