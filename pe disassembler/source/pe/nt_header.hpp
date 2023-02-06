/// nt_header.hpp

#pragma once

class nt_header;

template<typename T>
class directory_wrapper
{ };

template<>
class directory_wrapper<image_export>
{
private:

	nt_header* parent;

public:

	directory_wrapper(nt_header* parent);

	image_export operator*();
};

template<>
class directory_wrapper<image_import_list>
{
private:

	nt_header* parent;

public:

	directory_wrapper(nt_header* parent);

	image_import_list operator*();
};

template<>
class directory_wrapper<image_base_relocations>
{
private:

	nt_header* parent;

public:

	directory_wrapper(nt_header* parent);

	image_base_relocations operator*();
};

class nt_header: public header<IMAGE_NT_HEADERS32>
{
public:

	nt_header(void* const base, unsigned long const e_lfanew);

	template<typename T>
	T get_directory();

	section_list get_sections();

	template<typename T>
	friend class directory_wrapper;
};

#include "nt_header.ipp"
