/*
 * tcpconnection.hpp
 *
 *  Created on: 20 mrt. 2022
 *      Author: andre
 */

#include "network.hpp"

#include "connection.hpp"
#include <atomic>
#include <thread>

namespace network {

class TcpConnection : public Connection {
  public:
    TcpConnection(socket_t socket, struct sockaddr_in6 sin6_accept = {0});
    ~TcpConnection();

    void sendPacket(std::vector<uint8_t> packet) override;
    void process(void) override;

  private:
    struct sockaddr_in6 m_sin6 = {0};
    socket_t m_socket = 0;

    std::atomic<bool> m_receiveThreadActive = false;
    std::thread *m_receiveThread = nullptr;

    static void receiveThreadFunc(TcpConnection *_this_);
};

} // namespace network
