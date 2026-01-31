#include <array>
#include <ranges>
#include "const.h"
#include "users.h"

namespace cat {
	/*
		@brief Structure to hold user entry information.

		@member active Indicates whether the user entry is currently active.
		@member peer The peer associated with the user entry.
	 */
	struct user_entry {
		bool active;
		peer_t peer;
	};

	/*
		Array to hold user entries.
		Size is defined by MAX_USERS constant.
	 */
	static std::array<user_entry, MAX_USERS> users;


	/*
		@brief Find the user entry associated with a given peer.

		@param peer The peer whose user entry is to be found.
		@return An iterator to the user entry if found, otherwise users.end().
	 */
	static auto find_entry(const peer_t _Peer) noexcept {
		return std::ranges::find_if(users, [_Peer](const auto& _Entry) {
			return _Entry.active && _Entry.peer == _Peer; });
	}

	/*
		@brief Acquire a user ID for a given peer.
		
		@param _Peer The peer for which to acquire a user ID.
		@return The acquired user ID, or std::nullopt if acquisition failed.
	 */
	std::optional<userid_t> 
	acquire_user(const peer_t _Peer) noexcept {
		auto it = std::ranges::find_if(users, [](const user_entry& entry) {
			return !entry.active; });
		if (it != users.end()) {
			it->active = true;
			it->peer = _Peer;
			return static_cast<userid_t>(std::distance(users.begin(), it));
		}
		return std::nullopt;
	}

	/*
		@brief Get the peer associated with a given user ID.
		
		@param _User The user ID whose peer is to be retrieved.
		@return The peer associated with the given user ID, or std::nullopt if not found.
	 */
	std::optional<peer_t> 
	get_peer(const userid_t _User) noexcept {
		if (_User < static_cast<userid_t>(users.size()) && users[_User].active) {
			return users[_User].peer;
		}

		return std::nullopt;
	}

	/*
		@brief Get a list of all user IDs.
		
		@return A vector containing all user IDs.
	 */
	std::vector<userid_t> 
	get_users() noexcept {
		std::vector<userid_t> userids;
		for (userid_t i = 0; i < static_cast<userid_t>(users.size()); ++i) {
			if (users[i].active) {
				userids.push_back(i);
			}
		}
		return userids;
	}

	/*
		@brief Release the user ID associated with a given peer.
		
		@param _Peer The peer whose user ID is to be released.
	 */
	void 
	release_user(const peer_t _Peer) noexcept {
		if (auto it = find_entry(_Peer); it != users.end()) {
			it->active = false;
			it->peer = nullptr;
		}
	}
}