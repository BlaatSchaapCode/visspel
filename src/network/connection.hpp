/*
 * iconnection.hpp
 *
 *  Created on: 20 mrt. 2022
 *      Author: andre
 */

#ifndef SRC_NETWORK_CONNECTION_HPP_
#define SRC_NETWORK_CONNECTION_HPP_

#include <vector>

namespace network {

class Connection {
  public:
    virtual ~Connection(void) {};
    virtual void sendPacket(std::vector<uint8_t> packet) =0;
    virtual void process(void) = 0;

    uint16_t m_connection_id = 0;
};

} // namespace network

#endif /* SRC_NETWORK_CONNECTION_HPP_ */
