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
	}

	/*
		Disconnects a client from the server.

		@param _Peer Pointer to the peer to disconnect.
	 */
	void
	Core_enet_server_disconnect(void* _Peer) {
		if (_Peer == nullptr) {
			return;
		}

		ENetPeer* peer = static_cast<ENetPeer*>(_Peer);
		enet_peer_disconnect_now(peer, 0);
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
		
		@param _WaitDuration The maximum duration to wait for events.
	 */
	void Core_enet_poll(std::chrono::milliseconds _WaitDuration) {
		/*ENetEvent enet;
		while (enet_host_service(host, &enet, static_cast<enet_uint32>(_WaitDuration.count())) > 0) {
			enet_data instance{ 0 };
			instance.type = static_cast<std::uint32_t>(enet.type);
			instance.channel = enet.channelID;

			instance.flags = (enet.packet != nullptr) ? enet.packet->flags : 0;

			if (enet.packet != nullptr && enet.packet->dataLength > 0) {
				instance.data.resize(enet.packet->dataLength);
				std::memcpy(instance.data.data(), enet.packet->data, enet.packet->dataLength);
			}

			instance.peer = static_cast<void*>(enet.peer);

			enet_packet_destroy(enet.packet);

			net::events.push(instance);
		}*/
	}
}