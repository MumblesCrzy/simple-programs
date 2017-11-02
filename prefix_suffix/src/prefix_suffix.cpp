#include <stdio.h>

#include "prefix_suffix.h"

// Start time 8:30 am
int solution(std::string &test)
{
	int retVal = 0;
	printf("Test value: %s\n", test.c_str());

	for (int i = test.size()-1; i >= 1; i--)
	{
		// printf("round %d\n", i);
		std::string prefix = test.substr(0, i);
		//printf("Prefix value: %s\n", prefix.c_str());

		int length = test.find(prefix.c_str(), test.size()-prefix.size(), prefix.size());

		if (length != std::string::npos)
		{
			//printf("length %d\n", length);
			retVal = test.size() - length;
			break;
		}
	}

	return retVal;
}
// End time 8:52