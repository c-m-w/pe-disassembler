/// except.ipp

#pragma once

#include "except.hpp"

template<const char* M>
inline pe_except<M>::pe_except() :
	std::runtime_error(M)
{ }
