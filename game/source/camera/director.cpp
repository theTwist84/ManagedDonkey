#include "camera/director.hpp"

#include "camera/game_director.hpp"
#include "camera/saved_film_director.hpp"
#include "camera/observer_director.hpp"
#include "camera/debug_director.hpp"
#include "camera/editor_director.hpp"
#include "game/game.hpp"
#include "game/players.hpp"
#include "interface/first_person_weapons.hpp"

#include "memory/thread_local.hpp"

#include <string.h>

long __cdecl dead_or_alive_unit_from_user(long user_index)
{
	return INVOKE(0x005916F0, dead_or_alive_unit_from_user, user_index);
}

const char* k_director_mode_names[k_number_of_director_modes]
{
	"game",
	"saved_film",
	"observer",
	"debug",
	"unused",
	"editor"
};

const char* director_mode_get_name(e_director_mode director_mode)
{
	if (director_mode < _director_mode_game || director_mode >= k_number_of_director_modes)
		return "<invalid 'director_mode'>";

	return k_director_mode_names[director_mode];
}

e_director_mode director_mode_from_string(const char* str)
{
	e_director_mode director_mode = e_director_mode(-1);
	for (long i = _camera_mode_following; i < k_number_of_director_modes; i++)
	{
		if (strcmp(str, k_director_mode_names[i]) != 0)
			continue;

		director_mode = e_director_mode(i);
	}

	return director_mode;
}

inline s_director_globals* director_globals_get()
{
	s_thread_local_storage* tls = get_tls();

	return (tls && tls->director_globals && tls->director_globals->directors[0][0]) ? tls->director_globals : nullptr;
}

e_director_perspective c_director::get_perspective()
{
	if (!game_in_progress())
		return _director_perspective_3;
	e_director_perspective director_perspective = (e_director_perspective)get_camera()->get_perspective();
	if (!director_perspective)
		director_perspective = e_director_perspective(m_transition_time > 0.0);
	if (game_is_ui_shell())
		return _director_perspective_3;

	return director_perspective;
}

bool c_director::set_camera_mode_internal(e_camera_mode camera_mode, real transition_time, bool force_update)
{
	if (!can_use_camera_mode(camera_mode))
		return false;

	e_camera_mode current_camera_mode = get_camera()->get_type();

	bool result = camera_mode != current_camera_mode;
	if (result || force_update)
	{
		switch (camera_mode)
		{
		case _camera_mode_following:
			get_camera<c_following_camera>()->ctor(dead_or_alive_unit_from_user(m_user_index));
			break;
		case _camera_mode_orbiting:
			get_camera<c_orbiting_camera>()->ctor(dead_or_alive_unit_from_user(m_user_index));
			break;
		case _camera_mode_flying:
			get_camera<c_flying_camera>()->ctor(m_user_index);
			break;
		case _camera_mode_first_person:
			get_camera<c_first_person_camera>()->ctor(dead_or_alive_unit_from_user(m_user_index));
			break;
		case _camera_mode_dead:
			get_camera<c_dead_camera>()->ctor(m_user_index);
			break;
		case _camera_mode_static:
			get_camera<c_static_camera>()->ctor(m_user_index);
			break;
		case _camera_mode_scripted:
			get_camera<c_scripted_camera>()->ctor();
			break;
		case _camera_mode_authored:
			get_camera<c_authored_camera>()->ctor(m_user_index);
			break;
		}
		m_transition_time = transition_time;
	}

	e_director_perspective director_perspective = get_perspective();
	s_director_globals* director_globals = director_globals_get();
	if (director_globals->infos[m_user_index].director_perspective != director_perspective ||
		director_globals->infos[m_user_index].camera_mode != camera_mode)
	{
		director_globals->infos[m_user_index].director_perspective = director_perspective;
		director_globals->infos[m_user_index].camera_mode = camera_mode;
		first_person_weapon_perspective_changed(m_user_index);
	}

	return result || force_update;
}

template<typename t_type>
t_type* director_get(long user_index)
{
	if (!director_globals_get())
		return nullptr;

	return (t_type*)&director_globals_get()->directors[user_index];
}

s_director_info* director_get_info(long user_index)
{
	if (!director_globals_get())
		return nullptr;

	return &director_globals_get()->infos[user_index];
}

e_director_perspective director_get_perspective(long user_index)
{
	c_director* director = director_get(user_index);
	if (!director)
		return _director_perspective_3;

	return director->get_perspective();
}

void director_set_perspective(long user_index, e_director_perspective director_perspective)
{
	s_director_globals* director_globals = director_globals_get();
	if (director_globals->infos[user_index].director_perspective != director_perspective)
	{
		director_globals->infos[user_index].director_perspective = director_perspective;
		first_person_weapon_perspective_changed(user_index);
	}
}

void director_set_mode(long user_index, e_director_mode director_mode)
{
	switch (director_mode)
	{
	case _director_mode_game:
		director_get<c_game_director>(user_index)->ctor(user_index);
		break;
	case _director_mode_saved_film:
		director_get<c_saved_film_director>(user_index)->ctor(user_index);
		break;
	case _director_mode_observer:
		director_get<c_observer_director>(user_index)->ctor(user_index);
		break;
	case _director_mode_debug:
		director_get<c_debug_director>(user_index)->ctor(user_index);
		break;
	case _director_mode_editor:
		director_get<c_editor_director>(user_index)->ctor(user_index);
		break;
	}

	director_get_info(user_index)->director_mode = director_mode;
}

bool director_get_camera_third_person(long user_index)
{
	return director_get(user_index)->get_camera()->get_type() == _camera_mode_orbiting;
}

bool director_in_scripted_camera()
{
	s_thread_local_storage* tls = get_tls();

	return (tls && tls->director_camera_scripted) ? *tls->director_camera_scripted : false;
}

void director_toggle(long user_index, e_director_mode director_mode)
{
	static e_director_mode previous_mode = {};

	if (director_get_info(user_index)->director_mode == director_mode)
		director_mode = previous_mode;

	director_set_mode(user_index, director_mode);
}

void director_toggle_perspective(long user_index, e_director_perspective director_perspective)
{
	static e_director_perspective previous_mode = {};

	if (director_get_info(user_index)->director_perspective == director_perspective)
		director_perspective = previous_mode;

	director_set_perspective(user_index, director_perspective);
}

void director_toggle_camera(long user_index, e_camera_mode camera_mode)
{
	static e_camera_mode previous_mode = {};

	if (director_get_info(user_index)->camera_mode == camera_mode)
		camera_mode = previous_mode;

	director_get(user_index)->set_camera_mode(camera_mode, 0.0f);
}