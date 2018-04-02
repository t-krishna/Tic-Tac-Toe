#include <iostream>
#include "board.h"

using namespace std;

//c++ -c main.cpp
//c++ -c board.cpp
//c++ -o game main.o board.o
//./game

/**
checks if user inputted an integer between 1-9
@param inp the raw input of the player
@return true if it is valid, false otherwise
*/
bool validEntry(char inp)
{
    if (isdigit(inp))
    {
        int inpInt = inp - '0';
        if ((inpInt > 0) && (inpInt < 10)) return true;
        else return false;
    }
    else return false;
}

/**
checks if the move is valid
@param inp the verified user input
@param b the game board
@return true if the move is valid, false otherwise
*/
bool validMove(char inp, char* b)
{
    if (validEntry(inp))
    {
        int inpInt = inp - '0';
        if ((b[inpInt - 1] != 'O') && (b[inpInt - 1] != 'X')) return true;
        else return false;
    }
    else return false;
    
}

/**
Prompts for player move verifying its a valid move
@param b the game board
@return integer index of the move
*/
int promptPlayer(Board game)
{
    
    char move[1];
    while (true)
    {
        cout << "PLAYER MOVE: ";
        cin >> move;
        
        if (validMove(move[0], game.board))
        {
            int moveInt = move[0] - '0';
            return moveInt - 1;
        }
        else cout << "Invalid Input." << endl;
    }
    game.playerTurn = false;
    game.currentPlayer = 'O';
}
 

int main()
{
    //determine first player
    char firstPlayer[1];
    bool valid = false;
    Board game(true);
    while (valid == false)
    {
        cout << "Do you want to go first? ('y' for yes, 'n' for no): ";
        cin >> firstPlayer;
        if (firstPlayer[0] == 'y' || firstPlayer[0] == 'Y')
        {
            game.playerTurn = true; //player going first
            game.currentPlayer = 'X';
            valid = true;
        }
        else if (firstPlayer[0] == 'n' || firstPlayer[0] == 'N')
        {
            game.playerTurn = false; //CPU going first
            game.currentPlayer = 'O';
            valid = true;
        }
        else
        {
            cout << "Invalid Input." << endl;
        }
    }
    
    
    //start game loop
    game.drawBoard();
    
    if (game.playerTurn == true) //if player goes first
    {
        game.changeTile(promptPlayer(game));
        game.drawBoard();
        cout << endl;
        
    }
    
    while (game.gameOver != true) //the game loop
    {
        game.moveCpu();
        game.drawBoard();
        
        game.checkGameOver();
        if (game.gameOver != true)
        {
            game.changeTile(promptPlayer(game));
            game.drawBoard();
            cout << endl;
        }
        
        if (game.gameOver == true)
        {
            int winner;
            winner = game.checkGameOver();
            if (winner == 0)
            {
                cout << "YOU LOSE." << endl;
            }
            else if (winner == 1)
            {
                cout << "YOU WON??? INCONCEIVABLE!!!" << endl;
            }
            else
            {
                cout << "DRAW." << endl;
            }
            
        }
        
    }
    
    
    
    
    
    
}