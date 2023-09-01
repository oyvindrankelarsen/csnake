#include "max72xx.h"
#include "uart.h"
#include "analogRead.h"
#include <stdio.h>
#include <string.h>
#include <avr/interrupt.h>
#include "millis.h"
#include <util/delay.h>
#include <stdbool.h>

// https://wokwi.com/projects/296234816685212169

#define VERT_PIN 0
#define HORZ_PIN 1

#define BIT_SET(a, b) ((a) |= (1ULL << (b)))
#define BIT_CLEAR(a, b) ((a) &= ~(1ULL << (b)))
#define BIT_FLIP(a, b) ((a) ^= (1ULL << (b)))
#define BIT_CHECK(a, b) (!!((a) & (1ULL << (b))))

#define CLK_PIN 13
#define DATA_PIN 11
#define CS_PIN 10

#define ROWS 8
#define COLS 16

typedef enum
{
    Snake_Direction_Left,
    Snake_Direction_Right,
    Snake_Direction_Up,
    Snake_Direction_Down,
} Snake_Direction;

typedef struct
{
    int X;
    int Y;
} Snake;

// void drawSnake(Snake snake)
// {
//     gotoxy(snake.X, snake.Y);
// }

// void gotoxy(int x, int y)
// {
//     // printf("%c[%d;%df",0x1B,y,x); //tänd led
// }

void moveSnake(Snake *snake, Snake_Direction direction)
{
    if (direction == Snake_Direction_Up)
    {
        if (snake->Y == 2)
        {
            snake->Y = ROWS + 1;
            BIT_SET(snake->X, snake->Y);
        }
        else
        {
            snake->Y--;
            BIT_SET(snake->X, snake->Y);
        }
    }
    if (direction == Snake_Direction_Down)
    {
        if (snake->Y == ROWS + 1)
        {
            snake->Y = 2;
            BIT_SET(snake->X, snake->Y);
        }
        else
        {
            snake->Y++;
            BIT_SET(snake->X, snake->Y);
        }
    }
    if (direction == Snake_Direction_Left)
    {
        if (snake->X == 2)
        {
            snake->X = COLS + 1;
            BIT_SET(snake->X, snake->Y);
        }
        else
        {
            snake->X--;
            BIT_SET(snake->X, snake->Y);
        }
    }
    if (direction == Snake_Direction_Right)
    {
        if (snake->X == COLS + 1)
        {
            snake->X = 2;
            BIT_SET(snake->X, snake->Y);
        }
        else
        {
            snake->X++;
            BIT_SET(snake->X, snake->Y);
        }
    }
    max7219b_out();
}

int main()
{
    Snake snake[ROWS * COLS]; // snake är en array med kroppsdelar - varje kroppsdel har en X och en Y
    snake[0].X = 16;
    snake[0].Y = 0;

    BIT_CLEAR(DDRC, VERT_PIN);
    BIT_CLEAR(DDRC, HORZ_PIN);

    millis_init();
    sei();
    init_serial();
    max7219_init();
    BIT_SET(snake[0].X, snake[0].Y);
    max7219b_out();
    // pinMode(VERT_PIN, INPUT);
    // pinMode(HORZ_PIN, INPUT);
    // pinMode(SEL_PIN, INPUT_PULLUP);
    // Snake_Direction currentDirection = Snake_Direction_Right;
    // volatile millis_t antalMilliSekunderSenasteBytet = 0;
    // bool first = true;
    // bool change = true;

    uint32_t oldhorz = 0;
    uint32_t oldvert = 0;

    while (true)
    {
        // max7219b_set(3, 3);
        // printf("%d%d", snake->X, snake->Y);
        // Läs joystick
        uint32_t horz = analogRead(HORZ_PIN);
        uint32_t vert = analogRead(VERT_PIN);
        if (horz != oldhorz)
            printf("Horz:%i\n", horz);
        oldhorz = horz;
        if (vert != oldvert)
            printf("Vert:%i\n", vert);
        oldvert = vert;

        if (horz < 300)
        {
            // RIGHT
            Snake_Direction direction = Snake_Direction_Right;
            moveSnake(snake, direction);
        }

        if (horz > 700)
        {
            // LEFT
            Snake_Direction direction = Snake_Direction_Left;
            moveSnake(snake, direction);
        }

        if (vert > 700)
        {
            // UP
            Snake_Direction direction = Snake_Direction_Up;
            moveSnake(snake, direction);
        }

        if (vert < 300)
        {
            // DOWN
            Snake_Direction direction = Snake_Direction_Down;
            moveSnake(snake, direction);
        }
        // if (first || millis_get() - antalMilliSekunderSenasteBytet > 1000)
        // {
        //     antalMilliSekunderSenasteBytet = millis_get();
        // }

        _delay_ms(100);
    }
    return 0;
}