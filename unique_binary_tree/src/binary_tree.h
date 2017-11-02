#include <string>

struct Tree
{
	int value;
	Tree* l;
	Tree* r;
	Tree() { value =0; l = NULL; r = NULL;}
	Tree* operator= (Tree &copyTree) {this->value = copyTree.value; this->l = copyTree.l; this->r = copyTree.r;}
};

class BinaryTree
{
public:
	BinaryTree(std::string treeLine);
	~BinaryTree();
	BinaryTree(BinaryTree &copyTree);
	BinaryTree& operator= (BinaryTree &copyTree);

	Tree* GetTree();
private:
	void GenerateTree(std::string &treeLine, Tree* node);
	void PrintOne(Tree *T);
	void PrintAll(Tree *T);

	Tree* T;
};