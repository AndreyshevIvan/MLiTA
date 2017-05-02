#include "FileManager.h"
#include "Search.h"

namespace
{
	std::string INPUT_FILE = "input.txt";
	std::string OUTPUT_FILE = "output.txt";
}

int main()
{
	setlocale(LC_ALL, "");

	try
	{
		auto inputText = CFileManager::GetAllText(INPUT_FILE);
		auto pattern = inputText[0];
		auto textFileName = inputText[1];
		auto text = CFileManager::GetAllText(textFileName);

		auto result = mlita::kmp_search(text, pattern);
		CFileManager::WriteAllText(OUTPUT_FILE, inputText);
	}
	catch (std::exception const& e)
	{
		std::cout << e.what();
		return 1;
	}
	
	return 0;
}