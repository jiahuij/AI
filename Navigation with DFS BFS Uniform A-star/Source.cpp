/*
Consider the problem of finding the shortest path between two points on a plane that has convex polygonal obstacles.
This is an idealization of the problem that a robot has to solve to navigate in a crowded environment.
he vertices of the graph are the vertices of the polygons and the starting and goal positions.
The shortest path from one polygon vertex to any other in the scene must consist of straight-line segments joining
some of the vertices of the polygons.
You are given a file representing a graph. The vertices of the graph are the vertices of the polygons and the starting and goal positions.
The edges of the graph are all the above pairs of vertices that can be connected by a straight line without going through an obstacle.

File format:
Line 1:
two integers m, n (tab separated) representing the numer of vertices and the number of edges.
Lines 2 to m+1 (list of vertices):
each line has 3 numbers i, x, y (tab separated) : i is an integer, the vertex id; x, y are real numbers, the 'x' and 'y' coordinates of the vertex .
Lines m+2 to m+n+1 (list of edges):
each line has two integers (tab separated) representing the id's of the two nodes connected by the edge.
Example: Here is the file for a graph with 6 vertices and 9 edges
					6	9
					0	0.0	0.0
					1	76.75792122307887	162.26001485048116
					2	11.935677016534685	100.82187428764182
					3	58.69782922720505	14.222944063582222
					4	98.64308647185301	57.25001252255944
					5	100.0	200.0
					0	2
					0	3
					1	2
					1	4
					1	5
					2	3
					2	5
					3	4
					4	5
*/

#include <iostream>   //cin,cout
#include <fstream>   //files
#include <queue>     
#include <vector>
#include <stack>
#include <map>
#include <iomanip>


using namespace std;

struct nodeType    //structure of each node in the tree
{
	int state;          //the index of the vertex
	int parent;         //the state of the parent node
	double costG;          //g(n), cost from start to present
	double costH;          //h(n), estimated cost by heuristic from present to goal
						//overload the < operator so we can use it for the priority queue
	friend bool operator<(nodeType x, nodeType y)
	{
		return x.costG + x.costH > y.costG + y.costH;
	};
};

struct navigationGraph
{
	int size; //number of vertices
	double** adjM;  //adjacency matrix 
	vector<double> xloc;
	vector<double> yloc;
};


bool readGraphFromFile(string filename, navigationGraph& g1);  //given a file, populate the graph
void printNode(nodeType curr);  //given a node, it prints out it's information
void printHeatmap(double** M, int n); //prints the adjacency (connections) matrix 

vector<nodeType> getSuccesors(nodeType curr, navigationGraph g1);  //given a current node curr and the graph, return the nodes you can reach from curr.


vector<int> breadth_first_search_Nav(navigationGraph g1, int start, int goal); //breadth-first search between two nodes, returns a path 
vector<int> uniform_cost_search_Nav(navigationGraph g1, int start, int goal);  //uniform cost search between two nodes, returns a path
vector<int> depth_first_search_Nav(navigationGraph g1, int start, int goal); //breadth-first search between two nodes, returns a path 
vector<int>astar_SLD_Nav(navigationGraph g1, int   start, int   goal);

//////////////////////////////////////////////////////////////

int main()
{
	string filename = "P4x6.txt";
	navigationGraph g1;
	cout << "Enter graph data filename :\n";
	cin >> filename;
	if (!readGraphFromFile(filename, g1))
		exit(1);
	int start = 0, goal = g1.size - 1;
	cout << "\nA heatmap representation of the adjacency matrix of the graph:\n";
	printHeatmap(g1.adjM, g1.size);


	vector<int> path1 = breadth_first_search_Nav(g1, start, goal);

	cout << "Breadth First Search Solution  : ";
	for (int i = path1.size() - 1; i >= 0; i--)
		cout << path1[i] << ", ";
	cout << endl;


	vector<int> path2 = uniform_cost_search_Nav(g1, start, goal);

	cout << "Uniform Cost Search Solution  : ";
	for (int i = path2.size() - 1; i >= 0; i--)
		cout << path2[i] << ", ";
	cout << endl;

	vector<int> path3 = depth_first_search_Nav(g1, start, goal);

	cout << "Depth First Search Solution  : ";
	for (int i = path3.size() - 1; i >= 0; i--)
		cout << path3[i] << ", ";
	cout << endl;

	vector<int> path4 = astar_SLD_Nav(g1, start, goal);

		cout << "A* Search Solution  : ";
	for (int i = path4.size() - 1; i >= 0; i--)
		cout << path4[i] << ", ";
	cout << endl;


	system("pause");

	return 0;
}




/////////////////////////////////////////////////////////////////////////////////
void printNode(nodeType curr)
{
	cout << "State: " << curr.state << ", Parent: " << curr.parent << ", costG: " << curr.costG << ", costH: " << curr.costH << endl;
}


bool readGraphFromFile(string filename, navigationGraph& g1)
{
	ifstream gfile(filename);

	if (!gfile)
	{
		cout << "Error opening file ..." << endl;
		return false;
	}

	int m, n;  //#of vertices, #of edges, 
	gfile >> m >> n;

	g1.size = m; //set the size of the graph

	//allocate memory for the adjacacy matrix
	g1.adjM = new double* [n];
	for (int i = 0; i < n; i++)
		g1.adjM[i] = new double[n] {0};

	int id; //vertex id
	double x, y;//x-y coordinates
	for (int i = 0; i < m; i++) //read the vertex information
	{
		gfile >> id >> x >> y;
		g1.xloc.push_back(x);
		g1.yloc.push_back(y);
	}

	int a, b; //read the edges and fill out the adjacency matrix

	for (int i = 0; i < n; i++)
	{
		gfile >> a >> b;
		g1.adjM[a][b] = 1;
		g1.adjM[b][a] = 1;
	}
	gfile.close();
	return true;
}


void printHeatmap(double** M, int n)
{
	cout << "   ";
	for (int i = 0; i < n; i++)
		cout << setw(2) << i;
	cout << endl;
	for (int i = 0; i < n; i++)
	{
		cout << setw(3) << i;
		for (int j = 0; j < n; j++)
		{
			if (M[i][j] > 0)
				cout << char(219) << char(219);
			else
				cout << char(176) << char(176);
		}
		cout << endl;
	}
}


//Put here your function implementations, including getSuccessors function


vector<nodeType> getSuccesors(nodeType curr, navigationGraph g1)
{
	vector<nodeType> children;
	int id = curr.state; //the id of current node
	nodeType newnode;
	int numChildren = 0;
	newnode.parent = id;
	for (int i = 0; i < g1.size; i++)
	{
		if (g1.adjM[id][i] > 0) //there is a connection between vertices id and i
		{
			double d = sqrt(pow(g1.xloc[id] - g1.xloc[i], 2) + pow(g1.yloc[id] - g1.yloc[i], 2));

			newnode.costG = curr.costG + d; //update the cost g(n)=cost of parent+ cost of transition
			newnode.state = i;
			newnode.costH = 0; //the heuristic cost is assumed 0 (the informed searches will update this themselves)
			children.push_back(newnode);
		}
	}
	return children;
}


vector<int> getSolPath(int currentId, int startId, map<int, nodeType> exploredNodes)
{
	vector<int> path;

	path.push_back(currentId);
	nodeType curr = exploredNodes[currentId];
	while (curr.parent != startId)
	{
		curr = exploredNodes[curr.parent];
		path.push_back(curr.state);

	}
	path.push_back(startId);
	return path;
}


vector<int> breadth_first_search_Nav(navigationGraph g1, int start, int goal)
{
	vector<int> path;
	map<int, nodeType> explored; //The set of all nodes already explored
	queue<nodeType> frontier; //for BFS the frontier is a queue
	nodeType startState = { start,-1,0,0 }; //initialize the start node
	frontier.push(startState); //initialize the frontier with the start node

	while (!frontier.empty())
	{
		nodeType curr = frontier.front(); frontier.pop(); //take next node from the frontier
		if (explored.find(curr.state) == explored.end()) //if the state has not been explored before, expand
		{
			explored[curr.state] = curr;
			vector<nodeType> children = getSuccesors(curr, g1);
			int numChildren = children.size();
			for (int i = 0; i < numChildren; i++)
			{
				if (children[i].state == goal) //reached the goal state
				{
					explored[goal] = children[i];
					path = getSolPath(children[i].state, start, explored);
					return path;
				}
				if (explored.find(children[i].state) == explored.end())
					frontier.push(children[i]);
			}
		}
	}
	return path;
}

vector<int> uniform_cost_search_Nav(navigationGraph g1, int start, int goal)
{
	vector<int> path;
	map<int, nodeType> explored; //The set of all nodes already explored
	priority_queue<nodeType> frontier; //for BFS the frontier is a queue
	nodeType startState = { start,-1,0,0 }; //initialize the start node
	frontier.push(startState); //initialize the frontier with the start node
	int nodeCount = 1;

	while (!frontier.empty())
	{
		nodeType curr = frontier.top(); frontier.pop(); //take next node from the frontier
		if (curr.state == goal)
		{
			explored[goal] = curr;
			cout << "UCS Total Node Visite: " << nodeCount << endl;
			return getSolPath(goal, start, explored);
		}
		if (explored.find(curr.state) == explored.end()) //if the state has not been explored before, expand
		{
			explored[curr.state] = curr;
			vector<nodeType> children = getSuccesors(curr, g1);
			int numChildren = children.size();
			for (int i = 0; i < numChildren; i++)
			{
				nodeCount++;
				if (explored.find(children[i].state) == explored.end())
					frontier.push(children[i]);
			}
		}
	}


	return path;
}

vector<int> depth_first_search_Nav(navigationGraph g1, int start, int goal)
{
	vector<int> path;
	map<int, nodeType> explored; //The set of all nodes already explored
	stack<nodeType> frontier; //for BFS the frontier is a queue
	nodeType startState = { start,-1,0,0 }; //initialize the start node
	frontier.push(startState); //initialize the frontier with the start node

	while (!frontier.empty())
	{
		nodeType curr = frontier.top(); frontier.pop(); //take next node from the frontier
		if (explored.find(curr.state) == explored.end()) //if the state has not been explored before, expand
		{
			explored[curr.state] = curr;
			vector<nodeType> children = getSuccesors(curr, g1);
			int numChildren = children.size();
			for (int i = 0; i < numChildren; i++)
			{
				if (children[i].state == goal) //reached the goal state
				{
					explored[goal] = children[i];
					path = getSolPath(children[i].state, start, explored);
					return path;
				}
				if (explored.find(children[i].state) == explored.end())
					frontier.push(children[i]);
			}
		}
	}

	return path;
}


vector<int> astar_SLD_Nav(navigationGraph g1, int   start, int   goal)
{
	vector<int> path;
	map<int, nodeType> explored; //The set of all nodes already explored
	priority_queue<nodeType> frontier; //for BFS the frontier is a queue
	nodeType startState = { start,-1,0,0 }; //initialize the start node
	frontier.push(startState); //initialize the frontier with the start node
	int nodeCount = 1;
	

	while (!frontier.empty())
	{
		nodeType curr = frontier.top(); frontier.pop(); //take next node from the frontier

		
			
		if (curr.state == goal)
		{
			explored[goal] = curr;
			cout << "A* Total Node Visite: " << nodeCount << endl;
			return getSolPath(goal, start, explored);
		}

		if (explored.find(curr.state) == explored.end()) //if the state has not been explored before, expand
		{
			explored[curr.state] = curr;
			vector<nodeType> children = getSuccesors(curr, g1);
			int numChildren = children.size();
			for (int i = 0; i < numChildren; i++)
			{
				nodeCount++;
				children[i].costH = sqrt(pow(g1.xloc[goal] - g1.xloc[curr.state], 2) + pow(g1.yloc[goal] - g1.yloc[curr.state], 2));
				if (explored.find(children[i].state) == explored.end())
				{
					frontier.push(children[i]);
				}
			}
		}
	}


	return path;

}