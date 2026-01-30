#include "net.h"
#include "core.h"
#include "users.h"
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
	is_connect() noexcept {
		return connecting;
	}

	/*
		Establishes a connection for the client or server.
		
		This function performs the necessary initialization and setup,
		such as creating network hosts and preparing for data transmission.
	 */
	void
	server::connect() const {
		setup_user_system();
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
		// core::Core_enet_poll();

		/*while (!net::events.empty()) {
			enet_data event = net::events.front();
			net::events.pop();
		}*/
	}

	/*
		Broadcasts a packet to all connected peers.
		
		@param _Packet Pointer to the packet to be broadcasted.
	 */
	void 
	server::broadcast(const packet* _Packet) const {
		cat::ostream os;
		_Packet->serialize(os);
		//core::Core_enet_send(buffer.data(), buffer.size(), 0, 1);
	}

	/*
		Sends a packet to a specific peer.
		
		@param _Packet Pointer to the packet to be sent.
		@param _Peer   The target peer to which the packet should be sent.
	 */
	void 
	server::sendto(const packet* _Packet, peer_t _Peer) const {
		cat::ostream os;
		_Packet->serialize(os);
		//core::Core_enet_send(buffer.data(), buffer.size(), 0, 0);
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
		// core::Core_enet_poll();

		//std::vector<std::byte> data = {
		//	std::byte{0x05}, std::byte{0x00}, std::byte{0x00}, std::byte{0x00},
		//	std::byte{'H'},  std::byte{'e'},  std::byte{'l'},  std::byte{'l'},
		//	std::byte{'o'} };

		//cat::istream stream(data);

		//std::uint8_t pid;
		//stream.read(pid);
		//auto packet = cat::packet_registry::create(pid);

		//if (packet && packet->deserialize(stream)) {
		//	// successfully created and deserialized packet
		//	result res = packet->process();

		//	if (res == result::success) {
		//		// packet processed successfully
		//	} else {
		//		// packet processing failed
		//	}
		//}
	}

	/*
		Sends a packet to the connected server.
		
		@param _Packet Pointer to the packet to be sent.
	 */
	void 
	client::send(const packet* _Packet) const {
		cat::ostream os;
		_Packet->serialize(os);
		//core::Core_enet_send(buffer.data(), buffer.size(), 0, 0);
	}
}