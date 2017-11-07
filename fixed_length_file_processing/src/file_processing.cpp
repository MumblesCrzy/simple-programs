// Reddit daily programmer, easy challenge 
// www.reddit.com/r/dailyprogrammer/comments/7b5u96/20171106_challenge_339_easy_fixedlength_file/
// Favored cout over printf. Learned about imbue/locale number formatting on streams
// Trimmed name, but not other fields since it doesn't show in output
// Relied on atoi for dropping leading o's on numbers
// Not very robust code. Could see a few places it might fail


#include <fstream>
#include <iostream>
#include <locale>
#include <map>
#include <stdlib.h> 
#include <vector>

#include "file_processing.h"

struct Person
{
	int Age;
	std::string Name;
	std::string Birthday;
	std::map<std::string, std::string> extensions;
};

void fileProcessing(std::string testFileName)
{
	std::cout.imbue(std::locale(""));
	int index = -1;
	std::vector<Person*> people;

	std::ifstream testFile;
	testFile.open(testFileName.c_str());
	if (testFile.is_open())
	{
		printf("\n");
		char test[256];
		while (testFile.getline(test, 256))
		{
			std::string testString(test);
			if(testString.substr(0, 7).compare("::EXT::") == 0)
			{
				Person* person = people[index];
				std::string extension = testString.substr(7, 4);
				std::string value = testString.substr(11, 17);
				person->extensions[extension] = value;
			}
			else
			{
				index++;
				Person* person = new Person();
				person->Name = testString.substr(0,19);
				int trim = person->Name.find_last_not_of(' ');
				person->Name = person->Name.substr(0, trim+1);
				person->Age = atoi(testString.substr(20, 21).c_str());
				person->Birthday = testString.substr(22, 27);
				people.push_back(person);
			}
		}
	}
	else
		printf("Error: could not find or open %s\n", testFileName.c_str());

	testFile.close();

	int highestSalary = 0;
	int highI = 0;

	for (int i = 0; i < people.size(); ++i)
	{
		int salary = atoi(people[i]->extensions["SAL "].c_str());
		if (salary > 0)
		{
			// std::cout << std::fixed << people[i]->Name << ": $" << salary << "\n";
			if(salary > highestSalary)
			{
				highestSalary = salary;
				highI = i;
			}
		}
	}
	printf("\n\n");


	std::cout << std::fixed << people[highI]->Name << ": $" 
		<< atoi(people[highI]->extensions["SAL "].c_str()) << "\n\n";
}