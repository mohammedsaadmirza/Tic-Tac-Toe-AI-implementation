#include <iostream>
#include <iomanip>
#include <string>
#include <array>

// This is a program to play a single game of tic-tac-toe
// between either two human (non-AI) players or an AI.

using namespace std;

void PrintBoard(array <char, 9>);
int programprogress();
int checkwin(array <char, 9>);
int minimax(array <char, 9>, int, int);
int bestMove(array <char, 9>, int);
int Opposite(int);
char PlayerSymbol(int);

const int SIZE = 9;
array <char, SIZE> Pos = { '1', '2', '3', '4', '5', '6', '7', '8', '9' };
int player_number = 1;
int k = -11, result;
bool AI = false, first;

// Global variables used by 2 or more functions.
// Array had to be initialized with numbers instead of blank spaces
// because the check win function wouldn't work properly.

int main()
{
	string userinp;

	cout << "This is tic tac toe! Here's your board!" << endl;
	PrintBoard(Pos);

	cout << "Would you like to play versus an AI? (Y/N)" << endl;
	cin >> userinp;
	if (userinp[0] == 'Y')
	{
		cout << "Excellent! Would you like to start first, or second? (F/S)" << endl;
		cin >> userinp;
		if (userinp[0] == 'F')
		{
			cout << "You will start first!" << endl;
			first = false;
			player_number = 2;
		}

		else
		{
			cout << "The AI will start first!" << endl;
			first = true;
		}
		AI = true;
	}

	else
	{
		cout << "Excellent! Your game will start soon." << endl;
	}

	result = programprogress();
	player_number--;
	PrintBoard(Pos);

	if (result == 1)
		cout << endl << "Player " << player_number << " has won!!!\n";
	else if (result == 10)
		cout << endl << "The AI has won! Better luck next time!\n";
	// forgot to add the second "="
	else if (result == -10)
		cout << endl << "You beat the world's best AI! Congratulations!\n";
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
	while (k == -11 && AI)
	{
		bool InvalidChoice = false;
		char letter;
		//player_number = (player_number % 2) ? 1 : 2;
		int PlayerChoice;

		if (player_number == 2)
		{
			cout << endl << "What is your move?" << endl;
			cin >> PlayerChoice;

			while ((PlayerChoice < 1) || (PlayerChoice > 9))
			{
				cout << "That's an invalid choice! Please choose a number that is 1-9!" << endl;
				cin >> PlayerChoice;
			}

			PlayerChoice--;
			letter = (!first) ? 'X' : 'O';

			if (Pos[PlayerChoice] == '1' || Pos[PlayerChoice] == '2' || Pos[PlayerChoice] == '3' || Pos[PlayerChoice] == '4' || Pos[PlayerChoice] == '5' || Pos[PlayerChoice] == '6' || Pos[PlayerChoice] == '7' || Pos[PlayerChoice] == '8' || Pos[PlayerChoice] == '9')
			{
				Pos[PlayerChoice] = letter;
				PrintBoard(Pos);
			}
			/*else
			{
				cout << "That space is already taken!" << endl;
				player_number--;
			}*/
			k = checkwin(Pos);
			if (k != -11)
			{
				k = k * -10;
				cout << "chicken" << endl;
			}
			player_number = 1;
		}
		else
		{
			cout << endl << "The computer has made its move!" << endl;

			letter = (first) ? 'X' : 'O';
			if (first)
				PlayerChoice = bestMove(Pos, 1);
			else
				PlayerChoice = bestMove(Pos, 2);

			Pos[PlayerChoice] = letter;
			PrintBoard(Pos);

			k = checkwin(Pos);
			if (k != -11)
				k = k * 10;

			player_number = 2;
		}
	}

	while (k == -11 && !AI)
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
		k = checkwin(Pos);

		player_number++;
	}
	return k;
}

int checkwin(array <char, SIZE> Pos)
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
		return -11;
}

int minimax(array <char, SIZE> newpos, int depth, int player)
{
	int scale = 0;

	if ((player == 1 && first) || (player == 2 && !first))
		scale = -10;
	else
		scale = 10;
	// switched the scales
	int score = scale*checkwin(newpos);

	

	if (score == -10 || score == 10 || score == 0)
	{	
		if (score < 0)
			score += depth;
		else if (score > 0)
			score -= depth;

		return score;
	}

	if ((player == 1 && first) || (player == 2 && !first))
	{
		int best = -1000;

		for (int i = 0; i < SIZE; i++)
		{
			if (newpos[i] != 'X' && newpos[i] != 'O')
			{
				char temp = newpos[i];

				newpos[i] = PlayerSymbol(player);

				best = max(best, minimax(newpos, depth + 1, Opposite(player)));

				newpos[i] = temp;
			}
		}
		return best;
	}
	
	else
	{
		int best = 1000;

		for (int i = 0; i < SIZE; i++)
		{
			if (newpos[i] != 'X' && newpos[i] != 'O')
			{
				char temp = newpos[i];

				newpos[i] = PlayerSymbol(player);

				best = min(best, minimax(newpos, depth + 1, Opposite(player)));

				newpos[i] = temp;
			}
		}
		return best;
	}

}

int bestMove(array <char, SIZE> newpos, int player)
{
	int best = -1000;
	int bestpos = -1;

	for (int i = 0; i < SIZE; i++)
	{
		if (newpos[i] != 'X' && newpos[i] != 'O')
		{
			char temp = newpos[i];

			newpos[i] = PlayerSymbol(player);

			//opposite player instead of player
			int move = minimax(newpos, 0, Opposite(player));

			newpos[i] = temp;

			if (move > best)
			{
				bestpos = i;
				best = move;
			}
		}
	}
	cout << bestpos;
	return bestpos;
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