#pragma once

#include "cseries/cseries.hpp"

#include "networking/logic/network_search.hpp"
#include "networking/messages/network_message_type_collection.hpp"

struct s_network_message_broadcast_search
{
	word protocol_version;
	qword nonce;
};
static_assert(sizeof(s_network_message_broadcast_search) == 0x10);

struct s_network_message_broadcast_reply
{
	word protocol_version;
	qword search_nonce;
	s_network_session_status_data status_data;
};
static_assert(sizeof(s_network_message_broadcast_reply) == 0x164D0);

struct c_network_link;
struct c_network_message_gateway;
struct s_available_session;

struct s_broadcast_search_globals
{
	bool initialized;
	byte : 8;
	byte : 8;
	byte : 8;

	c_network_link* link;
	c_network_message_gateway* message_gateway;

	bool search_active;

	// new status data
	bool __unknownD;
	byte : 8;
	byte : 8;

	dword search_time;
	byte : 8;
	byte : 8;
	byte : 8;
	byte : 8;

	qword search_nonce;
	long maximum_session_count;
	s_available_session* available_sessions;
};
static_assert(sizeof(s_broadcast_search_globals) == 0x28);

extern s_broadcast_search_globals& g_broadcast_search_globals;

struct transport_address;

extern bool __cdecl network_broadcast_search_active(qword* search_nonce);
extern bool __cdecl network_broadcast_search_begin(long controller_index, long maximum_session_count, s_available_session* session_storage);
extern void __cdecl network_broadcast_search_dispose();
extern void __cdecl network_broadcast_search_end();
extern void __cdecl network_broadcast_search_handle_reply(transport_address const* address, s_network_message_broadcast_reply const* message);
extern bool __cdecl network_broadcast_search_initialize(c_network_link* link, c_network_message_gateway* message_gateway);
extern void __cdecl network_broadcast_search_update();

