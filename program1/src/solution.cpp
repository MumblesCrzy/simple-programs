#include <stdio.h>
#include <vector>

#include "solution.h"

int solution(std::string value)
{
	int max = 0;
	std::vector<std::string> pairs;
	while(!value.empty())
	{
		int place = value.find("-");
		if (place > 0)
		{
			std::string pair = value.substr(0, place);
			printf("pair %s\n", pair.c_str());
			pairs.push_back(pair);
			value.erase(0, place+1);
		}
		else if (place == std::string::npos)
			break;
	}

	int maxSoFar = 0;
	for (int i = 0; i < pairs.size(); i++)
	{
		std::string pair = pairs[i];
		int commaPlace = pair.find(',');
		std::string value1 = pair.substr(0, commaPlace);
		std::string value2 = pair.substr(commaPlace+1, pair.size());

		printf("Comparing: %s:%s\n", value1.c_str(), value2.c_str());

		if (value1.compare(value2) == 0)
		{
			++maxSoFar;
			printf("maxSoFar: %d\n", maxSoFar);
		}
		else
		{
			if (maxSoFar > max)
				max = maxSoFar;
			maxSoFar = 0;
		}

		if (maxSoFar > max)
			max = maxSoFar;
	}

	return max;
}