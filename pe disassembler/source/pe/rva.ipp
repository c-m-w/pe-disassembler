/// rva.ipp

#pragma once

#include "rva.hpp"

template<typename T>
inline rva<T>::rva(ptr_t base, ptr_t offset) :
	base(reinterpret_cast<void *>(base)), offset(offset)
{ }

template<typename T>
rva<T>::rva(void* const base, ptr_t offset) :
	base(base), offset(offset)
{ }

template<typename T>
T* rva<T>::operator->() const
{
	return reinterpret_cast<T*>(reinterpret_cast<ptr_t>(base) + offset);
}

template<typename T>
inline T& rva<T>::operator*() const
{
	return *reinterpret_cast<T*>(reinterpret_cast<ptr_t>(base) + offset);
}

template<typename T>
inline rva<T> rva<T>::operator[](unsigned const i) const
{
	return rva<T>(base, offset + i * sizeof(T));
}

template<typename T>
inline T* rva<T>::operator&() const
{
	return reinterpret_cast<T*>(reinterpret_cast<ptr_t>(base) + offset);
}

template<typename T>
inline rva<T>& rva<T>::operator++()
{
	return rva<T>(base, offset + sizeof(T));
}

template<typename T>
inline rva<T> rva<T>::operator+(unsigned const rhs) const
{
	return rva<T>(base, offset + sizeof(T) * rhs);
}

template<typename T>
inline bool rva<T>::operator==(const rva<T> rhs)
{
	return base == rhs.base && offset == rhs.offset;
}

template<typename T>
inline bool rva<T>::operator!=(const rva<T> rhs)
{
	return !(*this == rhs);
}

template<typename T>
inline bool rva<T>::operator!()
{
	return !base;
}

template<typename T>
inline void rva<T>::advance(ptr_t by)
{
	offset += by;
}
