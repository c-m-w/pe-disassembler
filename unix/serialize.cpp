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
	nlohmann::json out { };
	
	if (2 != argc)
	{
		out["success"] = false;
		out["message"] = "error in program arguments";
		
		std::cout << out.dump(4) << std::endl;
		
		return 0;
	}

	auto const file = argv[1];
	auto data = read_file(file);	
	
	try
	{
		auto mb = pe(&data[0], data.size());
		auto nt = mb.get_nt();
		
		out["success"] = true;
		out["data"] = mb.serialize();
	}
	catch(bad_pe & e)
	{
		out["success"] = false;
		out["message"] = e.what();
	}
	catch(bad_architecture & e)
	{
		out["success"] = false;
		out["message"] = e.what();
	}

	std::cout << out.dump(4) << std::endl;

	return 0;
}
