#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include "solution.h"

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
		char treeLine[1024];
		while (testFile.getline(treeLine, 1024))
		{
			std::string treeString(treeLine);
    		BinaryTree* testTree = new BinaryTree(treeString);

			int value = solution(testTree->GetTree());
			printf("Solution Value %d\n\n", value);
		}
	}
	else
		printf("Error: could not find or open %s\n", testFileName.c_str());

	testFile.close();

	return 0;
}

// Final time 9:37am