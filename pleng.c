//jชนะqแบบยังไม่โดน
//

#include <stdio.h>
#include <unistd.h>    // สำหรับ sleep()
#include <sys/select.h> // สำหรับ select()
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


int main(void){
    int value;
    struct timeval timeout;

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
        
        struct timeval timeout;
        fd_set fds;
        FD_ZERO(&fds);
        FD_SET(STDIN_FILENO, &fds);
        
        timeout.tv_sec = 3;  
        timeout.tv_usec = 0;
    
        printf("Enter the row [1-5]: ");
        fflush(stdout);
        
        int ret = select(STDIN_FILENO + 1, &fds, NULL, NULL, &timeout);
        if (ret > 0) {
            scanf("%d", &row);
        } else {
            printf("\nTime out! Switching turn to Player %c.\n", player == '1' ? '2' : '1');
            player = (player == '1') ? '2' : '1';
            continue;
        }
    
        FD_ZERO(&fds);
        FD_SET(STDIN_FILENO, &fds);
        timeout.tv_sec = 10;  
        timeout.tv_usec = 0;
    
        printf("Enter the column [1-5]: ");
        fflush(stdout);
        
        ret = select(STDIN_FILENO + 1, &fds, NULL, NULL, &timeout);
        if (ret > 0) {
            scanf("%d", &column);
        } else {
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

