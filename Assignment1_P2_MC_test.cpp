#include <iostream>   //cin,cout
#include <queue>     
#include <vector>
#include <stack>
#include <map>
#include <iomanip>


using namespace std;

struct mcNode    //structure of each node in the tree
{
	int state;
	//state of the node
	// x =1 if boat is on the original side of the river, x=0 otherwise
	// y = "number of missionaries on the original side of the river"
	// z = "number of cannibals on the original side of the river"
	//state=x*100+y*10+z
	int parent;         //the state of the parent node
	double costG;       //g(n), cost (1 per step) from start to present
	int action;   //1=one cannibal on the boat; 2=two cannibals; 10=one missionary; 20=two missionaries; 11=one missionary+one cannibal 
};



vector<mcNode> getSuccesors(mcNode curr);
vector<mcNode> getSuccesors35(mcNode curr);

void printNode(mcNode x)
{
	cout << "State: " << x.state << "; Parent:" << x.parent << "; Cost: " << x.costG << "; Action: " << x.action << endl;
}

int main()
{
	mcNode curr = { 133,-1, 0, 0 };
	vector<mcNode> children;
	cout << "Testing 3 couples and boat capacity 2....\n\n";
	cout << "Current Node :\n";
	printNode(curr);
	children = getSuccesors(curr);
	cout << "Possible child nodes :\n";
	int n = children.size();
	for (int i = 0; i < n; i++)
		printNode(children[i]);

	cout << "Enter a node (apace separated: state parent cost action)\n";
	cin >> curr.state >> curr.parent >> curr.costG >> curr.action;
	cout << "Current Node :\n";
	printNode(curr);
	children = getSuccesors(curr);
	cout << "Possible child nodes :\n";
	n = children.size();
	for (int i = 0; i < n; i++)
		printNode(children[i]);

	system("pause");
	cout << "\nTesting 5 couples and boat capacity 3....\n\n";
	curr = { 155,-1, 0, 0 };
	cout << "Current Node :\n";
	printNode(curr);
	children = getSuccesors35(curr);
	cout << "Possible child nodes :\n";
	n = children.size();
	for (int i = 0; i < n; i++)
		printNode(children[i]);

	cout << "Enter a node (apace separated: state parent cost action)\n";
	cin >> curr.state >> curr.parent >> curr.costG >> curr.action;
	cout << "Current Node :\n";
	printNode(curr);
	children = getSuccesors35(curr);
	cout << "Possible child nodes :\n";
	n = children.size();
	for (int i = 0; i < n; i++)
		printNode(children[i]);


	return 0;
}

vector<mcNode> getSuccesors(mcNode curr)
{
	int boatSide = curr.state / 100;
	int can = curr % 10;
	int mis = (curr.state - (boatSide * 100) - (can)) / 10;

	cout << boatSide << mis << can << endl;



	mcNode newNode;
	vector<mcNode> childrenNode;

	newNode.parent = curr.state;
	newNode.costG = curr.costG + 1;

		if(boatSide ==1)
		{ 
			if()
		}
		if(boatSide ==0)
		{ }


}

//To test your functions, place them below