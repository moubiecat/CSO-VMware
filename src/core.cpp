#include <stdexcept>
#include <enet/enet.h>
#include "core.h"

namespace cat::core {
	/*
		Indicates whether the ENet library has been successfully initialized.
		Prevents redundant initialization and ensures a proper shutdown sequence.
	 */
	static bool initialized = false;

	/*
		Global pointer to the active ENet host instance.
		Used by both server and client configurations to manage network operations.
		Set to nullptr when no active host exists.
	 */
	static ENetHost* host = nullptr;

	/*
		Global pointer representing the active peer connection.
		Used on the client side to maintain the connection to a remote ENet server.
	 */
	static ENetPeer* conn = nullptr;


	/*
		Initializes the ENet library for networking.

		Must be called before any ENet operations.
	 */
	void
	Core_enet_initialize() {
		if (initialized) {
			return;
		}

		int res = enet_initialize();
		if (res != 0) {
			throw std::runtime_error("An error occurred while initializing ENet.");
		}

		initialized = true;
	}

	/*
		Deinitializes the ENet library and cleans up resources.

		Must be called after all ENet operations are finished.
	 */
	void
	Core_enet_deinitialize() {
		if (host) {
			enet_host_destroy(host);
			host = nullptr;
		}

		if (initialized) {
			enet_deinitialize();
			initialized = false;
		}

		conn = nullptr;
	}
}