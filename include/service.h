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
		ENET_CONNECT	= 1,
		ENET_DISCONNECT = 2,
		ENET_MESSAGE	= 3,
	};

	class service {
	public:
		using param_t = enet_event&;
		using callback_t = std::function<void(param_t)>;
		using handlers_t = std::unordered_map<service_type, callback_t>;
	public:

		service& on(service_type type, callback_t cb) {
			handlers[type] = cb;
			return *this;
		}

		void call(service_type type, enet_event& event) {
			auto it = handlers.find(type);
			if (it != handlers.end()) {
				it->second(event);
			}
		}

		static service& instance() {
			static service inst;
			return inst;
		}
	private:
		//< The map of event handlers
		std::unordered_map<service_type, callback_t> handlers;
	};
}

#endif // ^^^ !_SERVICE_H_