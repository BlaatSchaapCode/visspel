/*
 * iconnection.hpp
 *
 *  Created on: 20 mrt. 2022
 *      Author: andre
 */

#pragma once

#include <vector>
#include <cstdint>

#include "protocol.hpp"

namespace network {

class Connection {
  public:
    virtual ~Connection(void){};
    virtual void sendPacket(std::vector<uint8_t> packet) = 0;
    virtual void process(void) = 0;

    uint16_t m_client_id = 0;
};

} // namespace network
