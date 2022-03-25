/*
 * tcpconnection.cpp
 *
 *  Created on: 20 mrt. 2022
 *      Author: andre
 */

#include "tcpconnection.hpp"
#include "network.hpp"

#include <iostream>
#include <vector>
#include <errno.h>
#include <cstring>

namespace network {

TcpConnection::TcpConnection(socket_t socket) {
    m_socket = socket;
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

TcpConnection::TcpConnection(struct sockaddr_in6 sin6, socket_t socket) {
    m_sin6 = sin6;
    m_socket = socket;

    std::cout << "New TCP Connection" << std::endl;
    char str[INET6_ADDRSTRLEN];
    if (inet_ntop(AF_INET6, &sin6.sin6_addr, str, INET6_ADDRSTRLEN) == NULL) {
        std::cerr << "Error parsing remote address" << std::endl;
    } else {
        std::cout << "Remote Address is " << str << std::endl;
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
    m_receiveThreadActive = false;
    if (m_receiveThread->joinable())
        m_receiveThread->join();
    delete m_receiveThread;
    closesocket(m_socket);
}

void TcpConnection::sendPacket(void) {}
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
            break;
        } else {
            // Todo: pass data to parser
            std::cout << "Received " << bytes_received << " bytes " << std::endl;

            // Please note: we want a copy of the data so the receive buffer is available for the next message
            std::vector<uint8_t> received_data(recv_buffer, recv_buffer + bytes_received);
            // When we want to parse this data, we need to identify who sent it
            // Thus this connection needs an identifier.
            // Therefore I think we need a ConnectionManager of some kind
            parse(received_data);
        }
    }
}

} // namespace network
