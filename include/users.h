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
#include <vector>
#include "typings.h"

namespace cat {
	/*
	 * @brief Acquire a user ID for a given peer.
	 *
	 * @param _Peer The peer for which to acquire a user ID.
	 * @return true if the user ID was successfully acquired, false otherwise.
	 */
	[[nodiscard]] bool acquire_user(const peer_t _Peer) noexcept;

	/*
	 * @brief Get the user ID associated with a given peer.
	 *
	 * @param _Peer The peer whose user ID is to be retrieved.
	 * @return The user ID associated with the given peer.
	 */
	[[nodiscard]] std::optional<userid_t> get_userid(const peer_t _Peer) noexcept;

	/*
	 * @brief Get a list of all user IDs.
	 *
	 * @return A vector containing all user IDs.
	 */
	[[nodiscard]] std::vector<userid_t> get_userids() noexcept;

	/*
	 * @brief Release the user ID associated with a given peer.
	 *
	 * @param _Peer The peer whose user ID is to be released.
	 */
	void release_user(const peer_t _Peer) noexcept;
}

#endif // ^^^ !_USERS_H_