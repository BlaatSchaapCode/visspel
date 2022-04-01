/*
 * protocol.cpp
 *
 *  Created on: 30 mrt. 2022
 *      Author: andre
 */

#include "protocol.hpp"

#include <functional>
#include <map>
#include <string>
#include <vector>

#include "connection.hpp"

#include "../utils/logger.hpp"

namespace network {

std::map<MessageType, std::function<void(Connection *, Header, std::vector<uint8_t>)>> protocol_handlers;

void request_info() {}

void set_connection_id_handler(Connection *c, Header h, std::vector<uint8_t> d) {
    switch (h.action) {
    case MessageAction::Request_Get:
    	// NOT IMPLEMENTED
    	send_status(c,h.type, MessageStatus::ERROR_NOT_IMPLEMENTED, h.id);
        break;
    case MessageAction::Request_Set:
        if (d.size() == sizeof(client_id_t)) {
            client_id_t client_id = *(client_id_t *)(d.data());
            c->m_client_id = client_id;
            LOG_INFO("We are assigned client ID %d", client_id);
            send_status(c,h.type, MessageStatus::OK, h.id);
            break;
        }
        break;
    case MessageAction::Response_Status:
    	LOG_INFO("Connection ID Status received:  %02X", h.status);
    	break;
    case MessageAction::Response_Data:
    	// NOT IMPLEMENTED
    	// As Request_Get is not implemented, parsing the response to
    	// such request is not implemented either
    	break;
    default:
    	send_status(c,h.type, MessageStatus::ERROR_BAD_ACTION, h.id);
        break;
    }
}

void send_status(Connection *con, MessageType type, MessageStatus status, MessageId id) {
	Header message;
	message.size = sizeof(message);
	message.type = type;
	message.action = MessageAction::Response_Status;
	message.status = status;
	message.id = id;

    std::vector<uint8_t> mess((uint8_t *)&message, ((uint8_t *)&message) + sizeof(message));
    con->sendPacket(mess);
}

void set_connection_id(Connection *con) {
    LOG_INFO("Sending Set Connection ID to client");
    struct {
        Header header;
        client_id_t client_id;
    } message;

    message.header.size = sizeof(message);
    message.header.type = MessageType::Connection_Id;
    message.header.action = MessageAction::Request_Set;
    message.header.status = MessageStatus::OK;

    message.client_id = con->m_client_id;

    std::vector<uint8_t> mess((uint8_t *)&message, ((uint8_t *)&message) + sizeof(message));
    con->sendPacket(mess);
}

void parse(std::vector<uint8_t> received_data, Connection *connection) {
    LOG_DEBUG("Received data: ");
    std::string hex;
    char hexval[6];
    for (size_t i = 0; i < received_data.size(); i++) {
        sprintf(hexval, "0x%02X ", received_data[i]);
        hex += hexval;
    }
    LOG_DEBUG(hex.c_str());

    // What is the proper C++ way? I'm a C coder...
    size_t size = received_data.size();
    uint32_t offset = 0;
    if (size < sizeof(Header))
        return;

    Header *header = (Header *)received_data.data();
    while (header->size && (header->size + offset) <= size) {
        LOG_DEBUG("Received packet type %04X of %3d bytes", header->type, header->size);
        std::vector<uint8_t> payload(received_data.data() + offset + sizeof(Header), received_data.data() + offset + header->size);

        LOG_INFO("Received payload (%d bytes): ", payload.size());
        hex.clear();
        for (size_t i = 0; i < payload.size(); i++) {
            sprintf(hexval, "0x%02X ", payload[i]);
            hex += hexval;
        }
        LOG_DEBUG("%s", hex.c_str());

        auto search = protocol_handlers.find(header->type);
        if (search != protocol_handlers.end()) {
            LOG_INFO("This was a client connection");
            search->second(connection, *header, payload);
        } else {
            LOG_ERROR("Message Type Handler not registered");

            // Is this desirable, a bad packet may bounce up and forth forever this way
            // We should filter on MessageAction to be "(action & 0xF0) == 0x10"
            // Can we keep using class enum and do such a thing?
            send_status(connection, header->type, MessageStatus::ERROR_BAD_TYPE, header->id);
        }

        offset += header->size;
        header = (Header *)received_data.data() + offset;
    }
}

void protocol_init(void) { protocol_handlers[MessageType::Connection_Id] = set_connection_id_handler; }

} // namespace network
