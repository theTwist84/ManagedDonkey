#include "networking/logic/network_session_interface.hpp"

#include "cseries/console.hpp"
#include "networking/logic/network_life_cycle.hpp"
#include "networking/session/network_session.hpp"
#include "networking/session/network_session_parameter_type_collection.hpp"

REFERENCE_DECLARE(0x019A0328, s_network_session_interface_globals, session_interface_globals);

long __cdecl network_squad_session_get_countdown_timer()
{
	FUNCTION_BEGIN(true);

	c_network_session* active_squad_session = nullptr;
	if (network_life_cycle_in_squad_session(&active_squad_session) && active_squad_session->established())
	{
		c_network_session_parameters* parameters = active_squad_session->get_session_parameters();
		c_network_session_parameter_countdown_timer* countdown_timer = 
			static_cast<c_network_session_parameter_countdown_timer*>(parameters->m_parameter_interfaces[_network_session_parameter_type_countdown_timer]);
		return countdown_timer->get_countdown_timer();
	}

    return -1;
}

void __cdecl network_session_interface_handle_message(long session_network_message)
{
	FUNCTION_BEGIN(true);

	INVOKE(0x004365D0, network_session_interface_handle_message, session_network_message);
}
