/*
 * protocol.hpp
 *
 *  Created on: 30 mrt. 2022
 *      Author: andre
 */

#ifndef SRC_NETWORK_PROTOCOL_HPP_
#define SRC_NETWORK_PROTOCOL_HPP_

#include "connection.hpp"
#include <cstdint>
#include <vector>

namespace network {

#pragma pack(push, 1)

enum class MessageType : uint16_t {
    Info = 0x00,
    Connection_Id = 0x01,
};

enum class MessageAction : uint8_t {
    Request_Get = 0x10,
    Request_Set = 0x11,

    Response_Data = 0x20,
    Response_Status = 0x21,
};

enum class MessageStatus : uint8_t {
    OK = 0x00,
};

typedef struct {
    uint16_t size;
    MessageType type;
    MessageAction action;
    MessageStatus status;
    uint16_t request_id;
} Header;

typedef uint16_t client_id_t;

#pragma pack(pop)

void parse(std::vector<uint8_t> received_data, Connection *connection);
void set_connection_id(Connection *con);

void protocol_init(void);

} // namespace network

#endif /* SRC_NETWORK_PROTOCOL_HPP_ */
