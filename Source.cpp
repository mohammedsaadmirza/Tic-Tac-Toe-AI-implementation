#include <iostream>
#include <iomanip>
#include <string>
#include <array>

// This is a program to play a single game of tic-tac-toe
// between two human (non-AI) players.

using namespace std;

void PrintBoard(array <char, 9>);
int programprogress();
int checkwin(array <char, 9>);
int minimax(array <char, 9>, int, int, bool);
int Opposite(int);
char PlayerSymbol(int);

const int SIZE = 9;
array <char, SIZE> Pos = { '1', '2', '3', '4', '5', '6', '7', '8', '9' };
int player_number = 1;
int i = -1, result;

// Global variables used by 2 or more functions.
// Array had to be initialized with numbers instead of blank spaces
// because the check win function wouldn't work properly.

int main()
{
	cout << "This is tic tac toe! Here's your board!" << endl;

	PrintBoard(Pos);
	//programprogress();
	result = programprogress();
	player_number--;
	PrintBoard(Pos);

	if (result == 1)
		cout << endl << "Player " << player_number << " has won!!!\n ";
	else
		cout << endl << "The game has been drawn!" << endl;
	return 0;
}

void PrintBoard(array <char, 9> Pos)
{
	system("cls");
	cout << setw(6) << "|" << setw(6) << "|" << endl << setw(3) << Pos[0] << setw(3) << "|" << setw(3) << Pos[1] << setw(3) << "|" << setw(3) << Pos[2] << "     TIC           TOE" << endl;
	cout << "_____|_____|_____" << endl;
	cout << setw(6) << "|" << setw(6) << "|" << endl << setw(3) << Pos[3] << setw(3) << "|" << setw(3) << Pos[4] << setw(3) << "|" << setw(3) << Pos[5] << "            TAC   " << endl;
	cout << "_____|_____|_____" << endl;
	cout << setw(6) << "|" << setw(6) << "|" << endl << setw(3) << Pos[6] << setw(3) << "|" << setw(3) << Pos[7] << setw(3) << "|" << setw(3) << Pos[8] << "     TIC            TOE  " << endl;
	cout << "     |     |" << endl;
}


int programprogress()
{
	while (i == -1)
	{
		bool InvalidChoice = false;
		char letter;
		player_number = (player_number % 2) ? 1 : 2;
		int PlayerChoice;

		cout << endl << "What's player " << player_number << "'s move?" << endl;
		cin >> PlayerChoice;

		while ((PlayerChoice < 1) || (PlayerChoice > 9))
		{
			cout << "That's an invalid choice! Please choose a number that is 1-9!" << endl;
			cin >> PlayerChoice;
		}

		PlayerChoice--;
		letter = (player_number == 1) ? 'X' : 'O';

		if (Pos[PlayerChoice] == '1' || Pos[PlayerChoice] == '2' || Pos[PlayerChoice] == '3' || Pos[PlayerChoice] == '4' || Pos[PlayerChoice] == '5' || Pos[PlayerChoice] == '6' || Pos[PlayerChoice] == '7' || Pos[PlayerChoice] == '8' || Pos[PlayerChoice] == '9')
		{
			Pos[PlayerChoice] = letter;
			PrintBoard(Pos);
		}
		else
		{
			cout << "That space is already taken!" << endl;
			player_number--;
		}
		i = checkwin(Pos);

		player_number++;
	}
	return i;
}

int checkwin(array <char, 9> Pos)
{
	if (Pos[0] == Pos[1] && Pos[1] == Pos[2])

		return 1;
	else if (Pos[3] == Pos[4] && Pos[4] == Pos[5])

		return 1;
	else if (Pos[6] == Pos[7] && Pos[7] == Pos[8])

		return 1;
	else if (Pos[0] == Pos[3] && Pos[3] == Pos[6])

		return 1;
	else if (Pos[1] == Pos[4] && Pos[4] == Pos[7])

		return 1;
	else if (Pos[2] == Pos[5] && Pos[5] == Pos[8])

		return 1;
	else if (Pos[0] == Pos[4] && Pos[4] == Pos[8])

		return 1;
	else if (Pos[2] == Pos[4] && Pos[4] == Pos[6])

		return 1;
	else if (Pos[0] != '1' && Pos[1] != '2' && Pos[2] != '3'
		&& Pos[3] != '4' && Pos[4] != '5' && Pos[5] != '6'
		&& Pos[6] != '7' && Pos[7] != '8' && Pos[8] != '9')

		return 0;
	else
		return -1;
}

int minimax(array <char, 9> newpos, int depth, int player, bool opp)
{
	int scale = 0;

	if (player == 1)
		scale = 10;
	else
		scale = -10;

	int score = scale*checkwin(newpos);

	if (score == -10 || score == 10 || score == 0)
		return score;

	if (opp)
	{
		int best = -1000;

		for (int i = 0; i < SIZE; i++)
		{
			if (newpos[i] != 'X' && newpos[i] != 'O')
			{
				char temp = newpos[i];

				newpos[i] = PlayerSymbol(player);

				best = max(best, minimax(newpos, depth + 1, Opposite(player), !opp));

				newpos[i] = temp;
			}
		}
	}
}

int Opposite(int x)
{
	if (x == 1)
		return 2;
	else
		return 1;
}

char PlayerSymbol(int x)
{
	if (x == 1)
		return 'X';
	else
		return 'O';
}