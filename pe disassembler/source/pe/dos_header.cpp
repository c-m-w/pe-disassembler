/// dos_header.cpp

#include "../pe disassembler.hpp"

dos_header::dos_header(void* base) :
	header<_IMAGE_DOS_HEADER>(base, 0)
{ 
	if (std::memcmp(&(*this)->e_magic, DOS_SIGNATURE, DOS_SIGNATURE_LENGTH))
		throw bad_pe();
}
