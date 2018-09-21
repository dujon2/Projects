/*
Raise the pay part 1
Bruce Elenbogen Fall 2017

Raise the part part 2 
DuJon Brown-Deacon

Input 
two ints first number of employees and then percentage for request for raise
the input the employee at the current index's boss
*/
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <vector>
using namespace std;
struct Node
{
	int id;
	int minRequests4Raise;
	vector< Node *> underlings;

	Node(int n = 0) // constructor
	{
		id = n;
		minRequests4Raise = -1;
	}


};

//Pre:ptr must already be created 
//and node with same id number has not been created
//Post:Node is created with int id as its id and it is made into
//an underling for ptr
void addUnderling(Node * ptr, int id)
{
	ptr->underlings.push_back(new Node(id));
}
//Pre:Both ptr and underptr have already been created
//Post:the under pointer is now an underling
void addUnderling(Node * ptr, Node *underPtr)
{
	ptr->underlings.push_back(underPtr);
}


class Tree
{
private:
	Node * root;
	//pre:Tree must be completed
	//post:prints out the id and its underling 
	void print(Node * ptr, int level) // private version of print
	{
		if (ptr != nullptr)
		{
			cout << setw(5 * level) <<"" <<ptr->id<<endl;
			for (int i = 0; i < ptr->underlings.size(); i++)
				print(ptr->underlings[i], level + 1);
		}
	}

	//pre:Tree must be completed and and mins must be added
	//post:Prints the min of the root of the tree
	void printMins(Node * ptr, int level)
	{
		if (ptr->id == 0)
		{
			
			cout << setw(5 * level) << "" << ptr->minRequests4Raise << endl;

		}
	}
	//pre:root must exist and target has to be positive
	//post:find the location of the node whos id is equal to target
	Node * find(Node * root, int target)  // private version of find 
	{
		Node * temp;
		if (root == nullptr)
			return nullptr;
		else if (root->id == target)
			return root;
		else
			for (int i = 0; i < root->underlings.size(); i++)
			{
				temp = find(root->underlings[i], target);
				if (temp != nullptr)
					return temp;
			}
		return nullptr;
	}
	//pre:Tree must be completed(in terms of adding Nodes)
	//post:Sets all Nodes who have no uderlings min to 1
	void setTermMins(Node * root) 
	{
		

		if (root->underlings.size() == 0) {root->minRequests4Raise = 1; }
			
			for (int i = 0; i < root->underlings.size(); i++)
			{
				

				
				setTermMins(root->underlings[i]);
				
			}
		
	}
	//pre:All nodes who dont have underlings mins are set to 1
	//and tree must be completed
	//post:all nodes who have underlings whose mins all equal 1 
	//mins are set
	void setMins(Node * root,double threshold)
	{


		for (int i = 0; i < root->underlings.size(); i++)
		{
			if(alltermUnderlings(root)==0)
			{
				root->minRequests4Raise = ceil(root->underlings.size()*(threshold / 100.00));
			}


			setMins(root->underlings[i],threshold);

		}



	}
	//pre:All nodes who dont have underlings mins are set to 1
	//and tree must be completed
	//post: returns 1 if one of the underlings min isnt 1 and 
	//0 if all underlings equal 1
	bool alltermUnderlings(Node * root)
	{
		int count=0;
		
		for (int i = 0; i < root->underlings.size(); i++) 
		{
			if (!root->underlings.empty()) 
			{
				if (root->underlings[i]->minRequests4Raise == 1) { ++count; }
			}
			else { return 1; }
		}
		if (count == root->underlings.size()) { return 0; }
		else { return 1; }
	}
	//pre:All nodes who dont have underlings mins are set to 1
	//and tree must be completed and all nodes who have underlings whose mins 
	//all equal 1  mins are set to their respective mins
	//post:Sets the rest of the mins
	void setOtherMins(Node * root,double threshold) 
	{ 
		double d=0;
		int total;
		vector <int> mins;
		for (int i = 0; i < root->underlings.size(); i++)
		{
		
			if((!root->underlings.empty()))
			{
				for (int j = 0; j < root->underlings.size(); j++)
				{
					if ((root->underlings[j]->minRequests4Raise == -1) || (root->id == 0))
					{
						setOtherMins(root->underlings[j], threshold);
					}

				}
					d= ceil(root->underlings.size()*(threshold / 100.00));
					for (int k = 0; k < root->underlings.size(); k++)
					{
						mins.push_back(root->underlings[k]->minRequests4Raise);
					}

					sort(mins.begin(), mins.end());

					total = 0;
					for (int l = 0; l < d; l++) 
					{
						total = total + mins[l];

					}

					root->minRequests4Raise = total;
					mins.clear();
				}
			
			setOtherMins(root->underlings[i],threshold);
		}
		
	}
	//pre:Tree must be complete
	//post: All nodes mins are set 
	void setAllMins(Node * root, double threshold)
	{
		setTermMins(root);
		setMins(root, threshold);
		setOtherMins(root, threshold);
	}

	
public:
	Tree(Node * rt = nullptr) { root = rt; }
	//pre: Tree must be completed
	//post: Trees ids are printed
	void print() { print(root, 0); }
	Tree(int id) { root = new Node(id); }
	Node * getRoot() { return root; }
	void printTree()                   // public print
	{
		print(root, 0);
	}
	//pre: Tree must be complete and mins must be set
	//post: Tree at id 0's min is printed
	void printMin() { printMins(root, 0); }
	//pre: Tree must have atleast one node in it
	//post: returns location of node whos id is equal to target
	Node * find(int target)          // public find 
	{
		return find(root, target);
	}
	//pre: Tree must be complete and threshold must be above -1 and below 101
	//post:All mins are set
	void setAllMins(double threshold)
	{
		setAllMins(root, threshold);
	}
};

class Forest
{
private:
	vector< Tree > trees;
	
public:
	//pre: Trees must be complete (all Trees Nodes are already in tree)
	//post: All trees are printed
	void print()
	{
		for (int i = 0; i < trees.size(); i++)
			trees[i].printTree();
		cout << endl;
	}
	//pre: Trees must be complete (all Trees Nodes are already in tree and their min are set)
	//post: All trees mins at the root are printed
	void printMins()
	{
		
		



		for (int i = 0; i < trees.size(); i++)
		{
			trees[i].printMin();
			
		}
	}
	//pre: Atleast one tree must be in the trees vector and atleast one node in that tree
	//post: returns the the location of node whose id matches target
	Node * find(int target)
	{
		Node * temp;
		for (int i = 0; i < trees.size(); i++)
		{
			temp = trees[i].find(target);
			if (temp != nullptr)
				return temp;
		}
		return nullptr;
	}
	//pre: boss and underling must be positive and first node must be in tree
	//post: ints that were passed through have nodes created with 
	//respectives ints as ids if not made already and those nodes are connected
	void insert(int boss, int underling)
	{
		Node * bossPtr = find(boss);
		Node * underPtr = find(underling);
		if (bossPtr == nullptr && underPtr == nullptr) // need a new tree
		{
			trees.push_back(*(new Tree(boss)));
			addUnderling(trees[trees.size() - 1].getRoot(), underling);
		}
		else if (underPtr == nullptr)
		{
			addUnderling(bossPtr, underling);
		}
		else if (underPtr != nullptr) // the underling is already a boss
		{
			if (bossPtr == nullptr)  // if boss is not in the tree put him in
			{
				trees.push_back(*(new Tree(boss)));
				bossPtr = find(boss);
			}
			// now both are in the tree 
			addUnderling(bossPtr, underPtr);
			for (auto itr = trees.begin(); itr != trees.end(); itr++)
				if (itr->getRoot()->id == underling)
				{
					trees.erase(itr);
					return;
				}

		}
	}
	Forest()
	{
		trees.push_back(Tree(0));
	}

	void clear() { trees.clear(); }
	//pre: Tree must be complete
	//post: Tree's mins are set
	void setAllMins(double threshold) 
	{ 
	trees[0].setAllMins(threshold);
	
	}
};

int main()
{
	int numEmploys, boss;
	double threshold;
	Forest gump;
	vector<Forest> dum;

	cin >> numEmploys >> threshold;
	while (numEmploys > 0 && threshold > 0)
	{
		for (int i = 0; i < numEmploys; i++)
		{
			cin >> boss;
			gump.insert(boss, i + 1);

		}
		
			gump.setAllMins(threshold);

		
		dum.push_back(gump);
		gump.clear();
		cin >> numEmploys >> threshold;
	}
	for (int i = 0; i < dum.size(); i++) 
{
		dum[i].printMins();
		
}
	
	
	return 0;
}
 
