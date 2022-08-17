#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <sstream>
#include <time.h>
#include <stdlib.h>

using namespace std;

/*
 0 | X | 0
-----------
 X | 0 | X
-----------
 0 | X | 0
*/

//Asks who is going first? Checks for valid input.
string goingFirst() {
	bool isGoodInput = false;
	string firstPlayer = "";

	do {
		firstPlayer = "";
		cout << "Hello player, who will go first? You or the computer?" << endl << "Please type \"me\" or \"computer\"." << endl;
		getline(cin, firstPlayer);

		if (firstPlayer == "me" || firstPlayer == "computer") {
			isGoodInput = true;
		}

		if (!isGoodInput) {
			cout << endl << "Invalid input" << endl << endl;
		}

	} while (!isGoodInput);

	return firstPlayer;
}

string cpuDiff() {
	bool isGoodInput = false;
	string difficulty = "";

	do {
		difficulty = "";
		cout << "What level of difficulty should the computer be on?" << endl << "Please type \"easy\" or \"medium\"." << endl;
		getline(cin, difficulty);

		if (difficulty == "easy" || difficulty == "medium") {
			isGoodInput = true;
		}

		if (!isGoodInput) {
			cout << endl << "Invalid input" << endl << endl;
		}

	} while (!isGoodInput);

	return difficulty;
}

//Asks if you will Play again? Checks for valid input.
string playAgain() {
	bool isGoodInput = false;
	string playAgainAnswer = "";

	do {
		playAgainAnswer = "";
		cout << "Will you play again?" << endl << "Please type \"yes\" or \"no\"." << endl;
		getline(cin, playAgainAnswer);

		if (playAgainAnswer == "yes" || playAgainAnswer == "no") {
			isGoodInput = true;
		}

		if (!isGoodInput) {
			cout << endl << "Invalid input" << endl << endl;
		}
	} while (!isGoodInput);

	return playAgainAnswer;
}

void easyCPU(vector<char>& board) {
	//Computer's Turn
	for (int i = 0; i < board.size(); i++) {
		if (board[i] != 'X' && board[i] != 'O') {
			board[i] = 'O';
			break;
		}
	}
	cout << "Computer's turn" << endl;
}

void mediumCPU(vector<char>& board) {
	srand(time(0));

	bool isGoodInput = false;

	while (!isGoodInput) {
		int input = (rand() % 9) + 1;

		stringstream ss;
		ss << input;
		string str = ss.str();

		if (board[input - 1] == str[0]) {
			board[input - 1] = 'O';
			isGoodInput = true;
		}

	}

	cout << "Computer's turn" << endl;

}

void HardCPU(vector<char>& board) {

}

int checkGameOver(vector<char>& board) {
	//Combinations to check for: 123, 456, 789, 147, 258, 369, 159, 357, and all full.
	bool isGameOver = false;
	int winner = -1;
	vector<int> combos = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 0, 3, 6, 1, 4, 7, 2, 5, 8, 0, 4, 8, 2, 4, 6 };
	for (int i = 0; i < combos.size(); i += 3) {
		if ((board[combos[i]] == board[combos[i + 1]]) && (board[combos[i]] == board[combos[i + 2]])) {
			isGameOver = true;
			if (board[combos[i]] == 'X') {
				return 0;
			}
			else if (board[combos[i]] == 'O') {
				return 1;
			}
		}
	}
	//Check if all are full
	isGameOver = true;
	for (int i = 0; i < board.size(); i++) {
		if (board[i] != 'X' && board[i] != 'O') {
			isGameOver = false;
		}
	}
	if (isGameOver) {
		return 2;
	}
	return -1;
}

//Asks for input during the game. Checks for valid input.
int getValidTurnInput(vector<char>& board) {

	bool isGoodInput = false;
	int num = 0;

	while (!isGoodInput) {
		cout << "Please type a number, 1-9 to select where to place your token." << endl;
		string input = "";
		getline(cin, input);

		if (input.size() == 1 && isdigit(input[0])) {
			stringstream ss(input);
			num = 0;
			ss >> num;
		}
		if (board[num - 1] == input[0]) {
			isGoodInput = true;
		}
		if (!isGoodInput) {
			cout << endl << "Invalid input" << endl << endl;
		}
	}

	cout << "You selected " << num << endl;
	return num;
}

void printBoard(vector<char> board) {
	cout << " " << board[0] << " | " << board[1] << " | " << board[2] << " " << endl;
	cout << "-----------" << endl;
	cout << " " << board[3] << " | " << board[4] << " | " << board[5] << " " << endl;
	cout << "-----------" << endl;
	cout << " " << board[6] << " | " << board[7] << " | " << board[8] << " " << endl;
	cout << endl;
}

/* Returns 0 if player won, returns 1 if computer won, returns a 2 if the game is a tie */
int playGame(string firstPlayer, string difficulty) {
	int winner = -1;
	bool isGameOver = false;
	vector<char> board = { '1', '2', '3', '4', '5', '6', '7', '8', '9' };

	printBoard(board);
	cout << "The computer is O's and the player is X's." << endl;
	while (!isGameOver) {

		//Players Turn
		if (firstPlayer == "me") { //If statement allows computer to go first when chosen.
			int num = getValidTurnInput(board);
			board[num - 1] = 'X';
			printBoard(board);

			//Check if game is over
			winner = checkGameOver(board);
			if (winner != -1) {
				isGameOver = true;
				break;
			}
		}
		else {
			firstPlayer = "me";
		}

		//Computer's Turn
		if (difficulty == "easy") {
			easyCPU(board);
		}
		if (difficulty == "medium") {
			mediumCPU(board);
		}
		printBoard(board);

		//Check if game is over
		winner = checkGameOver(board);
		if (winner != -1) {
			isGameOver = true;
			break;
		}
	}

	return winner;
}


int main() {

	bool isPlayAgain = false;
	string firstPlayer = "";
	string playAgainAnswer = "";
	string difficulty = "";
	int winner;

	do {
		isPlayAgain = false;
		firstPlayer = goingFirst();
		difficulty = cpuDiff();
		winner = playGame(firstPlayer, difficulty);

		if (winner == 0) {
			cout << "Congratulations! You won the game!" << endl;
		}
		else if (winner == 1) {
			cout << "Sorry, the computer won. Better luck next time!" << endl;
		}
		else {
			cout << "Good game! It's a tie!" << endl;
		}

		playAgainAnswer = playAgain();

		if (playAgainAnswer == "yes") {
			isPlayAgain = true;
		}

		if (isPlayAgain == false) {
			cout << endl << "Thanks for playing!" << endl;
		}

	} while (isPlayAgain == true);
	return 0;
}