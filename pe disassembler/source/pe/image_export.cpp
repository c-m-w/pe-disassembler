/// image_export.cpp

#include "../pe disassembler.hpp"

export_iterator::export_iterator(image_export* const exports, unsigned const i) :
	exports(exports), i(i)
{ }

export_iterator& export_iterator::operator++()
{
	i++;
	return *this;
}

bool export_iterator::operator!=(const export_iterator& rhs)
{
	return i != rhs.i;
}

bool export_iterator::operator==(const export_iterator& rhs)
{
	return i == rhs.i;
}

std::pair<const char*, ptr_t> export_iterator::operator*()
{
	return std::make_pair<const char*, ptr_t>(
		reinterpret_cast<const char*>((ptr_t)exports->base + (ptr_t)*exports->name_table()[i]),
		std::move(*exports->function_table()[i]));
}

rva<unsigned> image_export::function_table()
{
	return rva<unsigned>(base, (*this)->AddressOfFunctions);
}

rva<unsigned> image_export::name_table()
{
	return rva<unsigned>(base, (*this)->AddressOfNames);
}

image_export::image_export(void* const base, ptr_t const offset) :
	rva<IMAGE_EXPORT_DIRECTORY>(base, offset)
{ }

export_iterator image_export::begin()
{
	return export_iterator(this, 0);
}

export_iterator image_export::end()
{
	return export_iterator(this, (*this)->NumberOfNames);
}
