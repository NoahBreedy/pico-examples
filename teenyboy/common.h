#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include "pico/stdlib.h"
#include "gfx/ssd1351.h"


#define A_BUTTON 13
#define B_BUTTON 17
#define UP_BUTTON 22
#define LEFT_BUTTON 21
#define DOWN_BUTTON 20
#define RIGHT_BUTTON 19

#define NAME_BUFFER_LENGTH 10

#define INTERRUPT_RESET 255
extern uint interrupt;
extern uint current_selected;
#define BUTTON_BREAK()    if (interrupt != INTERRUPT_RESET) break;
#define BUTTON_CONTINUE() if (interrupt != INTERRUPT_RESET) continue;
#define BUTTON_RETURN()   if (interrupt != INTERRUPT_RESET) return;


extern int name_buffer_length;

void init_all();
void sleep_loop(uint);
void fade_out();
void fade_in();
void splash_screen();
void game_selection();

