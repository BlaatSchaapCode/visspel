/*
 * tcpconnection.hpp
 *
 *  Created on: 20 mrt. 2022
 *      Author: andre
 */

#include "iconnection.hpp"
#include "network.hpp"

#include <atomic>
#include <thread>

namespace network {

class TcpConnection : public iConnection {
  public:
    TcpConnection(struct sockaddr_in6 sin6_accept, socket_t socket);
    TcpConnection(socket_t socket);
    ~TcpConnection();

    void sendPacket(void) override;
    void process(void) override;

  private:
    struct sockaddr_in6 m_sin6 = {0};
    socket_t m_socket = 0;
    char m_recv_buffer[1024] = {0};
    std::atomic<bool> m_receiveThreadActive = false;
    std::thread *m_receiveThread = nullptr;

    static void receiveThreadFunc(TcpConnection *_this_);
};

} // namespace network
