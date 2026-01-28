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
#ifndef _NET_H_
#define _NET_H_

#include <cstdint>
#include <format>
#include <string>
#include <string_view>
#include <queue>
#include <vector>

namespace cat {
    /*
     * Reports whether the ENet subsystem has been successfully initialized.
     *
     * @return true  If the ENet system is initialized and ready.
     * @return false If ENet has not been set up or has already been shut down.
     */
    [[nodiscard]] bool is_setup() noexcept;

    /*
     * Returns whether a client connection attempt is currently active.
     *
     * @return true  If a connection is active or being established.
     * @return false If no client connection exists.
     */
    [[nodiscard]] bool is_connecting() noexcept;

    /*
     * Represents a network event in the ENet library.
     * Contains information about the type of event,
     * the channel on which it occurred, any associated flags,
     * the data payload for packet events, and the peer
     * that generated the event for connection-related events.
     */
    struct enet_data {
        std::uint32_t   type;			/**< type of the event */
        std::uint8_t    channel;		/**< channel on the peer that generated the event, if appropriate */
        std::uint32_t   flags;			/**< bitwise-or of ENetPacketFlag constants */
        std::vector<std::uint8_t> data;	/**< data for packet */
        void* peer;						/**< peer that generated a connect, disconnect or receive event */
    };

    /*
     * Abstract base class representing a network endpoint (client or server).
     *
     * This class encapsulates common properties and behaviors for network
     * communication, including host and port management, connection handling,
     * and event polling.
     */
    class net {
    public:
        /*
         * Constructs a net object with the specified host and port.
         *
         * @param _Host The host name or IP address for the endpoint.
         * @param _Port The port number for the endpoint.
         */
        constexpr net(std::string_view _Host, std::uint32_t _Port) noexcept
            : host(_Host), port(_Port) {
        }

        /*
         * Returns the client/server address in "host:port" format.
         * Each call generates a new std::string using std::format.
         *
         * @return A std::string representing the formatted address.
         */
        [[nodiscard]] std::string ipaddress() const noexcept {
            return std::format("{}:{}", host, port);
        }

        /*
         * Establishes a connection for the client or server.
         *
         * This function performs the necessary initialization and setup,
         * such as creating network hosts and preparing for data transmission.
         */
        virtual void connect() const = 0;

        /*
         * Disconnects the client from the server or shuts down the server.
         *
         * This function ensures that all active connections are properly
         * terminated and that associated resources are released.
         */
        virtual void disconnect() const = 0;

        /*
         * Polls for incoming network events such as connections,
         * disconnections, and data packets.
         *
         * This function blocks for a specified duration while waiting
         * for events, then returns control to the caller.
         */
        virtual void poll() const = 0;
    public:
        //< Host name or IP address for the listening endpoint
        const std::string host;

        //< Port number for accepting incoming connections
        const std::uint32_t port;

        //< Queue to store incoming ENet events
        static std::queue<enet_data> events;
    };
}

#endif // ^^^ !_NET_H_