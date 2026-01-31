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
#ifndef _SERVICE_H_
#define _SERVICE_H_

#include <cstdint>
#include <functional>
#include "const.h"

namespace cat {
	/* Network event structure */
	struct enet_event {
		peer_t		peer;
		pdata_t		data;
		std::size_t size;
	};

	/* Service types for network events */
	enum class service_type : std::uint8_t {
		enet_connect	= 1,
		enet_disconnect = 2,
		enet_message	= 3,
	};

	/*
	 * @brief Lightweight event dispatch service.
	 *
	 * Provides a centralized registry for handling ENet-related events
	 * based on service_type. Each service type can register a single
	 * callback, which will be invoked when the corresponding event occurs.
	 *
	 * This class follows the singleton pattern and is intended to be used
	 * as a global event router within the networking subsystem.
	 */
	class service {
	public:
		using param_t = enet_event&;
		using callback_t = std::function<void(param_t)>;
		using handlers_t = std::unordered_map<service_type, callback_t>;
	public:
		/*
		 * @brief Register or replace an event handler for a service type.
		 *
		 * If a handler is already registered for the given type, it will
		 * be replaced by the new callback.
		 *
		 * @param type The service type to associate with the handler.
		 * @param cb   The callback to invoke when the event is dispatched.
		 * @return Reference to this service instance (for chaining).
		 */
		service& on(service_type type, callback_t cb) {
			handlers[type] = std::move(cb);
			return *this;
		}

		/*
		 * @brief Dispatch an event to the registered handler.
		 *
		 * Looks up the handler associated with the given service type
		 * and invokes it if found. If no handler is registered, the
		 * call is silently ignored.
		 *
		 * @param type  The service type of the event.
		 * @param event The ENet event to forward to the handler.
		 */
		void call(service_type type, param_t event) {
			auto it = handlers.find(type);
			if (it != handlers.end()) {
				it->second(event);
			}
		}

		/*
		 * @brief Get the singleton instance of the service.
		 *
		 * The instance is lazily initialized on first use and is
		 * guaranteed to be thread-safe since C++11.
		 *
		 * @return Reference to the global service instance.
		 */
		static service& instance() {
			static service instance;
			return instance;
		}
	private:
		//< The map of event handlers
		std::unordered_map<service_type, callback_t> handlers;
	};
}

#endif // ^^^ !_SERVICE_H_