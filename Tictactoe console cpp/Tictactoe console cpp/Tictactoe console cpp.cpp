// Tictactoe console cpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>



class Player {
private:
    char playerInput;

public:
    void SetPlayerInput(char input) {
        if (input != NULL) {
            playerInput = input;
        }
    }
    char GetPlayerInput() {
        return playerInput;
    }
};

enum WINNER_FLAG {
    WIN = 1,
    LOSE = -1,
    NONE = 0,
    DRAW = -2
};

class Board {
public:
    char board[3][3];
    Board() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                board[i][j] = ' ';
                ;
            }
        }
    }

public:
    void Input(int pos, char player) {
        int i = 0;
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                if (i == pos && board[row][col] == ' ') {
                    board[row][col] = player;
                }
                i++;
            }
        }
    }
    void DrawBoard() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                std::cout << "|" << board[i][j];
            }
            std::cout << "|\n";
        }
    }
    int CheckWinner() {

        for (int row = 0; row < 3; row++) {
            if (board[row][0] == board[row][1] && board[row][0] == board[row][2] && board[row][0] != ' ') {
                return board[row][0] == 'X' ? 1 : -1;
            }
        }
        for (int col = 0; col < 3; col++) {
            if (board[0][col] == board[1][col] && board[0][col] == board[2][col] && board[0][col] != ' ') {
                return board[0][col] == 'X' ? 1 : -1;
            }
        }

        if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ') {
            return board[0][0] == 'X' ? 1 : -1;
        }
        if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ') {
            return board[0][2] == 'X' ? 1 : -1;
        }

        int counter = 0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] != ' ') {
                    counter++;
                }
            }
        }

        if (counter == 9)
            return 0;

        return -2;
    }
    int Minimax(int depth, int alpha, int beta, bool isAI) {
        int result = CheckWinner();
        if (result != -2) {
            return result;
        }
        if (depth == 0) {
            return 0;
        }
            if (isAI) {
                int bestScore = INT_MIN;
                for (int row = 0; row < 3; row++) {
                    for (int col = 0; col < 3; col++) {
                        if (board[row][col] == ' ') {
                            board[row][col] = 'X';
                            int score = Minimax(depth - 1, alpha, beta, false);
                            board[row][col] = ' ';
                            bestScore = std::max(score, bestScore);
                            alpha = std::max(alpha, score);
                            if (beta <= alpha) {
                                break;
                            }
                        }
                    }
                }
                return bestScore;
            }
            else {
                int bestScore = INT_MAX;
                for (int row = 0; row < 3; row++) {
                    for (int col = 0; col < 3; col++) {
                        if (board[row][col] == ' ') {
                            board[row][col] = 'O';
                            int score = Minimax(depth - 1, alpha, beta, true);
                            board[row][col] = ' ';
                            bestScore = std::min(score, bestScore);
                            beta = std::min(beta, score);
                            if (beta <= alpha) {
                                break;
                            }
                        }
                    }
                }
                return bestScore;
            }
        
    }
    void Bestmove(int availableMove) {
        int bestMove[2];
        int bestScore = INT_MIN;
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                if (board[row][col] == ' ') {
                    board[row][col] = 'X';
                    int score = Minimax(availableMove, INT_MIN, INT_MAX, false);
                    board[row][col] = ' ';
                    if (score >= bestScore) {
                        bestScore = score;
                        bestMove[0] = row;
                        bestMove[1] = col;
                    }
                }
            }
        }
        board[bestMove[0]][bestMove[1]] = 'X';
    }
};

class Tictactoe {
private:
    Board board;
    Player playerOne;
    Player playerTwo;
    bool winner = false;
    bool currentPlayer = false;
    int playerTurns = 9;

public:
    void Start() {
        board.DrawBoard();

        std::cout << "First player is O" << std::endl;
        playerOne.SetPlayerInput('O');
        playerTwo.SetPlayerInput('X');
        int checkValue;

        int input;
        while(!winner){
            std::cout << "Please pick where to put your input 0-8: ";
            if (currentPlayer) {
                board.Bestmove(playerTurns);
                checkValue = board.CheckWinner();
            }
            else{
                while (!(std::cin >> input) && input >= 0 && input <= 8) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    board.DrawBoard();
                    std::cout << "Invalid input. Please enter an integer: ";
                }
                board.Input(input, playerOne.GetPlayerInput());
                checkValue = board.CheckWinner();
            }
            playerTurns--;
            system("CLS");
            board.DrawBoard();
            
            if (!currentPlayer && checkValue == 1) {
                std::cout << "Winner is Player one !!!!";
                winner = true;
            }
            else if (currentPlayer && checkValue == 1) {
                std::cout << "Winner is Player two !!!!";
                winner = true;
            }

            currentPlayer = !currentPlayer;
            
        }
    }
};

int main()
{
    Tictactoe game;
    game.Start();
}