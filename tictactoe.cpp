/* Baoheng Ling
   CCS5002
   Programming Assignment 1
*/

#include <stdio.h>
#include "tictactoe.h"
#include <string.h>

const int DIMENSION = 3;

int main() 
{
    Marker** board = createBoard();
    Marker turn = X;
    printf("To play a position use the following map to enter a position.\n");
    printf("-------------\n");
    for (int x = 0; x< 3; x++)
    {
        printf("| %d | %d | %d |\n", (DIMENSION*x)+1,(DIMENSION*x)+2,(DIMENSION*x)+3 );
        printf("-------------\n");
    }
    while (!isTie(board) && !hasWon(board, X) && !hasWon(board, O))
    {
        int posSelected = -1;
        bool validInput = false;
        
        while(!validInput) {
            printf("Player %c, enter the position you want to play.\n", toChar(turn));
            int success = scanf("%d", &posSelected);
            if (success < 0 || posSelected < 1 || posSelected > 9 || 
                board[(posSelected-1)/DIMENSION][(posSelected-1)%DIMENSION] != EMPTY)
            {
                continue;
            }
            validInput = true;
        }
        
        markTheBoard(board, turn, posSelected);
        printf("%s\n", getBoardDisplay(board));
        
        switch(turn)
        {
            case X:
            {
                turn = O;
                break;
            }
            case O:
            {
                turn = X;
                break;
            }
        }
    }
    
    if (isTie(board))
    {
        printf("The game ends in a tie.\n");
    }
    else if (hasWon(board, X))
    {
        printf("Player X has won.");
    }
    else
    {
        printf("Player O has won.");   
    }
    
}

/**
 *  This function creates a 3x3 array representing a tic tac toe board
 */
Marker** createBoard()
{
    Marker** board = new Marker*[DIMENSION];
	for(int i = 0; i < 3; i++)
	{
		board[i] = new Marker[DIMENSION];
		for(int j = 0; j < 3; j++)
		{
			board[i][j] = EMPTY;
		}
	}
	return board;
}

/**
 * This function converts an enum value to an equivalent character
 */ 
char toChar(Marker m)
{
    switch(m)
	{
		case X:
		{
			return 'X';
		}
		case O:
		{
			return 'O';
		}
		case EMPTY:
		{
			return ' ';
		}
	}
}

/**
 * This function returns a string that represents a board with the currently populated values
 */
char* getBoardDisplay(Marker** board)
{    
    char* displayBoard = new char[100];
	char line[] = "-------------\n";
	strcpy(displayBoard, line);
	char open[] = "| ";
	char middle[] = " | ";
	char close[] = " |\n";
    for (int x = 0; x < 3; x++)
    {
        strcat(displayBoard, open);
		displayBoard[strlen(displayBoard)] = toChar(board[x][0]);
		strcat(displayBoard, middle);
		
		displayBoard[strlen(displayBoard)] = toChar(board[x][1]);
		strcat(displayBoard, middle);
		
		displayBoard[strlen(displayBoard)] = toChar(board[x][2]);
		strcat(displayBoard, close);
        strcat(displayBoard, line);
    }
	return displayBoard;
}

/**
 * This function takes a position 1-9 and a marker.  It places that marker value on the board
 * at the given position
 */ 
void markTheBoard(Marker** board, Marker m, int pos)
{
	board[(pos-1)/DIMENSION][(pos-1)%DIMENSION] = m;
}

/**
 * This function returns true if the given marker has won the game, false otherwise.
 */
bool hasWon(Marker** board, Marker m)
{
	bool won = false;
	for(int i = 0; i < 3; i++)
	{
		if(board[i][0] == m && board[i][1] == m && board[i][2] == m)
		{
			won = true;
		}
		else if(board[0][i] == m && board[1][i] == m && board[2][i] == m){
			won =true;
		}
	}
	if(board[0][0] == m && board[1][1] == m && board[2][2] == m)
	{
		won = true;
	}
	else if(board[0][2] == m && board[1][1] == m && board[2][0] == m)
	{
		won = true;
	}
    return won;
}

/**
 * This function returns true if the given board is a tie, false otherwise.
 */
bool isTie(Marker** board)
{
   if(hasWon(board, X) || hasWon(board, O))
   {
	   return false;
   }
   int count = 0;
   	for(int i = 0; i < 3; i++)
	{
		for(int j = 0; j < 3; j++)
		{
			if(board[i][j] != EMPTY)
			{
				count++;
			}
		}
	}
	if(count == 9){return true;}
	return false;
}