#include <iostream>
#include <string>
#include <math.h>
#include <time.h>
#include <algorithm>

using namespace std;



void drawBoard(string state);

string play(string state, bool xturn);
string playAI(string state, bool xturn);
string playAIab(string state, bool xturn);


int minimax(string state, bool xturn);
double minvalue(string state);
double maxvalue(string state);

int minimaxAB(string state, bool xturn);
double minvalueAB(string state, double alpha, double beta);
double maxvalueAB(string state, double alpha, double beta);

int eval(string state);  //given a state s, return 1 if x wins, -1 if o wins, 0  undetermined (may or may not be a leaf)



int main()
{
	cout << "Testing eval function ...\n";
	system("pause");


	string s[] = { ".........", "o..xooxXx","xoxxoxoO.", "x.oxOxo..","......xox","xxooxxoxo",".x..o...x" };

	for (int i = 0; i < 7; i++)
	{
		system("cls");
		drawBoard(s[i]);
		cout << "Evaluation : " << eval(s[i]) << endl;
		system("pause");
	}



	cout << "Testing minimax by game playing ...\n";
	system("pause");
	string state;
	bool xturn;

	//AI goes first
	state = ".........";
	drawBoard(state);
	xturn = true;
	for (int i = 0; i < 9; i++)
	{
		if (xturn)
			state = playAI(state, xturn);
		else
			state = play(state, xturn);
		if (eval(state) > 0)
		{
			cout << "AI (x) wins !" << endl;
			break;
		}
		if (eval(state) < 0)
		{
			cout << "Player 2 (o) wins !" << endl;
			break;
		}
		if (eval(state) == 0 && i == 8)
		{
			cout << "Draw!" << endl;
			break;
		}
		xturn = !xturn;
	}

	system("pause");
	xturn = true;
	state = ".........";

	//AI goes second
	for (int i = 0; i < 9; i++)
	{
		if (xturn)
			state = play(state, xturn);
		else
			state = playAI(state, xturn);
		if (eval(state) < 0)
		{
			cout << "AI (o) wins !" << endl;
			break;
		}
		if (eval(state) > 0)
		{
			cout << "Palyer 1 (x) wins !" << endl;
			break;
		}
		if (eval(state) == 0 && i == 8)
		{
			cout << "Draw!" << endl;
			break;
		}
		xturn = !xturn;
	}
	system("pause");


	cout << "Testing minimax alpha-beta by game playing ...\n";
	system("pause");


	//AI goes first
	state = ".........";
	drawBoard(state);
	xturn = true;
	for (int i = 0; i < 9; i++)
	{
		if (xturn)
			state = playAIab(state, xturn);
		else
			state = play(state, xturn);
		if (eval(state) > 0)
		{
			cout << "AI (x) wins !" << endl;
			break;
		}
		if (eval(state) < 0)
		{
			cout << "Player 2 (o) wins !" << endl;
			break;
		}
		if (eval(state) == 0 && i == 8)
		{
			cout << "Draw!" << endl;
			break;
		}
		xturn = !xturn;
	}

	system("pause");
	xturn = true;
	state = ".........";

	//AI goes second
	for (int i = 0; i < 9; i++)
	{
		if (xturn)
			state = play(state, xturn);
		else
			state = playAIab(state, xturn);
		if (eval(state) < 0)
		{
			cout << "AI (o) wins !" << endl;
			break;
		}
		if (eval(state) > 0)
		{
			cout << "Palyer 1 (x) wins !" << endl;
			break;
		}
		if (eval(state) == 0 && i == 8)
		{
			cout << "Draw!" << endl;
			break;
		}
		xturn = !xturn;
	}
	system("pause");

	return 0;
}


/********************************************************/
///Drawing and game play functions////////////////////////
void drawBoard(string state)
{
	string board[] = { ".....|.....|.....",
	".....|.....|.....",
	".....|.....|.....",
	"-----+-----+-----",
	".....|.....|.....",
	".....|.....|.....",
	".....|.....|.....",
	"-----+-----+-----",
	".....|.....|.....",
	".....|.....|.....",
	".....|.....|.....", };
	cout << endl;

	for (int i = 0; i < 9; i++)
	{
		int a = i / 3, b = i % 3;
		board[a * 4 + 1][b * 6 + 2] = state[i];
	}

	cout << "      0     1     2" << endl;
	cout << endl;

	for (int i = 0; i < 11; i++)
	{
		if (i % 4 == 1)
			cout << i / 4 << "   ";
		else
			cout << "    ";
		for (int j = 0; j < 17; j++)
		{
			char ch = toupper(board[i][j]);
			switch (ch)
			{
			case '.': cout << ' '; break;
			case '|': cout << char(186); break;
			case '-': cout << char(205); break;
			case '+': cout << char(206); break;
			case 'X': cout << 'X'; break;
			case 'O': cout << 'O'; break;
			}

		}
		cout << endl;
	}
	cout << endl;
}

string play(string state, bool xturn)
{
	int r, c;
	system("cls");
	drawBoard(state);
	if (xturn)
	{
		cout << "X-player, enter the coordinates of where you want to play (row then column):";
		cin >> r >> c;
		int ind = r * 3 + c;
		while (r > 2 || r < 0 || c>2 || c < 0 || state[ind] == 'x' || state[ind] == 'X' || state[ind] == 'o' || state[ind] == 'O')
		{
			cout << "Illegal move.  Try again : ";
			cin >> r >> c;
			ind = r * 3 + c;
		}
		state[ind] = 'x';
	}
	else
	{
		cout << "O-player, enter the coordinates of where you want to play (row then column):";
		cin >> r >> c;
		int ind = r * 3 + c;
		while (r > 2 || r < 0 || c>2 || c < 0 || state[ind] == 'x' || state[ind] == 'X' || state[ind] == 'o' || state[ind] == 'O')
		{
			cout << "Illegal move.  Try again : ";
			cin >> r >> c;
			ind = r * 3 + c;
		}
		state[ind] = 'o';
	}
	system("cls");
	drawBoard(state);
	return state;
}

string playAI(string state, bool xturn)
{
	int action = minimax(state, xturn);// assign action based on algorithm

	if (xturn)
	{
		state[action] = 'x';
	}
	else
	{
		state[action] = 'o';
	}
	system("cls");
	drawBoard(state);
	cout << "AI played : (" << action / 3 << ", " << action % 3 << ")\n";
	system("pause");
	return state;
}

string playAIab(string state, bool xturn)
{
	int action = minimaxAB(state, xturn);// assign action based on algorithm

	if (xturn)
	{
		state[action] = 'x';
	}
	else
	{
		state[action] = 'o';
	}
	system("cls");
	drawBoard(state);
	cout << "AI played : (" << action / 3 << ", " << action % 3 << ")\n";
	system("pause");
	return state;
}

/*********************************************************/

int minimax(string state, bool xturn)
{
	int action = 0;
	for (int i = 0; i < 9; i++)
		state[i] = tolower(state[i]);

	if (xturn)  //max players turn
	{
		//pick the action that maximizes 
		double maxv = -2000;
		action = 0;
		for (int i = 0; i < 9; i++)
		{
			if (state[i] != 'x' && state[i] != 'o')  //a valid move
			{
				string newstate = state;
				newstate[i] = 'x';
				double val = minvalue(newstate);
				if (val > maxv)
				{
					maxv = val;
					action = i;
				}
			}
		}
	}
	else
	{
		//pick the action that minimizes 
		double minv = 2000;
		action = 0;
		for (int i = 0; i < 9; i++)
		{
			if (state[i] != 'x' && state[i] != 'o')  //a valid move
			{
				string newstate = state;
				newstate[i] = 'o';
				double val = maxvalue(newstate);
				if (val < minv)
				{
					minv = val;
					action = i;
				}
			}
		}
	}
	return action;
}

/*********************************************************/

int eval(string s)  //given a state s, return 1 if x wins, -1 if o wins, 0  undetermined (may or may not be a leaf)
{

	for (int i = 0; i < 9; i++)
		s[i] = tolower(s[i]);

	for (int i = 0; i < 9; i++)
	{
		//------------------------------------------- X Win -----------------------------------------------

		if (s[i] == 'x' || s[i] == 'X')
		{

			if (i <= 6 && s[i] == s[i + 1] && s[i + 1] == s[i + 2]) //vertical
				return 1;

			else if (i <= 2 && s[i] == s[i + 3] && s[i + 3] == s[i + 6]) //horizontal
				return 1;

			else if (i == 0 && s[i] == s[i + 4] && s[i + 4] == s[i + 8]) // diagnal
				return 1;

			else if (i == 2 && s[i] == s[i + 2] && s[i + 2] == s[i + 4]) // diagnal
				return 1;
		}

		//--------------------------------------------- O Win ---------------------------------------------

		if (s[i] == 'o' || s[i] == 'O')
		{

			if (i <= 5 && s[i] == s[i + 1] && s[i + 1] == s[i + 2]) //vertical
				return -1;

			else if (i <= 2 && s[i] == s[i + 3] && s[i + 3] == s[i + 6]) //horizontal
				return -1;

			else if (i == 0 && s[i] == s[i + 4] && s[i + 4] == s[i + 8]) // diagnal
				return -1;

			else if (i == 2 && s[i] == s[i + 2] && s[i + 2] == s[i + 4]) // diagnal
				return -1;
		}
	}



	return 0;
}



double minvalue(string state)
{

	if (eval(state) == -1)
		return -1;

	if (eval(state) == 1)
		return 1;
	
	double v = numeric_limits<double>::max();

	for (int i = 0; i < 9; i++)
		if (state[i] != 'x' && state[i] != 'o')  //a valid move
		{

			string newstate = state;
			newstate[i] = 'o';

			v =  min(v, maxvalue(newstate));

			//newstate[i] = '.';

		}

	return v;
}

double maxvalue(string state)
{
	if (eval(state) == 1)
		return 1;

	else if (eval(state) == -1)
		return -1;

	double v = numeric_limits<double>::min();

	for (int i = 0; i < 9; i++)
		if (state[i] != 'x' && state[i] != 'o')  //a valid move
		{
			string newstate = state;
			newstate[i] = 'o';

			v = max(v, minvalue(newstate));


			//newstate[i] = '.';
		}

	return v;
}


int minimaxAB(string state, bool xturn)
{
	int action = 0;
	for (int i = 0; i < 9; i++)
		state[i] = tolower(state[i]);

	if (xturn)  //max players turn
	{
		//pick the action that maximizes 
		double maxv = -2000;
		action = 0;
		for (int i = 0; i < 9; i++)
		{
			if (state[i] != 'x' && state[i] != 'o')  //a valid move
			{
				string newstate = state;
				newstate[i] = 'x';
				double val = minvalueAB(state, numeric_limits<double>::min(), numeric_limits<double>::max());
				if (val > maxv)
				{
					maxv = val;
					action = i;
				}
			}
		}
	}
	else
	{
		//pick the action that minimizes 
		double minv = 2000;
		action = 0;
		for (int i = 0; i < 9; i++)
		{
			if (state[i] != 'x' && state[i] != 'o')  //a valid move
			{
				string newstate = state;
				newstate[i] = 'o';
				double val = maxvalueAB(state, numeric_limits<double>::min(), numeric_limits<double>::max());
				if (val < minv)
				{
					minv = val;
					action = i;
				}
			}
		}
	}
	return action;
}
double minvalueAB(string state, double alpha, double beta)
{

	if (eval(state) == -1)
		return -1;
	else if (eval(state) == 1)
		return 1;

	double v = numeric_limits<double>::max();

	for (int i = 0; i < 9; i++)
		if (state[i] != 'x' && state[i] != 'o')  //a valid move
		{
			string newstate = state;
			newstate[i] = 'o';

			v = max(v, minvalueAB(newstate, alpha, beta));

			if (v <= alpha)
				return v;

			beta = max(beta, v);
		}

	return 0;
}
double maxvalueAB(string state, double alpha, double beta)
{

	if (eval(state) == -1)
		return -1;
	else if (eval(state) == 1)
		return 1;

	double v = numeric_limits<double>::min();

	for (int i = 0; i < 9; i++)
		if (state[i] != 'x' && state[i] != 'o')  //a valid move
		{
			string newstate = state;
			newstate[i] = 'x';

			v = max(v,minvalueAB(newstate, alpha, beta));

			if (v >= beta)
				return v;

			alpha = max(alpha, v);
		}

	return 0;
}