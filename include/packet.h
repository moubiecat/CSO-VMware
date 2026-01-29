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
#ifndef _PACKET_H_
#define _PACKET_H_

#include <concepts>
#include <cstdint>
#include <memory>
#include <unordered_map>
#include "stream.h"

namespace cat {
	/*
	 * Enumeration representing the result of packet processing.
	 */
	enum class result {
		success = 0,
		failure = 1,
		error	= 2,
	};

	/*
	 * Base interface for serializable packets.
	 * All derived packets must implement serialization and deserialization.
	 */
	struct packet {
		/*
		 * Base interface for serializable packets.
		 * Derived classes must implement serialization and deserialization logic.
		 * A virtual destructor is required to ensure correct cleanup when deleting
		 * derived packets through base class pointers.
		 */
		virtual ~packet() = default;

		/*
		 * Serializes the packet into a writable stream.
		 *
		 * @param _Stream Output stream to write data.
		 * @return true if successful, false otherwise.
		 */
		virtual bool serialize(ostream& _Stream) const = 0;

		/*
		 * Deserializes packet data from a readable stream.
		 *
		 * @param _Stream Input stream to read data.
		 * @return true if successful, false otherwise.
		 */
		virtual bool deserialize(istream& _Stream) = 0;

		/*
		 * Processes the packet's data.
		 *
		 * @return An integer status code indicating the result of processing.
		 */
		virtual result process() = 0;
	};

	/*
	 * Concept to ensure a type is a packet and default constructible.
	 * 1. The type must be derived from the 'packet' base class.
	 * 2. The type must be default constructible (i.e., it can be constructed without arguments).
	 *
	 * @tparam _Pkt Type to check.
	 */
	template<class _Pkt>
	concept packet_binder =
		std::derived_from<_Pkt, packet>&&
		std::is_default_constructible_v<_Pkt>;

	/*
	 * Packet type registry for dynamic packet creation.
	 *
	 * Allows registration of packet types with unique IDs and
	 * creation of packet instances based on those IDs.
	 */
	class packet_registry {
	public:
		/*
		 * Registers a packet type with a unique identifier.
		 *
		 * @tparam _Pkt Packet type to register (must satisfy packet_binder concept).
		 * @param _Id   Unique identifier for the packet type.
		 * @return true  If registration was successful
		 * @return false If the ID is already registered
		 */
		template<packet_binder _Pkt>
		static bool register_type(std::uint8_t _Id) {
			auto& map = types();
			if (map.find(_Id) != map.end()) {
				return false;
			}
			map[_Id] = []() -> std::unique_ptr<packet> {
				return std::make_unique<_Pkt>(); };
			return true;
		}

		/*
		 * Creates a packet instance based on the given ID.
		 *
		 * @param _Id Unique identifier for the packet type.
		 * @return A unique pointer to the created packet instance, or nullptr if ID not found.
		 */
		static std::unique_ptr<packet> create(std::uint8_t _Id) {
			auto it = types().find(_Id);
			return (it != types().end()) ? it->second() : nullptr;
		}
	private:
		//< Type alias for packet creator function pointer.
		using creator_fn = std::unique_ptr<packet>(*)();

		/*
		 * Returns the static map of registered packet types.
		 *
		 * @return Reference to the map of packet type creators.
		 */
		static std::unordered_map<std::uint8_t, creator_fn>& types() {
			static std::unordered_map<std::uint8_t, creator_fn> instance;
			return instance;
		}
	};
}

#endif // ^^^ !_PACKET_H_