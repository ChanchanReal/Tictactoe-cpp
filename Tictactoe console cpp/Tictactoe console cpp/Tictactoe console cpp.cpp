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
    NONE = 0
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
    int CheckWinner(char playerInput) {
        WINNER_FLAG isWinner = WINNER_FLAG::NONE;
        for (int row = 0; row < 3; row++) {
            if (board[row][0] == board[row][1] && board[row][0] == board[row][2] && board[row][0] == playerInput) {
                isWinner = WINNER_FLAG::WIN;
            }
        }
        for (int col = 0; col < 3; col++) {
            if (board[0][col] == board[1][col] && board[0][col] == board[2][col] && board[0][col] == playerInput) {
                isWinner = WINNER_FLAG::WIN;
            }
        }

        if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] == playerInput) {
            isWinner = WINNER_FLAG::WIN;
        }
        if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] == playerInput) {
            isWinner = WINNER_FLAG::WIN;
        }
        return static_cast<int>(isWinner);
    }
    int Minimax(int depth, bool isAI) {
        if (CheckWinner('X') == 1) {
            return 1;
        }
        if (CheckWinner('O') == 1) {
            return -1;
        }
        if (depth < 0) {
            return 0;
        }
            if (isAI) {
                int bestScore = INT_MIN;
                for (int row = 0; row < 3; row++) {
                    for (int col = 0; col < 3; col++) {
                        if (board[row][col] == ' ') {
                            board[row][col] = 'X';
                            int score = Minimax(depth - 1, false);
                            board[row][col] = ' ';
                            bestScore = std::max(score, bestScore);
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
                            int score = Minimax(depth - 1, true);
                            board[row][col] = ' ';
                            bestScore = std::min(score, bestScore);
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
                    int score = Minimax(availableMove, false);
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
                checkValue = board.CheckWinner('X');
            }
            else{
                while (!(std::cin >> input) && input >= 0 && input <= 8) {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    board.DrawBoard();
                    std::cout << "Invalid input. Please enter an integer: ";
                }
                board.Input(input, playerOne.GetPlayerInput());
                checkValue = board.CheckWinner('O');
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