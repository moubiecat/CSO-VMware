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
#ifndef _CALLBACKS_H_
#define _CALLBACKS_H_

#include <cstddef>
#include "const.h"

namespace cat::core {
	/*
	 * Callback invoked when a new peer connects to the server.
	 *
	 * @param _Peer  A handle representing the connected peer.
	 */
	extern void OnConnect(peer_t _Peer);

	/*
	 * Callback invoked when a peer disconnects from the server.
	 *
	 * @param _Peer  A handle representing the disconnected peer.
	 */
	extern void OnDisconnect(peer_t _Peer);

	/*
	 * Callback invoked when a message is received from a peer.
	 *
	 * @param _Peer  A handle representing the peer that sent the message.
	 * @param _Data  A pointer to the received data.
	 * @param _Size  The size of the received data in bytes.
	 */
	extern void OnMessage(peer_t _Peer, pdata_t _Data, std::size_t _Size);
}

#endif // ^^^ !_CALLBACKS_H_