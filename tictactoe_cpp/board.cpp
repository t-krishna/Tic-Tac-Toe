#include <iostream>
#include <vector>
#include <algorithm>
#include "board.h"

using namespace std;

/**
constructs the empty board as an array
 */
char Board::board[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};

/** 
constructs the empty board
@param turn 0 is CPU goes first, 1 is player goes first
*/
Board::Board(bool turn)
{
    if(turn == false) 
    {
        playerTurn = false;
        currentPlayer = cpu;
    }
    else 
    {
        playerTurn = true;
        currentPlayer = player;
    }
    
    gameOver = false;
}

/**
prints the board into the terminal in a readable format
*/
void Board::drawBoard()
{
    int z = 0;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cout << board[z] << " ";
            z++;
        }
       cout << endl;
    }
}

/**
changes tile on the game board
@param tile index of the tile to be changed to current player
*/
void Board::changeTile(int tile)
{
    board[tile] = currentPlayer;
}

/**
switches currentPlayer from cpu to player and vise versa
@param c the current player
@return the switched player char
*/
char Board::switchPlayer(char c)
{
    if (c == cpu) 
    {
        return player;
    }
    else 
    {
        return cpu;
    }
}

/**
checks win conditions and returns the winner if the game is over
@param b the board
@return 0:cpu wins, 1:playerwins, 2:game-not-over, 3:draw
*/
int Board::checkWinConditions(char* b)
{
    if (
    (b[0] == b[1]) && (b[1] == b[2]) && (b[2] == cpu) ||
    (b[3] == b[4]) && (b[4] == b[5]) && (b[5] == cpu) ||
    (b[6] == b[7]) && (b[7] == b[8]) && (b[8] == cpu) ||
    (b[0] == b[3]) && (b[3] == b[6]) && (b[6] == cpu) ||
    (b[1] == b[4]) && (b[4] == b[7]) && (b[7] == cpu) ||
    (b[2] == b[5]) && (b[5] == b[8]) && (b[8] == cpu) ||
    (b[0] == b[4]) && (b[4] == b[8]) && (b[8] == cpu) ||
    (b[2] == b[4]) && (b[4] == b[6]) && (b[6] == cpu))
    {
        //gameOver = true;
        return 0;
    }
    
    else if (
    (b[0] == b[1]) && (b[1] == b[2]) && (b[2] == player) ||
    (b[3] == b[4]) && (b[4] == b[5]) && (b[5] == player) ||
    (b[6] == b[7]) && (b[7] == b[8]) && (b[8] == player) ||
    (b[0] == b[3]) && (b[3] == b[6]) && (b[6] == player) ||
    (b[1] == b[4]) && (b[4] == b[7]) && (b[7] == player) ||
    (b[2] == b[5]) && (b[5] == b[8]) && (b[8] == player) ||
    (b[0] == b[4]) && (b[4] == b[8]) && (b[8] == player) ||
    (b[2] == b[4]) && (b[4] == b[6]) && (b[6] == player))
    {
        //gameOver = true;
        return 1;
    }
    
    else
    {
        for (int i = 0; i < 9; i++)
        {
            if ((b[i] != cpu) && (b[i] != player))
            {
                return 2; //if empty cell then game not over
            }
        }
        
        return 3; //no empty cells its a draw
    }
    
    
}


/**
checks if the game.board game is over and changes game.gameOver
@return 0:cpu wins, 1:playerwins, 2:game-not-over, 3:draw
*/
int Board::checkGameOver()
{
    if (checkWinConditions(board) != 2)
    {
        gameOver = true;
        return checkWinConditions(board);
    }
    else return 2;
}

/**
checks the score of the board to be used for the minimax algorithm
@b the board to check
@return 10 if cpu wins, -10 if player wins, and 0 otherwise
*/
int Board::score(char* b)
{
    if (checkWinConditions(b) == 0) return 10;
    else if (checkWinConditions(b) == 1) return -10;
    else return 0;
}


/**
the minimax algorithm that calculates the best possible move
@param b board of the tictactoe game
@param current the currentplayer of the board
@return scores used in recursion. index of best move stored in game.choice
*/
int Board::minimax(char* b, char current)
{
    if (checkWinConditions(b) != 2) return score(b);
    vector<int> scores;
    vector<int> moves;
    
    //populate scores array
    for (int i = 0; i < 9; i++)
    {
        if ((b[i] != cpu) && (b[i] != player))
        {
            //duplicate array for a possible game state
            char possibleBoard[9];
            for (int j = 0; j < 9; j++)
            {
                possibleBoard[j] = b[j];
            }
            possibleBoard[i] = current;
            scores.push_back(minimax(possibleBoard,switchPlayer(current)));
            moves.push_back(i);
        }
    }
    
    //the min and max calculations
    if (current == cpu)
    {
        //find the index of the max score
        int highest = scores[0];
        int highestIndex = 0;
        for (int i = 0; i < scores.size(); i++)
        {
            if (highest < scores[i])
            {
                highestIndex = i;
                highest = scores[i];
            }
        }
        
        //store the move in class variable choice
        choice = moves[highestIndex];
        return scores[highestIndex];
    }
    else
    {
        //index of the min score
        int lowest = scores[0];
        int lowestIndex = 0;
        for (int i = 0; i < scores.size(); i++)
        {
            if (lowest > scores[i])
            {
                lowestIndex = i;
                lowest = scores[i];
            }
        }
        choice = moves[lowestIndex];
        return scores[lowestIndex];
    }
}

/**
moves the CPU using the minimax algorithm
*/
void Board::moveCpu()
{
    //do the minimax algorithm
    minimax(board, cpu);
    currentPlayer = cpu;
    changeTile(choice);
    cout << "CPU: " << choice + 1 << endl;

    currentPlayer = player;
    playerTurn = true;
}