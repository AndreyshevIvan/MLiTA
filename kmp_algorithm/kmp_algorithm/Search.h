#pragma once

#define _MLITA_LOCAL_BEGIN	namespace {
#define _MLITA_LOCAL_END	}

#define _MLITA_BEGIN	namespace mlita {
#define _MLITA_END	}

_MLITA_BEGIN

_MLITA_LOCAL_BEGIN

const char KMP_SEPARATOR = '@';

_MLITA_LOCAL_END

typedef std::vector<std::string> Text;

static std::vector<size_t> prefix_func(const std::string &lineToScan);
static Text kmp_search(const Text &text, const std::string &pattern);

Text kmp_search(const Text &text, const std::string &pattern)
{
	std::string allTextStr = pattern + KMP_SEPARATOR;

	for (auto str : text)
	{
		allTextStr += (str + " ");
	}

	auto prefixArray = prefix_func(allTextStr);

	Text newText;
	return newText;
}
std::vector<size_t> prefix_func(const std::string &lineToScan)
{
	size_t length = lineToScan.length();
	std::vector<size_t> prefixArray(length);

	for (size_t i = 1; i < length; i++)
	{
		size_t lastPrefix = prefixArray[i - 1];
		while ((lastPrefix > 0) && (lineToScan[i] != lineToScan[lastPrefix]))
		{
			lastPrefix = prefixArray[lastPrefix - 1];
		}

		if (lineToScan[i] == lineToScan[lastPrefix])
		{
			lastPrefix++;
		}

		prefixArray[i] = lastPrefix;
	}

	return prefixArray;
}

_MLITA_END
