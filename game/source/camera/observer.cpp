#include "camera/observer.hpp"

#include "cseries/console.hpp"
#include "memory/thread_local.hpp"

#include <assert.h>

s_observer* observer_get(long user_index)
{
	assert(user_index >= 0 && user_index < 4);

	s_thread_local_storage* tls = get_tls();

	return (tls && tls->g_observer_globals) ? &tls->g_observer_globals->observers[user_index] : nullptr;
}

s_observer_result const* observer_get_camera(long output_user_index)
{
	s_observer* observer = observer_get(output_user_index);
	assert(observer);

	return &observer->result;
}

s_observer_result const* __cdecl observer_try_and_get_camera(long output_user_index)
{
	return INVOKE(0x00613960, observer_try_and_get_camera, output_user_index);
}

