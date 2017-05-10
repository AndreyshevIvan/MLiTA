#pragma once
#include <locale>

#define _MLITA_LOCAL_BEGIN	namespace {
#define _MLITA_LOCAL_END	}

#define _MLITA_BEGIN	namespace mlita {
#define _MLITA_END	}

_MLITA_BEGIN

typedef std::vector<std::string> Text;
typedef std::vector<size_t> StrCoords;
typedef std::vector<std::pair<size_t, size_t>> TextCoords;

static TextCoords kmpSearch(const Text &text, const std::string &pattern);
static StrCoords getPrefixArr(const std::string &lineToScan);
static Text asText(const TextCoords &coordinates, bool isStartFromZero);

_MLITA_LOCAL_BEGIN

TextCoords toTextCoordinates(const Text &srcText, StrCoords patternCoords);
StrCoords calculatePatternCoords(const std::string &srcText, const std::string &pattern, const StrCoords &prefixArr);
bool isEqual(char ch1, char ch2);

bool isEqual(char ch1, char ch2)
{
	return tolower(ch1) == tolower(ch2);
};

TextCoords toTextCoordinates(const Text &srcText, StrCoords patternCoords)
{
	TextCoords coordinates;
	size_t strNum = 0;
	size_t chNum = 0;

	while (!patternCoords.empty())
	{
		size_t topCoordinate = patternCoords.front();
		patternCoords.erase(patternCoords.begin());

		for (strNum; strNum < srcText.size(); strNum++)
		{
			const auto &currStr = srcText[strNum];
			const auto &lastNum = (currStr.size() == 0) ? 0 : currStr.size() - 1;
			const auto &eolnCh = (currStr[lastNum] == ' ') ? 0 : 1;

			if (chNum + srcText[strNum].size() + eolnCh > topCoordinate)
			{
				const auto &chCoordinate = topCoordinate - chNum;
				coordinates.push_back(std::make_pair(strNum, chCoordinate));
				break;
			}

			chNum += srcText[strNum].size() + eolnCh;
		}
	}

	return coordinates;
}

StrCoords calculatePatternCoords(const std::string &srcText, const std::string &pattern, const StrCoords &prefixArr)
{
	StrCoords coordinates;
	size_t patternChPos = 0;

	for (size_t i = 0; i < srcText.size(); i++)
	{
		char textCh = srcText[i];
		while (patternChPos > 0 && !isEqual(pattern[patternChPos], textCh))
		{
			patternChPos = prefixArr[patternChPos];
		}

		if (isEqual(pattern[patternChPos], textCh))
		{
			patternChPos++;
		}

		if (patternChPos == pattern.size() - 1)
		{
			coordinates.push_back(i - pattern.size() + 2);
			patternChPos = prefixArr[patternChPos - 1];
		}
	}

	return coordinates;
}

_MLITA_LOCAL_END

TextCoords kmpSearch(const Text &text, const std::string &pattern)
{
	if (pattern == "")
	{
		throw CInputException("Pattern is empty!");
	}

	std::string allTextStr;

	for (auto str : text)
	{
		const size_t lastNum = (str.size() == 0) ? 0 : str.size() - 1;
		const std::string addStr = (str[lastNum] == ' ') ? str : (str + ' ');
		allTextStr += addStr;
	}

	auto prefixArr = getPrefixArr(pattern);
	auto patternCoords = calculatePatternCoords(allTextStr, pattern, prefixArr);

	return toTextCoordinates(text, patternCoords);
}

StrCoords getPrefixArr(const std::string &lineToScan)
{
	StrCoords prefixArray(lineToScan.size(), 0);

	for (size_t chNum = 1; chNum < lineToScan.size(); chNum++)
	{
		size_t lastPrefix = prefixArray[chNum - 1];
		const char &scanCh = lineToScan[chNum];

		while ((lastPrefix > 0) && !isEqual(scanCh, lineToScan[lastPrefix]))
		{
			lastPrefix = prefixArray[lastPrefix - 1];
		}

		if (isEqual(lineToScan[chNum], lineToScan[lastPrefix]))
		{
			lastPrefix++;
		}

		prefixArray[chNum] = lastPrefix;
	}

	return prefixArray;
}

static Text asText(const TextCoords &coordinates, bool isStartFromZero)
{
	Text result;

	for (auto element : coordinates)
	{
		if (!isStartFromZero)
		{
			element.first++;
			element.second++;
		}

		std::string line = std::to_string(element.first);
		line += " " + std::to_string(element.second);
		result.push_back(line);
	}

	return result;
}

_MLITA_END
