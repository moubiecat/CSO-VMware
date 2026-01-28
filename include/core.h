/***
* MIT License
*
* Copyright (c) 2026 MouBieCat
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
#ifndef _CORE_H_
#define _CORE_H_

#include <cstdint>
#include <string_view>

namespace cat::core {
	/*
	 * Initializes the ENet library for networking.
	 *
	 * Must be called before any ENet operations.
	 */
	void Core_enet_initialize();

	/*
	 * Deinitializes the ENet library and cleans up resources.
	 *
	 * Must be called after all ENet operations are finished.
	 */
	void Core_enet_deinitialize();

	/*
	 * Creates an ENet server host.
	 *
	 * @param _Host The hostname or IP address to bind the server to.
	 * @param _Port The port number on which the server will listen for incoming connections.
	 * @param _Chunm The maximum number of channels to be used for communication.
	 * @param _Cltnum The maximum number of clients that can connect to the server.
	 */
	void Core_enet_server_create(std::string_view _Host, std::uint32_t _Port, std::uint32_t _Chunm, std::uint32_t _Cltnum);

	/*
	 * Creates an ENet client host.
	 *
	 * @param _Cltnum The maximum number of channels to be used for communication.
	 */
	void Core_enet_client_create(std::uint32_t _Cltnum);

	/*
	 * Connects the ENet client to a remote server.
	 *
	 * @param _Server The hostname or IP address of the remote server.
	 * @param _Port The port number of the remote server.
	 * @param _Chunm The number of channels to be used for communication.
	 */
	void Core_enet_client_connect(std::string_view _Server, std::uint32_t _Port, std::uint32_t _Chunm);

	/*
	 * Disconnects a client from the server.
	 *
	 * @param _Peer Pointer to the peer to disconnect.
	 */
	void Core_enet_server_disconnect(void* _Peer);

	/*
	 * Disconnects the client from its connected server.
	 */
	void Core_enet_client_disconnect();
}

#endif // ^^^ !_CORE_H_