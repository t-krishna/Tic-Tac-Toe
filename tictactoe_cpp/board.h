#ifndef BOARD_H
#define BOARD_H

using namespace std;

//class declaration of the Board
//implimentation in board.cpp
class Board
{
private:
    //int minimax();
    static const char player = 'X'; //player is always X
    static const char cpu = 'O'; //cpu is always Y
    int choice;
    
    int checkWinConditions(char* b);
    int score(char* b);
    char switchPlayer(char c);
    int minimax(char* b, char current);
    

public:
    static char board[9];
    char currentPlayer;
    bool playerTurn; //0 for cpu, 1 for player
    bool gameOver;
    
    Board(bool turn);
    void drawBoard();
    void changeTile(int tile);
    void moveCpu();
    int checkGameOver();
};


#endif