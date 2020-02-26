# AI


8 Queens with Hill Climb and Simulated Annealing
------------------------------------------------------------

Solve the 8-queens problem using Simulated Annealing and First Choice Hill Climbing.

One starts by placing one queen per column. Then, a single state is given as an array Q of 8 integers, where each

integer represents the position of the queen on the appropriate column, i.e., if Q[i]=j means that on column i, the

queen is placed on row j. Columns are rows are numbered 0 through 7.


a. () Implement a function that given a random placement of the queens, will return the # of conflicts

(as discussed in the book and in class (a conflicts occur anytime two queens can attack each other).

int getAttackScore(int Q[])

b. () Implement a function that given a queen position, will return a neighbor position obtained by

randomly “moving one of the queens to a different row on the same column. Implement a function that

given a ∆E and a temperature T, will return true with probability e∆E/T.



void nextPosition(int Q[], int nextQ[]);

bool acceptNext(double dE, double T);

c. () Using the functions from part a and b, implement simulated annealing using a linear

temperature schedule, with T0 and maximum number of steps N (i.e., decrease temperature each time step

by a ∆T, such that after N steps T=0. The function should take a random state Q, T0 and N as argument.

After each run the function should return true if solution is found and false if it is not. At the completion

of the run Q should contain the value of the solution (or the last attempt if the solution is not found).

bool solveSimulatedAnnealing(int Sol[], double T0 = 4, int maxSteps = 5000);

d. () Using the functions from part a and b, implement first choice hill climbing with maximum

number of steps N. The function should take a random state Q and N as argument. After each run the

function should return true if solution is found and false if it is not. At the completion of the run Q should

contain the value of the solution (or the last attempt if the solution is not found).

Hint: First Choice Hill climbing is basically simulated annealing with a much simpler acceptNext function.

bool solveHillClimbingFC(int Sol[], int maxSteps = 5000);

e. () Run the simulation 100 times with T0=4, N=5000 and record the number of times the solution is

found each of the above algorithms (simulated annealing and first choice). Make sure you use the same

starting queen position for both algorithms. Repeat with N=50000. Fill in the table below with the

success rate percentage.




Missionary and Cannibals + Navigation
------------------------------------------------------------

Robot Navigation. Consider the problem of finding the shortest path

between two points on a plane that has convex polygonal obstacles as shown in Figure below. This is an

idealization of the problem that a robot has to solve to navigate in a crowded environment.

The shortest path from one polygon vertex to any other in the scene must consist of straight-line segments

joining some of the vertices of the polygons. You are given a file representing a graph. The vertices of the graph are

the vertices of the polygons and the starting and goal positions. The edges of the graph are all the above pairs of vertices

that can be connected by a straight line without going through an obstacle. An implementation of the node structure and

the graph structure is given to you, as well as a function that populates the graph from the data file. In the last assignment

you implemented the getSuccesors function. You are now ready to implement some different search algorithms.

a. Implement a Breadth-First search function with the prototype given below. This algorithm will return a path with

the shortest number of jumps possible from start to goal state.

vector<int> breadth_first_search_Nav(navigationGraph g1, int start, int goal);

b. Implement a Uniform-Cost search function with the prototype given below. This algorithm will return the

shortest path possible between start and goal state.

vector<int> uniform_cost_search_Nav(navigationGraph g1, int start, int goal);

c. Implement a Depth-First search function with the prototype given below.

vector<int> depth_first_search_Nav(navigationGraph g1, int start, int goal);
  
  
  
  
  
Navigation with DFS BFS Uniform A-star
------------------------------------------------------------

 Implement an A* search function using the straight line distance (SLD) heuristic. The function

prototype is given below. This algorithm will return the shortest path possible between start and goal state.

vector<int> astar_SLD_Nav(navigationGraph g1, int start, int goal);

b. Modify  A* and uniform-cost functions to count the number of nodes visited. Submit both

modified functions, marking in bold font the changes you made



Tic Tac Toe with MinMax
------------------------------------------------------------


Implement the minimax and alpha beta algorithms to play TicTacToe. Consider the TicTacToe board. We can

label each position 0 to 8 as shown below

 0 | 1 | 2
 ---|---|---
 3 | 4 | 5
 ---|---|---
 6 | 7 | 8

Then the state of the board is given by a string S, where S[i]=’x’ or ‘X’ if the first player has made that move

and, S[i]=’o’ or ‘O’ if the second player has made that move, and S[i]=’ ‘ or ‘.’ otherwise. Player 1 (x)

is the maximizing player and Player 2 (o) is the minimizing one.

a. (1 point) Implement a function that given a state of the board will return

• 1 if it is a winning position for player 1 (x)

• -1 if it is a winning position for player 2 (0)

• 0 if the position is not a winning position for either side yet


int getAttackScore(int Q[])

b. (2 points) The minmax function has already implemented, but in order for it to work, you need to

implement the minvalue and maxvalue functions (pseudocode in the textbook page 166).


double minvalue(string state);
double maxvalue(string state);
c. (2 points) Implement the alpha-beta algorithm (pseudocode in the textbook page 170).
int minimaxAB(string state, bool xturn); 
