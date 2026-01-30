/***
* MIT License
*
* Copyright (c) 2026 moubiecat
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all
* copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
***/

#pragma once
#ifndef _SERVER_H_
#define _SERVER_H_

#include "net.h"
#include "typing.h"
#include "packet.h"

namespace cat {
	/*
	 * Represents a server endpoint for network communication.
	 *
	 * This class extends the base `net` class to provide server-specific
	 * functionality, including listening for incoming connections and handling
	 * client interactions.
	 */
	class server : public net {
	public:
		/*
		 * Constructs a server endpoint descriptor with the specified host and port.
		 *
		 * The constructor performs no validation and does not establish any
		 * networking resources. It simply stores the provided parameters.
		 *
		 * @param _Host  A string view representing the host/IP on which the server
		 *               should listen. The referenced string must remain valid for
		 *               the lifetime of this object.
		 *
		 * @param _Port  The port number on which the server is expected to bind.
		 */
		constexpr server(std::string_view _Host, uint16_t _Port) noexcept 
			: net(_Host, _Port) {
		}

		/*
		 * Establishes a connection for the client or server.
		 *
		 * This function performs the necessary initialization and setup,
		 * such as creating network hosts and preparing for data transmission.
		 */
		void connect() const override;

		/*
		 * Disconnects the client from the server or shuts down the server.
		 *
		 * This function ensures that all active connections are properly
		 * terminated and that associated resources are released.
		 */
		void disconnect() const override;

		/*
		 * Polls for incoming network events such as connections,
		 * disconnections, and data packets.
		 *
		 * This function blocks for a specified duration while waiting
		 * for events, then returns control to the caller.
		 */
		void flush() const override;

		/*
		 * Broadcasts a packet to all connected peers.
		 *
		 * @param _Packet Pointer to the packet to be broadcasted.
		 */
		void broadcast(const packet* _Packet) const;

		/*
		 * Sends a packet to a specific peer.
		 *
		 * @param _Packet Pointer to the packet to be sent.
		 * @param _Peer   The target peer to which the packet should be sent.
		 */
		void sendto(const packet* _Packet, peer_t _Peer) const;
	};
}

#endif // ^^^ !_SERVER_H_