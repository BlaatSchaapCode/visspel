/*
 * protocol.cpp
 *
 *  Created on: 30 mrt. 2022
 *      Author: andre
 */

#include "protocol.hpp"

#include <vector>

#include "connection.hpp"

namespace network {

void request_info() {}

void set_connection_id(Connection *con) {
	struct {
		visspel_network_header_t header;
		visspel_network_connection_id_t connection_id;
	} message;

	message.header.size = sizeof(message);
	message.header.type = MessageType::Info;
	message.header.action = MessageAction::Request_Set;
	message.header.status = MessageStatus::OK;

	message.connection_id.network_id = con->m_connection_id;

	std::vector<uint8_t> mess((uint8_t *)&message, ((uint8_t *)&message) + sizeof(message));
	con->sendPacket(mess);
}

} // namespace network
