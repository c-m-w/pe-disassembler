/// image_base_relocations.cpp

#include "../pe disassembler.hpp"

block_table_entry::block_table_entry(void* const base, ptr_t const offset) :
	rva<WORD>(base, offset)
{ }

block_table_entry::block_table_entry(rva<WORD> const& rhs) :
	rva<WORD>(rhs)
{ }

block_table_iterator::block_table_iterator(void* const base, ptr_t const offset,  unsigned const i) :
	rva<WORD>(base, offset), i(i)
{ }

block_table_entry block_table_iterator::operator*()
{
	return block_table_entry(reinterpret_cast<void *>(base), offset);
}

block_table_iterator& block_table_iterator::operator++()
{
	i++;
	advance(sizeof(WORD));

	return *this;
}

bool block_table_iterator::operator!=(block_table_iterator const& rhs)
{
	return i != rhs.i;
}

block_table::block_table(void* const base, ptr_t const offset) :
	rva<IMAGE_BASE_RELOCATION>(base, offset)
{ }

block_table::block_table(rva<IMAGE_BASE_RELOCATION> const& rhs) :
	rva<IMAGE_BASE_RELOCATION>(rhs)
{ }

std::size_t block_table::entries()
{
	return ((*this)->SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION)) / sizeof(WORD);
}

block_table_iterator block_table::begin()
{
	return block_table_iterator(reinterpret_cast<void *>(base), offset + sizeof(IMAGE_BASE_RELOCATION));
}

block_table_iterator block_table::end()
{
	auto const e = entries();

	return block_table_iterator(reinterpret_cast<void *>(base), offset + sizeof(IMAGE_BASE_RELOCATION) + sizeof(WORD) * e, e);
}

image_base_relocations::image_base_relocations(void* const base, ptr_t const offset) :
	rva<IMAGE_BASE_RELOCATION>(base, offset)
{ }

image_base_relocations::image_base_relocations(rva<IMAGE_BASE_RELOCATION> const rhs) :
	rva<IMAGE_BASE_RELOCATION>(rhs)
{ }

block_iterator<rva<IMAGE_BASE_RELOCATION>> image_base_relocations::begin()
{
	return block_iterator<rva<IMAGE_BASE_RELOCATION>>(reinterpret_cast<void *>(base), offset);
}

block_iterator<IMAGE_BASE_RELOCATION> image_base_relocations::end()
{
	return block_iterator<IMAGE_BASE_RELOCATION>();
}
