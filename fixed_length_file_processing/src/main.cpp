#include <stdio.h>
#include <string>

#include "file_processing.h"

int main(int argc, char const* argv[])
{
	std::string testFileName = "TestFile.txt";

	if (argc == 2)
	{
		testFileName = argv[1];
	}

    printf("Using test file %s\n", testFileName.c_str());
	fileProcessing(testFileName);

	return 0;
}
