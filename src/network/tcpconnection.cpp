/*
 * tcpconnection.cpp
 *
 *  Created on: 20 mrt. 2022
 *      Author: andre
 */

#include "tcpconnection.hpp"
#include "network.hpp"
#include "protocol.hpp"

#include <cstring>
#include <errno.h>
#include <iostream>
#include <random>
#include <vector>

#include "../utils/logger.hpp"

namespace network {

TcpConnection::TcpConnection(socket_t socket, struct sockaddr_in6 sin6) {
    m_sin6 = sin6;
    m_socket = socket;

    LOG_INFO("New TCP Connection", 0);

    char str[INET6_ADDRSTRLEN];
    if (inet_ntop(AF_INET6, &sin6.sin6_addr, str, INET6_ADDRSTRLEN) == NULL) {

        LOG_ERROR("Error parsing remote address", 0);
    } else {
        LOG_INFO("Remote Address is %s", str);
    }

    //--------------------------------------------
    // Configure socket options for the new socket
    //--------------------------------------------
    const int no = 0;
    (void)no;
    const int yes = 1;
    (void)yes;
    // Set timeouts for send and receive in blocking mode
    const struct timeval tv = {.tv_sec = 0, .tv_usec = 100000};
    setsockopt(socket, SOL_SOCKET, SO_RCVTIMEO, (const char *)&tv, sizeof(tv));
    setsockopt(socket, SOL_SOCKET, SO_SNDTIMEO, (const char *)&tv, sizeof(tv));

    setsockopt(socket, SOL_SOCKET, SO_KEEPALIVE, (const char *)&yes, sizeof(yes));

    m_receiveThreadActive = true;
    m_receiveThread = new std::thread(TcpConnection::receiveThreadFunc, this);
}

TcpConnection::~TcpConnection() {
    LOG_INFO("Destroying connection %d", m_client_id);
    m_receiveThreadActive = false;
    LOG_INFO("Stopping receive thread ", 0);
    if (m_receiveThread->joinable()) {
        LOG_INFO("receive thread joinable", 1);
        m_receiveThread->join();
    } else {
        LOG_INFO("receive thread not joinable", 0);
    }
    LOG_INFO("Deleting Receive Thread", 0);
    delete m_receiveThread;
    LOG_INFO("Closing socket", 0);
    closesocket(m_socket);
}

void TcpConnection::sendPacket(std::vector<uint8_t> packet) {
    size_t sent_bytes = send(m_socket, (const char *)packet.data(), packet.size(), 0);
    if (sent_bytes == packet.size()) {
        LOG_INFO("Sent %d bytes", sent_bytes);
    } else {
        LOG_ERROR("Sent %d of %d bytes", sent_bytes, packet.size());
    }
}
void TcpConnection::process(void) {}

void TcpConnection::receiveThreadFunc(TcpConnection *_this_) {
    std::cout << "Starting Receive Thread" << std::endl;
    char recv_buffer[1024] = {0};
    // TODO: exit conditions
    // Depends on:
    //	* setting  timeouts on sockets
    //  * termination signalling ( atomic )

    int bytes_received = 0;
    while (_this_->m_receiveThreadActive) {
        bytes_received = recv(_this_->m_socket, recv_buffer, sizeof(recv_buffer), 0);
        if (bytes_received < 0) {
            // If there is any other error then timeout
            if (EWOULDBLOCK != errno) {
                std::cerr << "Error reading from socket: " << errno << " " << strerror(errno) << std::endl;
                break;
            }
            // There is no data
            continue;
        } else if (bytes_received == 0) {
            std::cerr << "Remote disconnected" << std::endl;
            on_disconnect(_this_);
            break;
        } else {
            // Todo: pass data to parser
            std::cout << "Received " << bytes_received << " bytes " << std::endl;

            // Please note: we want a copy of the data so the receive buffer is available for the next message
            std::vector<uint8_t> received_data(recv_buffer, recv_buffer + bytes_received);
            // When we want to parse this data, we need to identify who sent it
            // Thus this connection needs an identifier.
            // Therefore I think we need a ConnectionManager of some kind
            parse(received_data, _this_);
        }
    }
}

} // namespace network
