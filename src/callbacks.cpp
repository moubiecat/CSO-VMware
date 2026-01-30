#include "callbacks.h"

namespace cat::core {
	/*
		Callback invoked when a new peer connects to the server.
		
		@param _Peer  A handle representing the connected peer.
	 */
	void 
	OnConnect(peer_t _Peer) {
	}

	/*
		Callback invoked when a peer disconnects from the server.
		
		@param _Peer  A handle representing the disconnected peer.
	 */
	void 
	OnDisconnect(peer_t _Peer) {
	}

	/*
		Callback invoked when a message is received from a peer.
		
		@param _Peer  A handle representing the peer that sent the message.
		@param _Data  A pointer to the received data.
		@param _Size  The size of the received data in bytes.
	 */
	void 
	OnMessage(peer_t _Peer, pdata_t _Data, std::size_t _Size) {
	}
}