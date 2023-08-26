#include "max72xx.h"
#include "uart.h"
#include <stdio.h>
#include <string.h>
#include <avr/interrupt.h>
#include "millis.h"
#include <stdbool.h>

// 3 * 3

void clear()
{
    for (int col = 3; col < 6; col++)
    {
        max7219b_clr(col, 3);
        max7219b_clr(col, 4);
        max7219b_clr(col, 5);
    }
}

void draw(int tal)
{
    if (tal == 1)
    {
        max7219b_set(4, 4);
    }
    else if (tal == 2)
    {
        max7219b_set(3, 3);
        max7219b_set(5, 5);
    }
    else if (tal == 3)
    {
        max7219b_set(3, 3);
        max7219b_set(4, 4);
        max7219b_set(5, 5);
    }
    else if (tal == 4)
    {
        max7219b_set(3, 3);
        max7219b_set(3, 5);
        max7219b_set(5, 3);
        max7219b_set(5, 5);
    }
    else if (tal == 5)
    {
        max7219b_set(3, 3);
        max7219b_set(3, 5);
        max7219b_set(4, 4);
        max7219b_set(5, 3);
        max7219b_set(5, 5);
    }
    else if (tal == 6)
    {
        max7219b_set(3, 3);
        max7219b_set(3, 4);
        max7219b_set(3, 5);
        max7219b_set(5, 3);
        max7219b_set(5, 4);
        max7219b_set(5, 5);
    }
    max7219b_out();
}

// s
//// https://wokwi.com/projects/296234816685212169

// senaste kaffet = 10:53
// 10:58
int main()
{
    millis_init();
    sei();

    init_serial();
    max7219_init();
    // int x = 0;
    // int y = 0;

    volatile millis_t antalMilliSekunderSenasteBytet = 0;
    bool first = true;
    int tal = 1;

    while (true)
    {

        if (first || millis_get() - antalMilliSekunderSenasteBytet > 1000)
        {
            first = false;
            // DAGS ATT GÖRA NÅT
            clear();
            draw(tal);
            tal = tal + 1;
            if (tal > 6)
                tal = 1;
            antalMilliSekunderSenasteBytet = millis_get();
        }
    }
    return 0;
}