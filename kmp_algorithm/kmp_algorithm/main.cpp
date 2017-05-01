#include "FileManager.h"

namespace
{
	std::string INPUT_FILE = "input.txt";
	std::string OUTPUT_FILE = "output.txt";
}

int main()
{
	try
	{
		CFileManager fileManager(INPUT_FILE, OUTPUT_FILE);

		auto text = {
			std::string("Hello, "),
			std::string("World")
		};

		fileManager.WriteAllText(text);
	}
	catch (std::exception const& e)
	{
		std::cout << e.what();
		return 1;
	}
	
	return 0;
}