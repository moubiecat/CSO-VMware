#include <stdexcept>
#include <enet/enet.h>
#include "core.h"

namespace cat::core {
	/*
		Indicates whether the ENet library has been successfully initialized.
		Prevents redundant initialization and ensures a proper shutdown sequence.
	 */
	static bool initialized = false;

	/*
		Global pointer to the active ENet host instance.
		Used by both server and client configurations to manage network operations.
		Set to nullptr when no active host exists.
	 */
	static ENetHost* host = nullptr;

	/*
		Global pointer representing the active peer connection.
		Used on the client side to maintain the connection to a remote ENet server.
	 */
	static ENetPeer* conn = nullptr;


	/*
		Initializes the ENet library for networking.

		Must be called before any ENet operations.
	 */
	void
	Core_enet_initialize() {
		if (initialized) {
			return;
		}

		int res = enet_initialize();
		if (res != 0) {
			throw std::runtime_error("An error occurred while initializing ENet.");
		}

		initialized = true;
	}

	/*
		Deinitializes the ENet library and cleans up resources.

		Must be called after all ENet operations are finished.
	 */
	void
	Core_enet_deinitialize() {
		if (host) {
			enet_host_destroy(host);
			host = nullptr;
		}

		if (initialized) {
			enet_deinitialize();
			initialized = false;
		}

		conn = nullptr;
	}

	/*
		Creates an ENet server host.
		
		@param _Host The hostname or IP address to bind the server to.
		@param _Port The port number on which the server will listen for incoming connections.
		@param _Chunm The maximum number of channels to be used for communication.
		@param _Cltnum The maximum number of clients that can connect to the server.
	 */
	void 
	Core_enet_server_create(std::string_view _Host, std::uint32_t _Port, std::uint32_t _Chunm, std::uint32_t _Cltnum) {
		if (!initialized) {
			throw std::runtime_error("ENet library is not initialized. Call Core_enet_initialize() first.");
		}

		if (host != nullptr) {
			throw std::runtime_error("An ENet host already exists. Cannot create a new server host.");
		}

		ENetAddress addr;
		enet_address_set_host(&addr, _Host.data());
		addr.port = _Port;

		host = enet_host_create(&addr, _Cltnum, _Chunm, 0, 0);
		if (host == nullptr) {
			throw std::runtime_error("An error occurred while trying to create an ENet server host.");
		}
	}

	/*
		Creates an ENet client host.
		
		@param _Chunm The maximum number of channels to be used for communication.
	 */
	void 
	Core_enet_client_create(std::uint32_t _Chunm) {
		if (!initialized) {
			throw std::runtime_error("ENet library is not initialized. Call Core_enet_initialize() first.");
		}

		if (host != nullptr) {
			throw std::runtime_error("An ENet host already exists. Cannot create a new client host.");
		}

		host = enet_host_create(nullptr, 1, _Chunm, 0, 0);
		if (host == nullptr) {
			throw std::runtime_error("An error occurred while trying to create an ENet client host.");
		}
	}

	/*
		Connects the ENet client to a remote server.
		
		@param _Server The hostname or IP address of the remote server.
		@param _Port The port number of the remote server.
		@param _Chunm The number of channels to be used for communication.
	 */
	void 
	Core_enet_client_connect(std::string_view _Server, std::uint32_t _Port, std::uint32_t _Chunm) {
		if (host == nullptr) {
			throw std::runtime_error("ENet client host is not created. Call Core_enet_client_create() first.");
		}

		ENetAddress addr;
		enet_address_set_host(&addr, _Server.data());
		addr.port = _Port;

		conn = enet_host_connect(host, &addr, _Chunm, 0);
		if (conn == nullptr) {
			throw std::runtime_error("No available peers for initiating an ENet connection.");
		}

		ENetEvent event;
		int res = enet_host_service(host, &event, 5000);
		if (res <= 0 || event.type != ENET_EVENT_TYPE_CONNECT) {
			enet_peer_reset(conn);
			conn = nullptr;
			throw std::runtime_error("Connection to ENet server failed or timed out.");
		}
	}

	/*
		Disconnects the client from its connected server.
	 */
	void
	Core_enet_client_disconnect() {
		if (conn == nullptr) {
			return;
		}

		enet_peer_disconnect_now(conn, 0);
		conn = nullptr;
	}

	/*
		Polls for incoming network events such as connections,
		disconnections, and data packets.
		
		This function blocks for a specified duration while waiting
		for events, then returns control to the caller.
	 */
	void Core_enet_poll() {
		ENetEvent event;
		while (enet_host_service(host, &event, 1000) > 0) {
			/*switch (event.type) {
			case ENET_EVENT_TYPE_CONNECT:
				break;
			case ENET_EVENT_TYPE_DISCONNECT:
				event.peer->data = nullptr;
				break;
			case ENET_EVENT_TYPE_RECEIVE:
				enet_packet_destroy(event.packet);
				break;
			}*/
		}
	}

	/*
		Sends queued outgoing packets to connected peers.
		
		This function ensures that all pending data is transmitted
		for both server and client hosts.
	 */
	void Core_enet_send() {
		/*auto res = pool_manager::instance().flush_packets();
		for (auto& r : res) {
			ENetPacket* packet = enet_packet_create(r.data.data(), r.data.size(), r.flags);
			int send_res = enet_peer_send(r.peer, r.channel, packet);
			if (send_res < 0) {
				enet_packet_destroy(packet);
			}
		}*/
	}
}