/// section.cpp

#include "../pe disassembler.hpp"

section::section(void* const base, unsigned long const offset) :
	rva<IMAGE_SECTION_HEADER>(base, offset)
{ }

section::section(rva<IMAGE_SECTION_HEADER> const rhs) :
	rva<IMAGE_SECTION_HEADER>(rhs)
{ }

section_list::section_list(void* const base, unsigned long const offset, unsigned const n) :
	rva<IMAGE_SECTION_HEADER>(base, offset), n(n)
{ }

section_iterator section_list::begin()
{
	return section_iterator(this);
}

section_iterator section_list::end()
{
	return section_iterator(this, n);
}

section_iterator::section_iterator(section_list* const list, unsigned const i) :
	list(list), i(i)
{ }

section section_iterator::operator*()
{
	return section(reinterpret_cast<void *>(list->base), list->offset + i * sizeof(IMAGE_SECTION_HEADER));
}

section_iterator& section_iterator::operator++()
{
	i++;

	return *this;
}

bool section_iterator::operator!=(section_iterator const& rhs)
{
	return i != rhs.i;
}
