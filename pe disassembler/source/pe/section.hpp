/// section.hpp

#pragma once

class section_list;

class section : public rva<IMAGE_SECTION_HEADER>
{
public:

	section(void* const base, ptr_t const offset);
	section(rva<IMAGE_SECTION_HEADER> const rhs);
};

class section_iterator
{
private:

	section_list* list;
	unsigned i;

public:

	section_iterator(section_list* const list, unsigned const i = 0u);

	section operator*();
	section_iterator& operator++();
	bool operator!=(section_iterator const& rhs);
};

class section_list : public rva<IMAGE_SECTION_HEADER>
{
private:

	unsigned const n;

public:

	section_list(void* const base, ptr_t const offset, unsigned const n);

	section_iterator begin();
	section_iterator end();

	friend class section_iterator;
};
