#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include "prefix_suffix.h"

int main(int argc, char const* argv[])
{
	std::string testFileName = "TestFile.txt";

	if (argc == 2)
	{
		testFileName = argv[1];
	}

    printf("Using test file %s\n", testFileName.c_str());

	std::ifstream testFile;
	testFile.open(testFileName.c_str());
	if (testFile.is_open())
	{
		printf("\n");
		char test[1024];
		while (testFile.getline(test, 1024))
		{
			std::string testString(test);
			int value = solution(testString);

			printf("Return Value %d\n\n", value);
		}
	}
	else
		printf("Error: could not find or open %s\n", testFileName.c_str());

	testFile.close();

	return 0;
}

// Final time 9:37am