/// image_export_table.hpp

#pragma once

class image_export;

class export_iterator
{
private:

	image_export* exports;
	unsigned i;

public:

	export_iterator(image_export* const exports, unsigned const i = 0);

	export_iterator& operator++();
	bool operator!=(const export_iterator& rhs);
	bool operator==(const export_iterator& rhs);
	std::pair<const char*, ptr_t> operator*();
};

class image_export : public rva<IMAGE_EXPORT_DIRECTORY>
{
private:

	rva<unsigned> function_table();
	rva<unsigned> name_table();

public:

	image_export(void* const base, ptr_t const offset);

	export_iterator begin();
	export_iterator end();

	friend class export_iterator;
};
