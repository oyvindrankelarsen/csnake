#include <stdio.h>
#include <unistd.h>

// #####################
// #      @            #  
// #                   #  
// #                   #  
// #                   #  
// #                   #  
// #                   #  
// #                   #  
// #                   #  
// #                   #  
// #                   #  
// #####################
// Ange vad du vill göra:u + ENTER           
        
#define ROWS 10 //
#define COLS 30 //
#define WALL '#'


typedef struct{
    int X;
    int Y;
}Snake;

typedef enum {
    Snake_Direction_Left,    
    Snake_Direction_Right,
    Snake_Direction_Up,
    Snake_Direction_Down,
}Snake_Direction;

#define clrscr() printf("\e[1;1H\e[2J")
char getch(){
    char c;
    c= getchar();
    return(c);
}

void gotoxy(int x,int y){
    printf("%c[%d;%df",0x1B,y,x);
}

void drawBoundaries(){
    for(int row = 0; row < ROWS+2;row++){
        for(int col = 0; col < COLS+2; col++){
            if(row == 0 || row == ROWS+1 || col == 0 || col == COLS+1){
                printf("%c",WALL);         
            }
            else{
                printf(" ");
            }
        }
        printf("\n");
        
    }
}

void drawSnake(Snake snake){
    gotoxy(snake.X,snake.Y);
    printf("@");

}

Snake_Direction getNextSnakeDirection(Snake_Direction currentSnakeDirection){
    gotoxy(0,ROWS+3);
    printf("Ange vad den ska göra:");
    char ch = getch(); // 
    fflush(stdin);
    if(ch == 'u') return Snake_Direction_Up;
    if(ch == 'd') return Snake_Direction_Down;
    if(ch == 'l') return Snake_Direction_Left;
    if(ch == 'r') return Snake_Direction_Right;
    return currentSnakeDirection;

}


void moveSnake(Snake *snake,Snake_Direction direction){
    if(direction == Snake_Direction_Up){
        if(snake->Y == 2) snake->Y = ROWS+1;
        else snake->Y--;
    }
    if(direction == Snake_Direction_Down){
        if(snake->Y == ROWS+1) snake->Y = 2;
        else snake->Y++;
    }
    if(direction == Snake_Direction_Left){
        if(snake->X == 2) snake->X = COLS+1;
        else snake->X--;
    }
    if(direction == Snake_Direction_Right){
        if(snake->X == COLS+1) snake->X = 2;
        else snake->X++;
    }

}




#define BIT_SET(a, b) ((a) |= (1ULL << (b)))
#define BIT_CLEAR(a,b) ((a) &= ~(1ULL<<(b)))
#define BIT_FLIP(a,b) ((a) ^= (1ULL<<(b)))
#define BIT_CHECK(a,b) (!!((a) & (1ULL<<(b)))) 

//unsigned char B[] = {0B01111000,0B01001000,0B01001000,0B01110000,0B01001000,0B01000100,0B01000100,0B01111100};


// unsigned char pacman[] = {
//     0B01111000,
//     0B01001000,
//     0B01001000,
//     0B01110000,
//     0B01001000,
//     0B01000100,
//     0B01000100,
//     0B01111100};


unsigned char B[] = {
    0B01111000,
    0B01001000,
    0B01001000,
    0B01110000,
    0B01001000,
    0B01000100,
    0B01000100,
    0B01111100};
unsigned char S[] = {
    0B00000000,
    0B00111100,
    0B00100000,
    0B00111100,
    0B00000100,
    0B00000100,
    0B00111100,
    0B00000000};

void scrollDemo(){
    for(int startX = 20; startX > 1; startX--)
    {
        clrscr();

        for(int row = 0; row < 8;row++){
            unsigned char todo = S[row];
            for(int col = 7; col >=0; col--){
                gotoxy(startX-col,0+row);
                if(BIT_CHECK(todo,col))
                    printf("#");
                else printf(" ");
            }
            printf("\n");
        }
        sleep(1);
   }
}





int main(){
    scrollDemo();
    return 0;
    Snake snake; // snake är en array med kroppsdelar - varje kroppsdel har en X och en Y
                    //   arrayen[0] = huvudet  12,10   array[1] = 11,10 array[2]=9,10
                        //           @@@
                        //             @@@@@  
    snake.X = 5;
    snake.Y = 5;

    Snake_Direction currentDirection = Snake_Direction_Right;

    while(1){
        clrscr();    // Motsvarar SLÄCK ALLA LEDS
        drawBoundaries();   // BEHÖVS INTE MNED LED MATRISEN
        drawSnake(snake); // Tänd LEDDEN där den är
        // om tryckt på u snake.Y = snake.Y - 1
        gotoxy(0,0);
        currentDirection = getNextSnakeDirection(currentDirection);
        moveSnake(&snake,currentDirection);

        // sleep
    }

    return 0;
}