/*
 * tcpconnection.cpp
 *
 *  Created on: 20 mrt. 2022
 *      Author: andre
 */

#include "tcpconnection.hpp"
#include "network.hpp"

#include <iostream>

namespace network {

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

    // TODO: exit conditions
    // Depends on:
    //	* setting  timeouts on sockets
    //  * termination signalling ( atomic )

    int bytes_received = 0;
    while (_this_->m_receiveThreadActive) {
        bytes_received = recv(_this_->m_socket, _this_->m_recv_buffer, sizeof(_this_->m_recv_buffer), 0 );
        if (bytes_received < 0) {
            // If there is any other error then timeout
            if (ETIMEDOUT != bytes_received) {
                std::cerr << "Error reading from socket" << std::endl;
                break;
            }
        } else if (bytes_received == 0) {
            std::cerr << "Remote disconnected" << std::endl;
            break;
        }
        // Todo: pass data to parser
        std::cout << "Received " << bytes_received << " bytes " << std::endl;
    }
}

} // namespace network
