/// except.hpp

#pragma once

template<const char * M>
class pe_except : public std::runtime_error
{
public:

	pe_except();
};

constexpr char BAD_PE_MESSAGE[] = "file is not a valid PE format";

class bad_pe : public pe_except<BAD_PE_MESSAGE>
{ };

constexpr char BAD_ARCHITECTURE_MESSAGE[] = "file is not 32-bit PE";

class bad_architecture : public pe_except<BAD_ARCHITECTURE_MESSAGE>
{ };

#include "except.ipp"
