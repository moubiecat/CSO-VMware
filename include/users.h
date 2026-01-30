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
#ifndef _USERS_H_
#define _USERS_H_

#include <optional>
#include "typing.h"

namespace cat {
	/*
	 * @brief Initialize the user management system.
	 */
	void setup_user_system() noexcept;

	/*
	 * @brief Acquire a new user ID.
	 *
	 * @param _Peer The peer to associate with the new user ID.
	 * @return A newly acquired user ID, or std::nullopt if none are available.
	 */
	[[nodiscard]] std::optional<userid_t> acquire_user(const peer_t _Peer) noexcept;

	/*
	 * @brief Get the peer associated with a given user ID.
	 *
	 * @param _User The user ID whose peer is to be retrieved.
	 * @return The peer associated with the given user ID, or std::nullopt if the user ID is invalid or not in use.
	 */
	[[nodiscard]] std::optional<peer_t> get_user_peer(userid_t _User) noexcept;

	/*
	 * @brief Release a previously acquired user ID.
	 *
	 * @param _User The user ID to release.
	 */
	void release_user(userid_t _User) noexcept;
}

#endif // ^^^ !_USERS_H_