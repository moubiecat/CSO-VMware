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
#ifndef _CLIENT_H_
#define _CLIENT_H_

#include "net.h"
#include "typing.h"
#include "packet.h"

namespace cat {
	/*
	 * Represents a client endpoint for network communication.
	 *
	 * This class extends the base `net` class to provide client-specific
	 * functionality, including connecting to a server and handling data exchange.
	 */
	class client : public net {
	public:
		/*
		 * Constructs a client endpoint descriptor with the specified host and port.
		 *
		 * The constructor performs no validation and does not establish any
		 * networking resources. It simply stores the provided parameters.
		 *
		 * @param _Host  A string view representing the server's host/IP to which
		 *               the client should connect. The referenced string must
		 *               remain valid for the lifetime of this object.
		 *
		 * @param _Port  The port number on which the server is expected to be
		 *               listening.
		 */
		constexpr client(std::string_view _Host, uint16_t _Port) noexcept
			: net(_Host, _Port) {
		}

		/*
		 * Establishes a connection to the server.
		 *
		 * This function performs the necessary initialization and setup,
		 * such as creating network hosts and preparing for data transmission.
		 */
		void connect() const override;

		/*
		 * Disconnects from the server and cleans up resources.
		 *
		 * This function ensures that all network resources are properly released
		 * and that the client is gracefully disconnected from the server.
		 */
		void disconnect() const override;

		/*
		 * Polls for incoming events or messages from the server.
		 *
		 * This function checks for any new data or events and processes them
		 * accordingly, allowing the client to respond to server communications.
		 */
		void poll() const override;

		/*
		 * Sends a packet to the connected server.
		 *
		 * @param _Packet Pointer to the packet to be sent.
		 */
		void send(const packet* _Packet) const;
	};
}

#endif // ^^^ !_CLIENT_H_