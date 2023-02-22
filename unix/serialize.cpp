/// serialize.cpp

#include <iostream>
#include <string>
#include <fstream>

#define BUILD_64
#include <pe disassembler.hpp>

std::vector<char> read_file(std::string const & file_name)
{
    std::ifstream file(file_name, std::ios::binary);
    std::vector<char> out {};

    file.seekg(0, std::ios::end);

    auto const size = file.tellg();

    file.seekg(0);
    out.resize(size);
    file.read(&out[0], size);

    return out;
}


int main(int argc, char ** argv)
{
	if (2 != argc)
		return std::cout << "invalid syntax" << std::endl, 1;

	auto const file = argv[1];
	auto data = read_file(file);	

	std::cout << data.size() << std::endl;

	nlohmann::json out { };
	
	try
	{
		auto mb = pe(&data[0], data.size());
		auto nt = mb.get_nt();
		
		out["success"] = true;
		out["data"] = mb.serialize();
	}
	catch( ... )
	{
		out["success"] = false;
	}

	std::cout << out.dump(4) << std::endl;

	return 0;
}
