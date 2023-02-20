/// rva.hpp

#pragma once

#if defined(BUILD_32)

using ptr_t = unsigned long;

#else

using ptr_t = unsigned long long;

#endif

template<typename T>
class rva
{
protected:

	void * base;
	ptr_t offset;

public:

	rva(ptr_t base, ptr_t offset);
	rva(void * const base, ptr_t offset);

	T* operator->() const;
	T& operator*() const;
	rva<T> operator[](unsigned const i) const;
	T* operator&() const;

	rva<T>& operator++();
	rva<T> operator+(unsigned const rhs) const;

	bool operator==(const rva<T> rhs);
	bool operator!=(const rva<T> rhs);
	bool operator!();

	void advance(ptr_t by);
};

#include "rva.ipp"
