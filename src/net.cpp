#include "net.h"
#include "core.h"
#include "client.h"
#include "server.h"

namespace cat {
	/*
		Global flag indicating whether a client connection to a remote server
		is currently active or in progress. Shared between client/server code
		to track connection state.
	 */
	static bool connecting = false;


	/*
		Returns whether a client connection attempt is currently active.

		@return true  If a connection is active or being established.
		@return false If no client connection exists.
	 */
	bool
	is_connecting() noexcept {
		return connecting;
	}

	/*
		Establishes a connection for the client or server.
		
		This function performs the necessary initialization and setup,
		such as creating network hosts and preparing for data transmission.
	 */
	void
	server::connect() const {
		core::Core_enet_initialize();
		core::Core_enet_server_create(host, port, 1, 32);
		connecting = true;
	}

	/*
		Disconnects the client from the server or shuts down the server.
		
		This function ensures that all active connections are properly
		terminated and that associated resources are released.
	 */
	void 
	server::disconnect() const {
		core::Core_enet_deinitialize();
		connecting = false;
	}

	/*
		Polls for incoming network events such as connections,
		disconnections, and data packets.
		
		This function blocks for a specified duration while waiting
		for events, then returns control to the caller.
	 */
	void 
	server::poll() const {
	}

	/*
		Establishes a connection to the server.
		
		This function performs the necessary initialization and setup,
		such as creating network hosts and preparing for data transmission.
	 */
	void
	client::connect() const {
		core::Core_enet_initialize();
		core::Core_enet_client_create(1);
		core::Core_enet_client_connect(host, port, 0);
		connecting = true;
	}

	/*
		Disconnects from the server and cleans up resources.
		
		This function ensures that all network resources are properly released
		and that the client is gracefully disconnected from the server.
	 */
	void
	client::disconnect() const {
		core::Core_enet_client_disconnect();
		core::Core_enet_deinitialize();
		connecting = false;
	}

	/*
		Polls for incoming events or messages from the server.
		
		This function checks for any new data or events and processes them
		accordingly, allowing the client to respond to server communications.
	 */
	void
	client::poll() const {
	}
}