/// nt_header.cpp

#include "../pe disassembler.hpp"

nt_header::nt_header(void* const base, unsigned long const e_lfanew) :
	header<IMAGE_NT_HEADERS32>(base, e_lfanew)
{
	if (std::memcmp(&(*this)->Signature, NT_SIGNATURE, NT_SIGNATURE_LENGTH))
		throw std::runtime_error("bad NT header");

	if (*(reinterpret_cast<unsigned char*>(&(*this)->Signature) + 4) != NT_32_SIGNATURE)
		throw std::runtime_error("not 32 bit");
}

section_list nt_header::get_sections()
{
	return section_list(reinterpret_cast<void *>(base), offset + sizeof(IMAGE_NT_HEADERS32), (*this)->FileHeader.NumberOfSections);
}
