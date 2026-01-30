#include <array>
#include <queue>
#include "users.h"

namespace cat {
	/*
		@brief Structure to hold user entry information.

		@member in_use Indicates whether the user entry is currently in use.
		@member peer The peer associated with the user entry.
	 */
	struct user_entry {
		bool in_use = false;
		peer_t peer = nullptr;
	};
	
	/* 	
		Queue to manage available user IDs.
		IDs are reused when users are released.
	 */
	static std::queue<userid_t> ids;

	/*
		Array to hold user entries.
		Supports up to 32 concurrent users.
	 */
	static std::array<user_entry, 32> users;


	/*
		@brief Initialize the user management system.
	 */
	void 
	setup_user_system() noexcept {
		while (!ids.empty()) {
			ids.pop();
		}

		for (userid_t i = 0; i < users.size(); ++i) {
			ids.push(i);
			users[i] = {};
		}
	}

	/*
		@brief Acquire a new user ID.
		
		@param _Peer The peer to associate with the new user ID.
		@return A newly acquired user ID, or std::nullopt if none are available.
	 */
	std::optional<userid_t> 
	acquire_user(const peer_t _Peer) noexcept {
		if (ids.empty()) {
			return std::nullopt;
		}

		const userid_t id = ids.front();
		ids.pop();

		auto& slot	= users[id];
		slot.in_use = true;
		slot.peer	= _Peer;
		return id;
	}

	/*
		@brief Get the peer associated with a given user ID.
		
		@param _User The user ID whose peer is to be retrieved.
		@return The peer associated with the given user ID, or std::nullopt if the user ID is invalid or not in use.
	 */
	std::optional<peer_t> 
	get_user_peer(userid_t _User) noexcept {
		if (_User >= users.size())
			return std::nullopt;

		const auto& slot = users[_User];
		if (!slot.in_use) {
			return std::nullopt;
		}

		return slot.peer;
	}

	/*
		@brief Get a list of all currently active user IDs.
		
		@return A list of active user IDs.
	 */
	std::list<userid_t> 
	get_active_users() noexcept {
		std::list<userid_t> res;
		for (userid_t i = 0; i < users.size(); ++i) {
			if (users[i].in_use) {
				res.push_back(i);
			}
		}
		return res;
	}

	/*
		@brief Release a previously acquired user ID.
		
		@param _User The user ID to release.
	 */
	void 
	release_user(userid_t _User) noexcept {
		if (_User >= users.size()) {
			return;
		}

		auto& slot = users[_User];
		if (!slot.in_use) {
			return;
		}

		slot = {};
		ids.push(_User);
	}
}