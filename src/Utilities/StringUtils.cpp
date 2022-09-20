#include "StringUtils.h"

namespace StringUtils
{
	std::vector<std::string> Split(std::string& s, const char* delim)
	{
		std::vector<std::string> res;

		size_t start = 0;
		size_t indexToSplit = s.find_first_of(delim);
		while (indexToSplit <= std::string::npos)
		{
			res.emplace_back(s.substr(start, indexToSplit));

			if (indexToSplit == std::string::npos)
				break;

			start = indexToSplit + 1;
			indexToSplit = s.find_first_of(delim, start);
		}

		return res;
	}
}