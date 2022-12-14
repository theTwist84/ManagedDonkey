#pragma once

#include "cseries/cseries.hpp"

template<typename t_type, long k_maximum_count>
struct c_static_stack
{
	long m_count;
	t_type stack[k_maximum_count];
};

struct s_start_menu_breadcrumb
{
	long __unknown0;
	long __unknown4;
};
static_assert(sizeof(s_start_menu_breadcrumb) == 0x8);

struct c_controller_input_message;
enum e_controller_index;
struct s_player_identifier;
struct s_service_record_identity;

struct c_start_menu_screen_widget
{
	static bool __fastcall handle_controller_input_message(void* _this, void* unused, c_controller_input_message* input_message);
	static bool __cdecl handle_global_start_button_press(c_controller_input_message* input_message);
	static bool __cdecl load_start_menu(e_controller_index controller_index, s_player_identifier* player_identifier, qword* player_xuid, s_service_record_identity* identity, s_start_menu_breadcrumb* breadcrumbs, long breadcrumb_count);
};
