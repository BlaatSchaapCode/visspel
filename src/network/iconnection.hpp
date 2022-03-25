/*
 * iconnection.hpp
 *
 *  Created on: 20 mrt. 2022
 *      Author: andre
 */

#ifndef SRC_NETWORK_ICONNECTION_HPP_
#define SRC_NETWORK_ICONNECTION_HPP_

namespace network {

class iConnection {
  public:
    // virtual ~iConnection(void) = 0;
    virtual void sendPacket(void) = 0;
    virtual void process(void) = 0;
};

} // namespace network

#endif /* SRC_NETWORK_ICONNECTION_HPP_ */
