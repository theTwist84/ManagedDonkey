#pragma once

#include "cseries/cseries.hpp"

struct s_file_last_modification_date
{
	dword low;
	dword hi;
};
static_assert(sizeof(s_file_last_modification_date) == 0x8);

struct s_file_handle
{
	void* handle;
};
static_assert(sizeof(s_file_handle) == 0x4);