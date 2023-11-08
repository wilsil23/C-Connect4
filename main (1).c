#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h> // for usleep function
#include "slist.h"

char board[6][8];
int NUM_ROWS = 6;
int NUM_COLS = 8;
char player = 'R';
int WinCondition = 0;

void EmptyBoard() {
    for (int i = 0; i < NUM_ROWS; i++) {
        for (int j = 0; j < NUM_COLS; j++) {
            board[i][j] = ' ';
        }
    }
}

void PrintBoard() {
    for (int i = 0; i < NUM_ROWS; i++) {
        printf("\n");
        for (int j = 0; j < NUM_COLS; j++) {
            printf("|%c", board[i][j]);
        }
    }
    printf("\n");
}

int GetColumn() {
    int column;

    printf("%s to play. Pick a column (1-7):", player == 'R' ? "Yellow" : "Red");

    int num_values = scanf("%d", &column);
    while (getchar() != '\n');

    while (num_values != 1 || column < 1 || column > NUM_COLS-1) {
        printf("Make sure the column is between 1 and 7: \n");
        num_values = scanf("%d", &column);
        while (getchar() != '\n');
    }
    return column - 1;
}

void CheckWinner() {
     for (int row = 0; row < NUM_ROWS; row++) {
        for (int col = 0; col <= NUM_COLS - 4; col++) {
            char cur = board[row][col];
            if (cur != ' ' && cur== board[row][col + 1] &&
                cur == board[row][col + 2] && cur == board[row][col + 3]) {
                WinCondition = 1;
                return printf("%c is the winner!", player);
            }
        }
    }

    for (int row = 0; row <= NUM_ROWS - 4; row++) {
        for (int col = 0; col < NUM_COLS; col++) {
            char cur = board[row][col];
            if (cur != ' ' && cur == board[row + 1][col] &&
                cur == board[row + 2][col] && cur == board[row + 3][col]) {
                WinCondition = 1;
                return printf("%c is the winner!", player);
            }
        }
    }

    for (int row = 0; row <= NUM_ROWS - 4; row++) {
        for (int col = 0; col <= NUM_COLS - 4; col++) {
            char cur= board[row][col];
            if (cur != ' ' && cur == board[row + 1][col + 1] &&
                cur == board[row + 2][col + 2] && cur == board[row + 3][col + 3]) {
                WinCondition = 1;
                return printf("%c is the winner!", player);
            }
        }
    }
}


int CheckBoardFull() {
    for(int i = 0; i<NUM_ROWS-1;i++){
        for(int k = 0; k<NUM_COLS-1;k++){
            if(board[i][k]==' '){
               return 0; 
            }
        }
    }
    return 1;
}
int GetEmptyRow(int col) {
    for(int i=NUM_ROWS; i>=0; i--){
        if(board[i][col]==' '){
            return i;
        }
    }
    return printf("Column Full!");
}


void PlayConnectFour() {
    bool game_over=false;
    
    while (!game_over)
    {
        int full = CheckBoardFull();
        CheckWinner();
        if (WinCondition==1){
            game_over=true;
            printf("Game Over!");
            break;
        }
        if(CheckBoardFull()==1){
            game_over=true;
            printf("All rows and columns full its a draw! game over!");
            break;
        }
        PrintBoard();
        int col = GetColumn(player);
        int row = GetEmptyRow(col);
        player = (player == 'R' ? 'Y' : 'R');
        board[row][col]=player;
    }

}

void replayGame(SList* moveList) {
    EmptyBoard();
    printf("Replaying the game:\n");
    Node* current = moveList->head;
    char currentPlayer = 'R';
    int moves[moveList->size];
    int moveIndex = 0;

    while (current != NULL) {
        int move = current->move;
        moves[moveIndex++] = move;
        current = current->next;
        usleep(500000);
    }
    printf("Replay complete!\n");
}

int main() {
    SList* moveList = createSList();
    EmptyBoard();
    int WinCondition = 0;
    printf("Welcome! Press 'q' to quit or 'r' to replay or any other key to continue:\n");

    char c;
    bool done = false;

    while (!done) {
        scanf(" %c", &c);

        if (c == 'q') {
            done = true;
            printf("Bye Bye!\n");
        } else if (c == 'r') {
            replayGame(moveList);
            printf("Press 'q' to quit or 'r' to replay or any other key to continue:\n");
        } else {
            int col = GetColumn();
            insertMove(moveList, col);
            PlayConnectFour();
            printf("Press 'q' to quit or 'r' to replay or any other key to continue:\n");
        }
    }
    freeSList(moveList);
    return 0;
}