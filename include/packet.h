/***
* MIT License
*
* Copyright (c) 2025 MouBieCat
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

#include "stream.h"

namespace cat {
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
	};
}

#endif // ^^^ !_PACKET_H_