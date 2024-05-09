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
    NONE = 0
};

class Board {
private:
    char board[3][3];

public:
    Board() {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                board[i][j] = ' ';
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
        WINNER_FLAG isWinner = NONE;
        for (int row = 0; row < 3; row++) {
            if (board[row][0] == board[row][1] && board[row][0] == board[row][2] && board[row][0] == 'X'||
                board[row][0] == board[row][1] && board[row][0] == board[row][2] && board[row][0] == 'O') {
                isWinner = WINNER_FLAG::WIN;
            }
        }
        for (int col = 0; col < 3; col++) {
            if (board[0][col] == board[1][col] && board[1][col] == board[2][col] && board[0][col] == 'X'||
                board[0][col] == board[1][col] && board[1][col] == board[2][col] && board[0][col] == 'O') {
                isWinner = WINNER_FLAG::WIN;
            }
        }

        if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] == 'X' ||
            board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] == 'O') {
            isWinner = WINNER_FLAG::WIN;
        }
        if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] == 'X' ||
            board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] == 'O') {
            isWinner = WINNER_FLAG::WIN;
        }
        return static_cast<int>(isWinner);
    }
};

class Tictactoe {
private:
    Board board;
    Player playerOne;
    Player playerTwo;
    bool winner = false;
    bool currentPlayer = false;

public:
    Tictactoe() {
        board = Board();
    }

public:
    void Start() {
        board.DrawBoard();

        std::cout << "First player is O" << std::endl;
        playerOne.SetPlayerInput('O');
        playerTwo.SetPlayerInput('X');

        int input;
        while(!winner){
            std::cout << "Please pick where to put your input 0-8: ";
            
            while (!(std::cin >> input) && input >= 0 && input <= 8) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                board.DrawBoard();
                std::cout << "Invalid input. Please enter an integer: ";
            }
            
            if (!currentPlayer) {
                board.Input(input, playerOne.GetPlayerInput());
            }
            else {
                board.Input(input, playerTwo.GetPlayerInput());
            }
           
            int checkValue = board.CheckWinner();
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