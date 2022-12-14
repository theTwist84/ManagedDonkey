#pragma once

#include "cseries/cseries.hpp"
#include "tag_files/tag_group_definitions.hpp"

extern void __cdecl tag_load_missing_tags_report();

struct tag_block
{
	long count;
	byte(&elements)[];
	long : 32; // byte* definition;
};
static_assert(sizeof(tag_block) == 0xC);

struct tag_reference
{
	tag group_tag;
	long : 32; // char const* name;
	long : 32; // long name_length;
	long index;

	void* get_definition();
};
static_assert(sizeof(tag_reference) == 0x10);

struct tag_data
{
	long size;
	long : 32; //  flags;
	long : 32; // long stream_position;
	byte(&base)[];
	long : 32; // byte* definition;
};
static_assert(sizeof(tag_data) == 0x14);

template<typename t_element_type, dword ...t_extra>
//using c_typed_tag_block = tag_block;
struct c_typed_tag_block
{
	long count;
	t_element_type* elements;
	long : 32; // byte* definition;
};

template<tag ...k_group_tags>
using c_typed_tag_reference = tag_reference;

template<typename t_data_type, dword ...t_extra>
//using c_typed_tag_data = tag_data;
struct c_typed_tag_data
{
	long size;
	long : 32; // dword_flags flags;
	long : 32; // long stream_position;
	t_data_type* base;
	long : 32; // byte* definition;
};
