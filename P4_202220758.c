#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum {PLAYER1 = 1, PLAYER2 = 2}; //game player 1: O, 2: @
enum {X = 9, Y = 9}; //X: column, Y: row
#define BLOCK_MAX 3 //block's col and row

void display_board(void); //initial board
void display_block(void); //initial block (after random choice of block)
int random_choice(void); //random number pick
void which_block(int r); //create a random block
void rotate_block(void); //rotate block
void put_block(const int block_x, const int block_y); //put the block on the main board
int put_able(const int block_x, const int block_y); // check that the player can put the block on the board
void player1_turn(void);
void player2_turn(void);
int win_check(int r); // for game end check 
void block_initial(void); //block initialization

//global variable
int block[BLOCK_MAX][BLOCK_MAX] = {0};
int board[X][Y] = {0};
int check_board[X][Y] = {0}; //for win_check function
int turn = PLAYER1; //start with player1
int block_x, block_y; //block coordinate

int main(void) {
    display_board();
    while (1) {
        if (turn == PLAYER1) { //player1
            player1_turn();
        }
        else { //player2
            player2_turn();
        }
    }
    return 0;
}

void display_board(void) {
    char ch = '_';
    //prints number of column
    printf("  ");
    for (int i = 1; i <= Y; i++)
        printf(" %d", i);
        puts(""); //new line

    //prints board
    printf("   _ _ _ _ _ _ _ _ _\n");
    for (int i = 0; i <= X-1; i++) {
        printf("%d ", i + 1);
        for (int j = 0; j <= Y-1; j++) {
            if (board[i][j] == 1) ch = 'O';
            else if (board[i][j] == 10) ch = '@';
            else ch = '_';
            printf("|%c", ch);
        } 
        printf("|");
        printf("\n");
    }
}

void block_initial(void) {
    //block array initialization
    for (int i = 0; i <BLOCK_MAX; i++) {
        for (int j = 0; j < BLOCK_MAX; j++) {
            block[i][j] = 0;
        }
    }
}

void display_block(void) {
    char ch = '_';
    printf(" _ _ _\n");
    for (int i = 0; i < BLOCK_MAX; i++) {
        for (int j = 0; j < BLOCK_MAX; j++) {
                if (block[i][j] == 1) {
                        ch = 'O';
                }
                else if (block[i][j] == 10) {
                        ch = '@';
                }
                else ch = '_';
                printf("|%c", ch);
        }
    printf("|");
    printf("\n");
    }
}

void player1_turn(void) {
    printf("\n");
    printf("P1's block: ");
    printf("\n");
    int r = random_choice();
    which_block(r);
    display_block();
    printf("\n");
    if (!win_check(r)) {
        printf("P1 fails to put the block. P2 wins!");
        exit(EXIT_SUCCESS);
    }
    printf("Put your block (r c) or Rotate (0): ");
    
    scanf("%d", &block_x);
    if (block_x != 0) {
        scanf("%d", &block_y);
        if (put_able(block_x, block_y)) {
            printf("P1 is not able to put the block into (%d,%d).\n", block_x, block_y);
            printf("\n");
            printf("P1's block: ");
            printf("\n");
            display_block();
            printf("\n");
            printf("Put your block (r c) or Rotate (0): ");
            scanf("%d %d", &block_x, &block_y);
            printf("\n");
            if (!put_able(block_x, block_y)) {
                put_block(block_x, block_y);
                display_board();
            }
        }
        else {
            printf("\n");
            put_block(block_x, block_y);
            display_board();
        }
    }

    else { //block_x == 0
        do {
            printf("\n");
            printf("P1's block: ");
            rotate_block();
            printf("\n");
            display_block();
            printf("\n");
            printf("Put your block (r c) or Rotate (0): ");
            scanf("%d", &block_x);
        } while (block_x == 0);

            scanf("%d", &block_y);
            printf("\n");
            if (!put_able(block_x, block_y)) {
                put_block(block_x, block_y);
                display_board();
            }
    }
    block_initial();
    turn = PLAYER2;
}

void player2_turn(void) {
    printf("\n");
    printf("P2's block: ");
    printf("\n");
    int r = random_choice();
    which_block(r);
    display_block();
    printf("\n");
    if (!win_check(r)) {
        printf("P2 fails to put the block. P1 wins!");
        exit(EXIT_SUCCESS);
    }
    printf("Put your block (r c) or Rotate (0): ");
    
    scanf("%d", &block_x);
    if (block_x != 0) {
        scanf("%d", &block_y);
        if (put_able(block_x, block_y)) {
            printf("P2 is not able to put the block into (%d,%d).\n", block_x, block_y);
            printf("\n");
            printf("P2's block: ");
            printf("\n");
            display_block();
            printf("\n");
            printf("Put your block (r c) or Rotate (0): ");
            scanf("%d %d", &block_x, &block_y);
            if (!put_able(block_x, block_y)) {
                put_block(block_x, block_y);
                display_board();
            }
        }
        else {
            printf("\n");
            put_block(block_x, block_y);
            display_board();
        }
    }

    else { //block_x == 0
        do {
            printf("\n");
            printf("P2's block: ");
            rotate_block();
            printf("\n");
            display_block();
            printf("\n");
            printf("Put your block (r c) or Rotate (0): ");
            scanf("%d", &block_x);
        } while (block_x == 0);

            scanf("%d", &block_y);
            printf("\n");
            if (!put_able(block_x, block_y)) {
                put_block(block_x, block_y);
                display_board();
            }
    }
    block_initial();
    turn = PLAYER1;
}

int win_check(int r) {
    if (r == 1) {
        for (int i = 0; i < X; i++) {
            for (int j = 0; j < Y; j++) {
                for (int k = 0; k < 4; k++) {
                    rotate_block();
                }
                if (!put_able(i, j)) {
                    return 1;
                }
            }
        }
    }

    else if ((r == 2)||(r == 3)||(r == 4)||(r == 5) || (r == 6) || (r == 7) || (r == 8)) {
        for (int i = 0; i < X - 1; i++) {
            for (int j = 0; j < Y - 1; j++) {
                for (int k = 0; k < 4; k++) {
                    rotate_block();
                }
                if (!put_able(i, j)) {
                    return 1;
                }
            }
        }
    }

    else { //r == 9, r == 10, r == 11, r == 12, r == 13, r == 14
        for (int i = 0; i < X - 2; i++) {
            for (int j = 0; j < Y - 2; j++) {
                for (int k = 0; k < 4; k++) {
                    rotate_block();
                }
                if (!put_able(i, j)) {
                    return 1;
                }
            }
        }
    }
    return 0;
}

int random_choice(void) {
    srand((unsigned int) time(NULL)); /* Initialization: run this only once(at the beginning of the program) */
    int r = rand() % 14; /* Generate a random integer between [0, 13] */
    return r;
}

void which_block(int r) {
    
    char ch = '_';
    switch (r)
    {
    case 1: 
        //     printf(" _ _ _\n");
        //     printf("|O|O|O|\n");
        //     printf("|_|_|_|\n");
        //     printf("|_|_|_|\n");
        //     printf("\n");
            if (turn == PLAYER1) {
                    block[0][0] = 1; block[0][1] = 1; block[0][2] = 1;
            }
            else {//player2
                block[0][0] = 10; block[0][1] = 10; block[0][2] = 10;
            } 
            break;

    case 2: 
        //     printf(" _ _ _\n");
        //     printf("|O|O|O|\n");
        //     printf("|O|_|_|\n");
        //     printf("|_|_|_|\n");
        //     printf("\n");
            if (turn == PLAYER1){
                block[0][0] = 1; block[0][1] = 1; block[0][2] = 1; block[1][0] = 1;
            }
            else {
                block[0][0] = 10; block[0][1] = 10; block[0][2] = 10; block[1][0] = 10;
            }
            break;
    
    case 3: 
        //     printf(" _ _ _\n");
        //     printf("|O|O|O|\n");
        //     printf("|_|_|O|\n");
        //     printf("|_|_|_|\n");
        //     printf("\n");
            if (turn == PLAYER1) {
                block[0][0] = 1; block[0][1] = 1; block[0][2] = 1; block[1][2] = 1;
            }
            else {
                block[0][0] = 10; block[0][1] = 10; block[0][2] = 10; block[1][2] = 10;
            }
            break;
    
    case 4: 
        //     printf(" _ _ _\n");
        //     printf("|O|O|O|\n");
        //     printf("|_|O|_|\n");
        //     printf("|_|_|_|\n");
        //     printf("\n");
            if (turn == PLAYER1){
                block[0][0] = 1; block[0][1] = 1; block[0][2] = 1; block[1][1] = 1;
            }
            else {
                block[0][0] = 10; block[0][1] = 10; block[0][2] = 10; block[1][1] = 10;
            }
            break;
    
    case 5: 
        //     printf(" _ _ _\n");
        //     printf("|_|O|O|\n");
        //     printf("|O|O|_|\n");
        //     printf("|_|_|_|\n");
        //     printf("\n");     
            if (turn == PLAYER1) {        
                block[0][1] = 1; block[0][2] = 1; block[1][0] = 1; block[1][1] = 1;
            }
            else {
                block[0][1] = 10; block[0][2] = 10; block[1][0] = 10; block[1][1] = 10;
            }
            break;

    case 6: 
        //     printf(" _ _ _\n");
        //     printf("|O|O|_|\n");
        //     printf("|_|O|O|\n");
        //     printf("|_|_|_|\n");
        //     printf("\n");
            if (turn == PLAYER1) {
                block[0][0] = 1; block[0][1] = 1; block[1][1] = 1; block[1][2] = 1;
            }
            else {
                block[0][0] = 10; block[0][1] = 10; block[1][1] = 10; block[1][2] = 10;
            }
            break;
    
    case 7: 
        //     printf(" _ _ _\n");
        //     printf("|O|O|_|\n");
        //     printf("|O|O|_|\n");
        //     printf("|_|_|_|\n");
        //     printf("\n");
            if (turn == PLAYER1) {
                block[0][0] = 1; block[0][1] = 1; block[1][0] = 1; block[1][1] = 1;
            }
            else {
                block[0][0] = 10; block[0][1] = 10; block[1][0] = 10; block[1][1] = 10;
            }
            break;
    
    case 8: 
        //     printf(" _ _ _\n");
        //     printf("|O|_|_|\n");
        //     printf("|O|O|_|\n");
        //     printf("|O|O|_|\n");
        //     printf("\n");
            if (turn == PLAYER1) {
                block[0][0] = 1; block[1][0] = 1; block[1][1] = 1; block[2][0] = 1; block[2][1] = 1;
            }
            else {
                block[0][0] = 10; block[1][0] = 10; block[1][1] = 10; block[2][0] = 10; block[2][1] = 10;
            }
            break;
    
    case 9: 
        //     printf(" _ _ _\n");
        //     printf("|_|O|O|\n");
        //     printf("|O|O|_|\n");
        //     printf("|O|_|_|\n");
        //     printf("\n");
            if (turn == PLAYER1) {
                block[0][1] = 1; block[0][2] = 1; block[1][0] = 1; block[1][1] = 1; block[2][0] = 1;
            }
            else {
                block[0][1] = 10; block[0][2] = 10; block[1][0] = 10; block[1][1] = 10; block[2][0] = 10;
            }
            break;

    case 10: 
        //     printf(" _ _ _\n");
        //     printf("|O|O|_|\n");
        //     printf("|_|O|O|\n");
        //     printf("|_|O|_|\n");
        //     printf("\n");
            if (turn == PLAYER1) {
                block[0][0] = 1; block[0][1] = 1; block[1][1] = 1; block[1][2] = 1; block[2][1] = 1;
            }
            else {
                block[0][0] = 10; block[0][1] = 10; block[1][1] = 10; block[1][2] = 10; block[2][1] = 10;
            }
            break;

    case 11: 
        //     printf(" _ _ _\n");
        //     printf("|_|O|O|\n");
        //     printf("|O|O|_|\n");
        //     printf("|_|O|_|\n");
        //     printf("\n");
            if (turn == PLAYER1) {
                block[0][1] = 1; block[0][2] = 1; block[1][0] = 1; block[1][1] = 1; block[2][1] = 1;
            }
            else {
                block[0][1] = 10; block[0][2] = 10; block[1][0] = 10; block[1][1] = 10; block[2][1] = 10;
            }
            break;
    
    case 12: 
        //     printf(" _ _ _\n");
        //     printf("|_|_|O|\n");
        //     printf("|O|O|O|\n");
        //     printf("|O|_|_|\n");
        //     printf("\n");
            if (turn == PLAYER1) {
                block[0][2] = 1; block[1][0] = 1; block[1][1] = 1; block[1][2] = 1; block[2][0] = 1;
            }
            else {
                block[0][2] = 10; block[1][0] = 10; block[1][1] = 10; block[1][2] = 10; block[2][0] = 10;
            }
            break;

    case 13: 
        //     printf(" _ _ _\n");
        //     printf("|O|_|_|\n");
        //     printf("|O|O|O|\n");
        //     printf("|_|_|O|\n");
        //     printf("\n");
            if (turn == PLAYER1) {
                block[0][0] = 1; block[1][0] = 1; block[1][1] = 1; block[1][2] = 1; block[2][2] = 1;
            }
            else {
                block[0][0] = 10; block[1][0] = 10; block[1][1] = 10; block[1][2] = 10; block[2][2] = 10;
            }
            break;
    default: 
        //     printf(" _ _ _\n");
        //     printf("|_|O|_|\n");
        //     printf("|O|O|O|\n");
        //     printf("|_|O|_|\n");
        //     printf("\n");
            if (turn == PLAYER1) {
                block[0][1] = 1; block[1][0] = 1; block[1][1] = 1; block[1][2] = 1; block[2][1] = 1;
            }
            else {
                block[0][1] = 10; block[1][0] = 10; block[1][1] = 10; block[1][2] = 10; block[2][1] = 10;
            }
            break;
    }
}

void rotate_block(void) {
    int trans[BLOCK_MAX][BLOCK_MAX] = {0};
    int i, j;
    for (i = 0; i < BLOCK_MAX; i++) {
        for (j = 0; j < BLOCK_MAX; j++) {
            trans[i][j] = block[j][BLOCK_MAX - i - 1];
        }
    }

    for (i = 0; i < BLOCK_MAX; i++) {
        for (j = 0; j < BLOCK_MAX; j++) {
            block[i][j] = trans[i][j];
        }
    }
}

void put_block(const int block_x, const int block_y) {
    for (int i = 0; i < BLOCK_MAX; i++) {
        for (int j = 0; j < BLOCK_MAX; j++) {
            if (block[i][j] == 1) {
                board[block_x + i - 1][block_y + j - 1] = 1;
                check_board[block_x + i - 1][block_y + j - 1] += 1;
            }
            else if (block[i][j] == 10){
                board[block_x + i - 1][block_y + j - 1] = 10;
                check_board[block_x + i - 1][block_y + j - 1] += 1;
            }
        }
    }
    return;
}

int put_able(const int block_x, const int block_y) {
    for (int i = 0; i < BLOCK_MAX; i++) {
        for (int j = 0; j < BLOCK_MAX; j++) {
            if ((block[i][j] == 1) || block[i][j] == 10) {
                if (check_board[block_x + i - 1][block_y + j - 1] == 1) {
                    return 1;
                }
            }
        }
    }
    return 0;
}
