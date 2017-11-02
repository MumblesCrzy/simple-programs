#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "binary_tree.h"

BinaryTree::BinaryTree(std::string treeLine)
{
	if (!treeLine.empty())
	{
		T = new Tree();
		std::string base = treeLine.substr(1, treeLine.length());
		GenerateTree(base, T);
		// PrintAll(T);
	}
}

BinaryTree::~BinaryTree()
{

}

BinaryTree::BinaryTree(BinaryTree &copyTree)
{

}

BinaryTree& BinaryTree::operator= (BinaryTree &copyTree)
{
	this->T = copyTree.T;
}

Tree* BinaryTree::GetTree()
{
	return T;
}

void BinaryTree::GenerateTree(std::string &treeLine, Tree* node)
{
	if(!treeLine.empty() && node != NULL)
	{
		int delimiter = treeLine.find_first_not_of("1234567890NULL");
		if (delimiter != std::string::npos)
		{
			int erasePos = delimiter+1;
			std::string valueString = treeLine.substr(0, delimiter);
			printf("valueString %s\n", valueString.c_str());
			if (valueString.compare("NULL") == 0)
			{
				erasePos += 1;
				treeLine.erase(0, erasePos);
				delete node;
				node = NULL;
				return;
			}
			else
			{
				node->value = atoi(valueString.c_str());
				// printf("node's value %d\n", node->value);
				// printf("treeLine[erasePos+1] %c\n", treeLine[erasePos+1]);
				if (treeLine[erasePos+1] == '(')
				{
					erasePos += 2;
					node->l = new Tree();
					treeLine.erase(0, erasePos);
					GenerateTree(treeLine, node->l);
				}
				
				// printf("treeLine[erasePos] '%c'\n", treeLine[erasePos]);
				if (treeLine[erasePos] == ' ')
				{
					++erasePos;
					node->r = new Tree();
					treeLine.erase(0, erasePos);
					GenerateTree(treeLine, node->r);
				}

				if (treeLine[erasePos] == ')')
				{
					node->r = new Tree();
					treeLine.erase(0, erasePos);
					GenerateTree(treeLine, node->r);
				}

				if (isdigit(treeLine[erasePos]))
				{
					node->r = new Tree();
					treeLine.erase(0, erasePos);
					GenerateTree(treeLine, node->r);	
				}
			}
		}
	}
}

void BinaryTree::PrintOne(Tree *T)
{
    // std::cout << T->value << "\n";
}

void BinaryTree::PrintAll(Tree *T)
{
    if(T != NULL)
    {
	    std::cout << T->value << "\n";
        PrintAll(T->l);
        PrintOne(T);
        PrintAll(T->r);
    }
}
