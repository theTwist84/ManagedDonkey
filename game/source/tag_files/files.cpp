#include "tag_files/files.hpp"

s_file_reference* __cdecl file_reference_agnostic_create(s_file_reference* file_reference, short location)
{
	return DECLTHUNK(0x00528500, file_reference_agnostic_create, file_reference, location);
}

s_file_reference* __cdecl file_reference_create_from_path(s_file_reference* file_reference, char const* path, bool a3)
{
	return DECLTHUNK(0x00528550, file_reference_create_from_path, file_reference, path, a3);
}

s_file_reference* __cdecl file_reference_copy(s_file_reference* file_reference, s_file_reference const* other)
{
	return DECLTHUNK(0x00528530, file_reference_copy, file_reference, other);
}

s_file_reference* __cdecl file_reference_add_directory(s_file_reference* file_reference, wchar_t const* directory)
{
	return DECLTHUNK(0x00528490, file_reference_add_directory, file_reference, directory);
}

//s_file_reference*__cdecl file_reference_remove_directory(s_file_reference* file_reference)

s_file_reference* __cdecl file_reference_set_name(s_file_reference* file_reference, char const* name)
{
	return DECLTHUNK(0x005288B0, file_reference_set_name, file_reference, name);
}

//s_file_reference* __cdecl file_reference_remove_name(s_file_reference*)
//long __cdecl find_files(unsigned long, s_file_reference const*, long, s_file_reference*)
//bool __cdecl file_is_readable(s_file_reference*, unsigned long*)
//void __cdecl file_trim(s_file_reference*, long)
//void* __cdecl file_read_into_memory_with_null_padding(s_file_reference*, unsigned long*, unsigned long)
//void* __cdecl file_read_into_memory(s_file_reference*, unsigned long*)
//bool __cdecl file_read_into_buffer(s_file_reference*, void*, unsigned long)
//void __cdecl file_printf(s_file_reference*, char const*, ...)
//void __cdecl file_vprintf(s_file_reference*, char const*, char*)