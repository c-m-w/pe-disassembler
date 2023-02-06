/// nt_header.ipp

#include "../pe disassembler.hpp"
#include "nt_header.hpp"

#pragma once

inline directory_wrapper<image_export>::directory_wrapper(nt_header* parent) :
	parent(parent)
{ }

inline image_export directory_wrapper<image_export>::operator*()
{
	return image_export(
		reinterpret_cast<void*>(parent->base),
		(*parent)->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress);
}


inline directory_wrapper<image_import_list>::directory_wrapper(nt_header* parent) :
	parent(parent)
{ }

inline image_import_list directory_wrapper<image_import_list>::operator*()
{
	return image_import_list(
		reinterpret_cast<void*>(parent->base),
		(*parent)->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT].VirtualAddress);
}


inline directory_wrapper<image_base_relocations>::directory_wrapper(nt_header* parent) :
	parent(parent)
{ }

inline image_base_relocations directory_wrapper<image_base_relocations>::operator*()
{
	return image_base_relocations(
		reinterpret_cast<void*>(parent->base),
		(*parent)->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC].VirtualAddress);
}

template<typename T>
inline T nt_header::get_directory()
{
	return *directory_wrapper<T>(this);
}
