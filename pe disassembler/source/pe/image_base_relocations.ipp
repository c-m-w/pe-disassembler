/// image_base_relocations.ipp

#pragma once

#include "../pe disassembler.hpp"

inline block_iterator<IMAGE_BASE_RELOCATION>::block_iterator() :
	IMAGE_BASE_RELOCATION({})
{ }

inline block_iterator<IMAGE_BASE_RELOCATION>::block_iterator(IMAGE_BASE_RELOCATION&& rhs) :
	IMAGE_BASE_RELOCATION(rhs)
{ }

inline block_iterator<rva<IMAGE_BASE_RELOCATION>>::block_iterator(void* const base, unsigned long const offset) :
	rva<IMAGE_BASE_RELOCATION>(base, offset)
{ }

inline block_iterator<rva<IMAGE_BASE_RELOCATION>>::block_iterator(rva<IMAGE_BASE_RELOCATION> const& rhs) :
	rva<IMAGE_BASE_RELOCATION>(rhs)
{ }

inline block_table block_iterator<rva<IMAGE_BASE_RELOCATION>>::operator*()
{
	return block_table(reinterpret_cast<void *>(base), offset);
}

inline block_iterator<rva<IMAGE_BASE_RELOCATION>>& block_iterator<rva<IMAGE_BASE_RELOCATION>>::operator++()
{
	advance((*this)->SizeOfBlock);

	return *this;
}

inline bool block_iterator<rva<IMAGE_BASE_RELOCATION>>::operator!=(block_iterator<IMAGE_BASE_RELOCATION> const& rhs)
{
	return (*this)->VirtualAddress != rhs.VirtualAddress;
}
