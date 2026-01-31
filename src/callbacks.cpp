#include "callbacks.h"
#include "service.h"

namespace cat::core {
	/*
		Callback invoked when a new peer connects to the server.
		
		@param _Peer  A handle representing the connected peer.
	 */
	void 
	OnConnect(peer_t _Peer) {
		//
		// Call the registered CONNECT callbacks
		//
		enet_event event{ _Peer, nullptr, 0 };
		service::instance().call(service_type::enet_connect, event);
	}

	/*
		Callback invoked when a peer disconnects from the server.
		
		@param _Peer  A handle representing the disconnected peer.
	 */
	void 
	OnDisconnect(peer_t _Peer) {
		//
		// Call the registered DISCONNECT callbacks
		//
		enet_event event{ _Peer, nullptr, 0 };
		service::instance().call(service_type::enet_disconnect, event);
	}

	/*
		Callback invoked when a message is received from a peer.
		
		@param _Peer  A handle representing the peer that sent the message.
		@param _Data  A pointer to the received data.
		@param _Size  The size of the received data in bytes.
	 */
	void 
	OnMessage(peer_t _Peer, pdata_t _Data, std::size_t _Size) {
		//
		// Call the registered MESSAGE callbacks
		//
		enet_event event{ _Peer, _Data, _Size };
		service::instance().call(service_type::enet_message, event);
	}
}