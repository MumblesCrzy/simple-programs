#include <stdio.h>

#include "solution.h"

int solution(Tree* T)
{
	std::map<int, int> map;
	int max = 0;

	findMax(T, map, max);

	printf("max %d\n", max);

	return max;
}

void findMax(Tree* T, std::map<int,int>& hash, int &max)
{
	if (T == NULL)
	{
        if (hash.size() >= max)
        { 
        	max = hash.size();
        	printf("max %d\n", max);
        }
        return;
    }

    hash[T->value]+=1;

    findMax(T->l, hash, max);
    findMax(T->r, hash, max);

    std::map<int,int>::iterator it = hash.find(T->value);
    if (it->second <= 1)
    {
        hash.erase(it);
        printf("erase %d:%d\n", it->first, it->second);
    }
    else
    {
        it->second--;
        printf("count %d\n", it->second);
    }
}