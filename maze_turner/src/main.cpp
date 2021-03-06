#include <stdio.h>
#include <string>
#include <vector>
#include <glob.h>

#include "maze_turner.h"

int main(int argc, char const* argv[])
{

	glob_t globResult;
	std::vector<std::string> files;
	const int result = glob("maps/*", 0, 0, &globResult);

	if (result == GLOB_NOMATCH) 
	{
	    printf("No files found that match maps/*\n");
	} 
	else 
	{
		for(unsigned int i = 0; i < globResult.gl_pathc; ++i)
		{
			files.push_back(std::string(globResult.gl_pathv[i]));
		}
	}

	for (int i = 0; i < files.size(); ++i)
	{
		/* code */
	    printf("Using map file %s\n", files[i].c_str());

	    MazeTurner turner(files[i]);
	    int turnerReport = 0;
	    while(turnerReport == 0)
	    {
	    	turnerReport = turner.NavigateMap();
	    }
	    if (turnerReport == 1)
		    printf("I did it!\n");
		else
			printf("It's impossible\n");
	}
	
	return 0;
}
