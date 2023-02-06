/// test.cpp

#include <fstream>
#include <iostream>
#include <cstring>
#include <vector>

int main()
{
	std::cout << "calling serialize..." << std::endl;

	auto const fp = popen("./serialize 'messagebox.dll'", "r");
	
	if (auto const fp = popen("./serialize 'messagebox.dll'", "r");
		nullptr != fp)
	{
		std::string buffer {};

		buffer.resize(128);
		std::memset(&buffer[0], 0, 128);

    	while (nullptr != fgets(&buffer[0], buffer.length(), fp))
        	std::cout << buffer << std::endl;

    	pclose(fp);
	}

	return 0;
}
