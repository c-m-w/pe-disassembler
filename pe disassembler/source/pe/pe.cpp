/// pe.cpp

#include "../pe disassembler.hpp"

pe::pe(void* const ptr, std::size_t const size)
{
	auto dos = dos_header(ptr);
	auto nt = nt_header(ptr, dos->e_lfanew);

	data = std::make_unique<unsigned char[]>(nt->OptionalHeader.SizeOfImage);

	std::memcpy(data.get(), ptr, nt->OptionalHeader.SizeOfHeaders);

	auto const delta = reinterpret_cast<std::uintptr_t>(data.get()) - nt->OptionalHeader.ImageBase;
	
	for (auto section: nt.get_sections())
	{
		auto sz = section->Name;

		if (0 == section->SizeOfRawData)
			continue;

		std::memcpy(data.get() + section->VirtualAddress,
					reinterpret_cast<unsigned char const*>(ptr) + section->PointerToRawData,
					section->SizeOfRawData);
	}

	auto new_nt = nt_header(data.get(), dos_header(data.get())->e_lfanew);

	for (auto reloc : new_nt.get_directory<image_base_relocations>())
		for (auto p : reloc)
		{
			if (!RELOC_FLAG32(*p))
				continue;

			auto patch = rva<DWORD>(data.get(), static_cast<ptr_t>(reloc->VirtualAddress) + (*p & 0xFFF));

			*patch += static_cast<DWORD>(delta);
		}

	if (!valid_pe())
		throw bad_pe();
}

bool pe::valid_pe()
{
	auto const dos = get_dos();
	
	if (0 != std::memcmp(&dos->e_magic, DOS_SIGNATURE, DOS_SIGNATURE_LENGTH))
		return false;

	auto const nt = get_nt();

	return 0 == std::memcmp(&nt->Signature, NT_SIGNATURE, NT_SIGNATURE_LENGTH);
}

dos_header pe::get_dos()
{
	return dos_header(data.get());
}

nt_header pe::get_nt()
{
	auto const dos = get_dos();

	return nt_header(data.get(), dos->e_lfanew);
}

#include <iostream>

nlohmann::json pe::serialize()
{
	nlohmann::json js { };

	auto dos	 = get_dos();
	auto nt		 = get_nt();
	auto imports = nt.get_directory<image_import_list>();
	auto exports = nt.get_directory<image_export>();
	auto relocs  = nt.get_directory<image_base_relocations>();

	std::time_t time = nt->FileHeader.TimeDateStamp;

	js["nt"]["image_base"] = nt->OptionalHeader.ImageBase;
	js["nt"]["image_size"] = nt->OptionalHeader.SizeOfImage;
	js["nt"]["build_time"] = std::asctime(std::localtime(&time));
	js["nt"]["entry_point"] = nt->OptionalHeader.AddressOfEntryPoint;

	for (auto s : nt.get_sections())
	{
		nlohmann::json section{ };

		std::cout << std::hex << (ptr_t)s->Name << std::endl;
		section["name"] = std::string(reinterpret_cast<const char*>(s->Name));
		section["size"] = s->SizeOfRawData;
		section["rva"] = s->VirtualAddress;

		js["sections"].push_back(section);
	}

	for (auto e : exports)
	{
		nlohmann::json exp { };

		std::cout << "here" << std::endl;
		std::cout << std::hex << (ptr_t)e.first << std::endl;
		exp["name"] = std::string(e.first);
		exp["rva"] = e.second;

		js["exports"].push_back(exp);
	}
	
	for (auto i : imports)
	{
		nlohmann::json import{ };

		import["module"] = std::string(i.name());

		for (auto t : i)
		{
			auto const name = t.name();
			import["list"].push_back(nullptr == name ? "failed to resolve" : std::string(name));
		}

		js["imports"].push_back(import);
	}

	for (auto r : relocs)
	{
		nlohmann::json reloc {};

		reloc["rva"] = r->VirtualAddress;
		reloc["entries"] = r.entries();

		js["relocations"].push_back(reloc);
	}

	return js;
}
