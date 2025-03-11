#include <stdio.h>
#include <windows.h>
#include <conio.h>
char player = '1';
int column, row;
int turn = 0;
int start = 1;


char board[5][5] = {{' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' '},
                    {' ', ' ', ' ', ' ', ' '}};

char boardBack[5][5] = {{' ', ' ', ' ', ' ', ' '},
                        {' ', ' ', ' ', ' ', ' '},
                        {' ', ' ', ' ', ' ', ' '},
                        {' ', ' ', ' ', ' ', ' '},
                        {' ', ' ', ' ', ' ', ' '}};



void displayBoard();
void moveAgent(int row,int column, char player);
void checkWin();

void clearXPosition();
void eatAgent(int row,int column,int rowE,int columnE);


int waitForInput(int *input, int timeoutSec) {
    DWORD startTime = GetTickCount();
    while (GetTickCount() - startTime < timeoutSec * 1000) {
        if (_kbhit()) {
            scanf("%d", input);
            return 1;
        }
        Sleep(50);
    }
    return 0;
}

int main(void) {
    board[0][2] = 'J';
    board[0][1] = 'Q';
    board[0][3] = 'K';
    board[4][1] = 'J';
    board[4][2] = 'Q';
    board[4][3] = 'K';
    board[1][0] = '^';
    board[2][1] = '>';
    board[3][4] = 'v';
    boardBack[0][1] = '1';
    boardBack[0][3] = '1';
    boardBack[0][2] = '1';
    boardBack[4][1] = '2';
    boardBack[4][2] = '2';
    boardBack[4][3] = '2';

    while (start == 1) {
        checkWin();
        displayBoard();
        printf("Player %c, select agent\n", player);

        printf("Enter the row [1-5]: ");
        fflush(stdout);
        if (!waitForInput(&row, 3)) {
            printf("\nTime out! Switching turn to Player %c.\n", player == '1' ? '2' : '1');
            player = (player == '1') ? '2' : '1';
            continue;
        }

        printf("Enter the column [1-5]: ");
        fflush(stdout);
        if (!waitForInput(&column, 10)) {
            printf("\nTime out! Switching turn to Player %c.\n", player == '1' ? '2' : '1');
            player = (player == '1') ? '2' : '1';
            continue;
        }

        moveAgent(row - 1, column - 1, player);
        player = (player == '1') ? '2' : '1';
    }
}


void displayBoard() {
    printf("\n  ____________________\n");
    for (int i = 0; i < 5; i++) {

        for (int j = 0; j < 5; j++) {

            if(j == 0){
                int num = i+1;
                printf("%d| %c ",num, board[i][j]);
            }
            else{
                printf("| %c ", board[i][j]);
            }
        }
        printf("|");
        printf("\n  ____________________\n");

    }
    printf("  1   2   3   4   5\n");
}


void moveAgent(int row,int column, char player) {

    int movement = 0;

        if (boardBack[row][column] == player) {

            printf("\n1)Up\n2)Left\n3)Right\n4)Down\nSelect your movement :");
            scanf("%d", &movement);

            switch (movement)
            {
            case 1:
                eatAgent(row, column, row - 1, column);
                break;

            case 2:
                eatAgent(row, column, row, column - 1);
                break;

            case 3:
                eatAgent(row, column, row, column + 1);
                break;

            case 4:
                eatAgent(row, column, row + 1, column);
                break;
            }  
                turn++;
        }

        else{
            printf("Not your agent please select again !!!\n");
        }
}

void  checkWin(){
    int count1 = 0;
    int count2 = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (boardBack[i][j] == '1' ) {
                count1++;
            }
            else if(boardBack[i][j] == '2' ){
                count2++;
            }
        }
    }

    if(count1 == 0 && count2 == 0){
        printf("!!!! Draw!!!!");
        displayBoard();
        start = 0;
    }
    else if(count1 == 0){
        printf("!!!! Plyer 2 WIN !!!!");
        displayBoard();
        start = 0;
    }
    else if(count2 == 0){
        printf("!!!! Plyer 1 WIN !!!!");
        displayBoard();
        start = 0;
    }
}


void eatAgent(int row,int column,int rowE,int columnE){

    if (board[rowE][columnE] == '^')
    {
        board[rowE-1][columnE] = board[row][column];
        board[row][column] = ' ';
        boardBack[rowE-1][columnE] = boardBack[row][column];
        boardBack[row][column] = ' ';
    }
    else if (board[rowE][columnE] == '>')
    {
        board[rowE][columnE+1] = board[row][column];
        board[row][column] = ' ';
        boardBack[rowE][columnE+1] = boardBack[row][column];
        boardBack[row][column] = ' ';
    }
    else if (board[rowE][columnE] == 'v')
    {
        board[rowE+1][columnE] = board[row][column];
        board[row][column] = ' ';
        boardBack[rowE+1][columnE] = boardBack[row][column];
        boardBack[row][column] = ' ';
    }
    else if(board[rowE][columnE] == ' ' || 
        (board[rowE][columnE] == 'K' && board[row][column] == 'J') || 
        (board[rowE][columnE] == 'J' && board[row][column] == 'Q') || 
        (board[rowE][columnE] == 'Q' && board[row][column] == 'K')){
        
        board[rowE][columnE] = board[row][column];
        board[row][column] = ' ';
        boardBack[rowE][columnE] = boardBack[row][column];
        boardBack[row][column] = ' ';
    }

    else if (board[rowE][columnE] == board[row][column])
    {
        board[rowE][columnE] = ' ';
        board[row][column] = ' ';
        boardBack[rowE][columnE] = ' ';
        boardBack[row][column] = ' ';
    }

    else
    {
        printf("!!! Please select again !!!\n\n");
    }
}

