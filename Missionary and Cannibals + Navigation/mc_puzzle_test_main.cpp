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
vector<mcNode> breadth_first_search_MC();
vector<mcNode> breadth_first_search_MC35();

void display(bool boat, int m, int c, int M = 3, int C = 3, int B = 2);




int main()
{


	vector<mcNode> path = breadth_first_search_MC();
	int n = path.size();
	if (n > 0)
	{

		cout << "Pathsize=" << n << endl;
		for (int i = n - 1; i >= 0; i--)
		{
			system("cls");
			int z = path[i].state;
			int boat = z / 100;
			z = z % 100;
			int x = z / 10;
			int y = z % 10;
			cout << "Testing 3 couples, boat capacity 2 case....\n";
			display(boat > 0, x, y);
			system("pause");
		}
	}
	else
	{
		cout << "No solution!!!" << endl;
	}
	system("pause");

	vector<mcNode> path2 = breadth_first_search_MC35();
	int n2 = path2.size();
	if (n2 > 0)
	{

		cout << "Pathsize=" << n2 << endl;
		for (int i = n2 - 1; i >= 0; i--)
		{
			system("cls");
			int z = path2[i].state;
			int boat = z / 100;
			z = z % 100;
			int x = z / 10;
			int y = z % 10;
			cout << "Testing 5 couples, boat capacity  case....\n";
			display(boat > 0, x, y, 5, 5, 3);
			system("pause");
		}
	}
	else
	{
		cout << "No solution!!!" << endl;
	}
	system("pause");
	return 0;
}
/////////////////////////////////////////////////////////////////////
void display(bool boat, int m, int c, int M , int C , int B )
{
	string Sm = "MMMMMMMMMMMMMMMMMMMM", Sc = "CCCCCCCCCCCCCCCCCCC", Sb = "___________", Ss = "         ";

	if (boat)
		cout << "\n\\" << Sb.substr(0, B) << "/  ";
	else
		cout << "\n      " << Ss.substr(0, B);
	cout << Sm.substr(0, m) << " " << Sc.substr(0, c) << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n";
	if (!boat)
		cout << "\\" << Sb.substr(0, B) << "/  ";
	else
		cout << "      " << Ss.substr(0, B);
	cout << Sm.substr(0, M - m) << " " << Sc.substr(0, C - c) << endl;

}



//Put here your function implementations, including getSuccessors functions
