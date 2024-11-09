#include <stdlib.h>
#include<stdio.h>
#include <stdbool.h>

#define SIZE 3
char computer = 'x';
char human = 'o';

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
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) {
            if (board[i][0] == computer) {
                return 'w';
            } else if (board[i][0] == human){
                return 'l';
            }
        }
    }

    //check columns
    for (int j = 0; j < SIZE; j++) {
        if (board[0][j] == board[1][j] && board[1][j] == board[2][j]) {
            if (board[0][j] == computer) {
                return 'w';
            } else if (board[0][j] == human){
                return 'l';
            }
        }
    }

    //check diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == computer) {
            return 'w';
        } else if (board[0][0] == human){
            return 'l';
        }
    }

    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == computer) {
            return 'w';
        } else if (board[0][2] == human){
            return 'l';
        }
    }
    // check for tie
    if (movesLeft(board) == false) {
        return 't';
    } else {
        return 'c';
    }
}

//determine optimal move for computer using minimax algorithm 
int minimax(char board[][SIZE], bool isMaximizing, int depth, int count) {
    //check if terminal state is reached then return score
    char result = checkWinner(board);
    if (result != 'c') {
        count ++;
        if (result == 'w') {
            return 10 - depth;
        } else if (result == 'l'){
            return -10 + depth;
        } else if (result == 't') {
            return 0;
        }
    } 

    if (isMaximizing) {

        int bestScore = -1000;
        for (int i=0; i<SIZE; i++) {
            for (int j=0; j<SIZE; j++) {
                if (board[i][j] == '-') {
                    board[i][j] = computer;
                    int score = minimax(board,false,depth+1,count);
                    board[i][j] = '-';
                    if (score > bestScore) {
                        bestScore = score;
                    }
                }
            }
        }
        return bestScore;

    } else {

        int bestScore = 1000;
        for (int i=0; i<SIZE; i++) {
            for (int j=0; j<SIZE; j++) {
                if (board[i][j] == '-') {
                    board[i][j] = human; 
                    int score = minimax(board,true,depth+1,count);
                    board[i][j] = '-';
                    if (score < bestScore) {
                        bestScore = score;
                    }
                }
            }
        }
        return bestScore;
    }
}

//move computer
void computerMove(char board[][SIZE], int count) {
    int bestScore = -1000;
    int cMove[] = {0,0};
    for (int i=0; i<SIZE; i++) {
        for (int j=0; j<SIZE; j++) {
            if (board[i][j] == '-') {
                board[i][j] = computer;
                int score = minimax(board,false,0,count);
                board[i][j] = '-';
                if (score > bestScore) {
                    bestScore = score;
                    cMove[0] = i;
                    cMove[1] = j;
                }
            }
        }
    }
    printf("%d games searched", count);
    printf("\n%d,%d\n",cMove[0],cMove[1]);
    board[cMove[0]][cMove[1]] = computer; //play best move
}

//move human
void humanMove(char board[][SIZE]) {
    int count = 0;
    bool input;
    int hMove[] = {0,0};
    do {
        //prompt user for input
        if (count==0) {
            printf("make your move: x,y (i.e 1,2)\n");
            fflush(stdout);
        }
        scanf("%d,%d",&hMove[0],&hMove[1]);
        //adjust for zero indexing
        hMove[0]--;
        hMove[1]--;
        //check for valid input (two edge cases)
        if (hMove[0]<SIZE && hMove[0]>=0 && hMove[1]<SIZE && hMove[1]>=0) {
            if (board[hMove[0]][hMove[1]] == '-') {
                board[hMove[0]][hMove[1]] = human;
                input = true; //input valid
            } else {
                printf("invalid input. cell already occupied.\n");
                fflush(stdout);
                input = false; 
            }
        } else {
            printf("invalid position. enter x and y between 1 and %d.\n",SIZE);
            fflush(stdout);
            input = false;
        }
        count++;

    } while (!input);
}

//main routine
int main(void) {

    char board[SIZE][SIZE] = {

        { '-', '-', '-' }, 
        { '-', '-', '-' }, 
        { '-', '-', '-' } 
    };
    char winner;
    bool player = true;
    int count = 0; //number of games searched
    
    boardLayout(board);

    while (true) {

        if (player) {
            computerMove(board,count);
        } else {
            humanMove(board);
        }        
        //check for winner
        winner = checkWinner(board);
        if (winner == 'w') {
            displayBoard(board);
            printf("computer has won!!!\n");
            break;
        } else if (winner == 'l') {
            displayBoard(board);
            printf("human has won!!!\n");
            break;
        } else if (winner == 't') {
            displayBoard(board);
            printf("it's a draw!!!\n");
            break;
        } else {
            displayBoard(board);
        }

        player = !player;
        count = 0;
    }
    return 0;
}