/* Tic-Tac-Toe */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define SIZE 3

//display game layout
void boardLayout() {
    for (int i=0, n=1; i<SIZE; i++) {
        for (int j=0; j<SIZE; j++) {
            printf("(%d,%d)",i+1,j+1);
            if (j < SIZE-1) printf("|");
            n++;
        }
        if (i < SIZE-1) printf("\n-----------------\n");
    }
    printf("\n");
}

//initialize game
void initializeBoard(char board[][SIZE]) {
    for (int i=0, n=1; i<SIZE; i++) {
        for (int j=0; j<SIZE; j++) {
            board[i][j] = '-';
            n++;
        }
    }
}

//display game 
void displayBoard(char board[][SIZE]) {
    printf("\n");
    for (int i=0; i<SIZE; i++) {
        for (int j=0; j<SIZE; j++) {
            printf(" %c ",board[i][j]);
            if (j < SIZE-1) printf("|");
        }
        if (i < SIZE-1) printf("\n-----------\n");
    }
    printf("\n");
}

//check if any moves remain
bool movesLeft(char board[][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == '-') {
                return true; //there are moves left
            }
        }
    }
    return false; //no moves left
}

//check if a player has won
char checkWinner(char board[][SIZE]) {
	//check rows
    for (int i = 0; i < SIZE; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != '-') {
            return board[i][0]; //return the winning character ('x' or 'o')
        }
    }
    //check columns
    for (int j = 0; j < SIZE; j++) {
        if (board[0][j] == board[1][j] && board[1][j] == board[2][j] && board[0][j] != '-') {
            return board[0][j]; //return the winning character
        }
    }
    //check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != '-') {
        return board[0][0]; //return the winning character
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != '-') {
        return board[0][2]; //return the winning character
    }

    // check for tie
    if (movesLeft(board) == false) {
        return 't';
    } else {
        return '-';
    }
}

//move player
void playerMove(char player, char board[][SIZE]) {
    bool move;
    int x,y;
    int count = 0;
    
    do {
        //prompt user for input
        if (count==0) {
            printf("player %c, choose your position: x,y (i.e 1,2)\n",player);
            fflush(stdout);
        }
        scanf("%d,%d", &x,&y);
        //adjust for zero indexing
        x--;
        y--;
        //check for valid input (two edge cases)
        if (x<SIZE && x>=0 && y<SIZE && y>=0) {
            if (board[x][y] == '-') {
                board[x][y] = player;
                move = true; //move valid
            } else {
                printf("invalid move. cell already occupied.\n");
                fflush(stdout);
                move = false; 
            
            }
        } else {
            printf("invalid position. enter x and y between 1 and %d.\n",SIZE);
            fflush(stdout);
            move = false;
        }
        count++;

    } while (!move);
}

int main(void) {
    char board[SIZE][SIZE];
    char player;
    char winner;

    //choose starting player by random
    srand(time(0));
    int num = rand() % 2; //generates 0 or 1
    if (num == 0) {
        player = 'x';
    } else {
        player = 'o';
    }

    //game setup
    boardLayout();
    initializeBoard(board); 

    //begin game
    while (true) {

        //add player's move
        playerMove(player,board);

        //check for winner
        winner = checkStatus(board);
        if (winner == 'x' || winner == 'o') {
            displayBoard(board);
            printf("player %c has won!!!\n",winner);
            break;
        } else if (winner == 't') {
            displayBoard(board);
            printf("it's a draw!!\n");
            break;
        }

        //switch player
        if (player == 'x') {
            player = 'o';
        } else {
            player = 'x';
        }

        displayBoard(board);//display board after every move
    }
    return 0;
}


