#include "FileManager.h"
#include "Search.h"

namespace
{
	std::string INPUT_FILE = "input.txt";
	std::string OUTPUT_FILE = "output.txt";
}

void WriteResults(const std::vector<std::pair<size_t, size_t>> &coordinates);

int main()
{
	setlocale(LC_ALL, "");

	try
	{
		auto inputText = CFileManager::GetAllText(INPUT_FILE);
		auto pattern = inputText[0];
		auto textFileName = inputText[1];
		auto text = CFileManager::GetAllText(textFileName);
		auto coordinates = mlita::kmpSearch(text, pattern);
		WriteResults(coordinates);
	}
	catch (std::exception const& e)
	{
		std::cout << e.what();
		return 1;
	}
	
	return 0;
}

void WriteResults(const std::vector<std::pair<size_t, size_t>> &coordinates)
{
	if (coordinates.empty())
	{
		CFileManager::WriteAllText(OUTPUT_FILE, "No\n");
		return;
	}

	auto result = mlita::asText(coordinates, false);
	CFileManager::WriteAllText(OUTPUT_FILE, result);
}