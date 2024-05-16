/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * 
 *  Going to turn this into the teenyat pico lcd system....
 *  hopefully
 */

#include "pico/stdlib.h"
#include "teenyat.h"
#include "teeny_blink.h"
#include "common.h"

#define LIGHT_ON 0xE000
#define LIGHT_OFF 0xE001
#define BOARD_SLEEP 0xE002

void bus_read(teenyat * t, tny_uword addr, tny_word *data, uint16_t *delay);
void bus_write(teenyat * t, tny_uword addr, tny_word data, uint16_t * delay);



int main() {

    init_all();

    splash_screen();
    game_selection();
    fade_in();

    bool selected_game = false;
    while(!selected_game){
        game_selection();
        if(gpio_get(DOWN_BUTTON) == 1){

            while(gpio_get(DOWN_BUTTON) == 1);

            if(current_selected < NAME_BUFFER_LENGTH-1){
                 current_selected++;
            }
        }else if(gpio_get(UP_BUTTON) == 1){

            while(gpio_get(UP_BUTTON) == 1);
            if(current_selected>0){
                current_selected--;
            }
        }else if(gpio_get(A_BUTTON) == 1){
            bool abort = false;
            while(gpio_get(A_BUTTON) == 1){
                if(gpio_get(B_BUTTON) == 1){
                    abort = true;
                }
            }

            if(!abort){
                selected_game = true;
                break;
            } 
        }
        sleep_ms(10);
    }

    ssd1351_fill_colour(BUFFER_TYPE_DISPLAY,0x0F00);
    ssd1351_refresh();

    while(true){
        sleep_ms(100);
    }
    // /* INIT ONBOARD LED PIN */
    // gpio_init(LED_PIN);
    // gpio_set_dir(LED_PIN, GPIO_OUT);
    // gpio_put(LED_PIN, 0);
    // teenyat t;
    //  #ifdef __BINARY_DATA__
    //     tny_init_from_header(&t, binary_length, binary_data, bus_read, bus_write);
    // #endif 
    // #ifndef __BINARY_DATA__
    //     printf("Failed to init bin file (no header file?)");
    //     return 0;
    // #endif

    // while (true) {
    //     tny_clock(&t);
    // }
}


void bus_read(teenyat * t, tny_uword addr, tny_word *data, uint16_t *delay){
    return;
}

void bus_write(teenyat * t, tny_uword addr, tny_word data, uint16_t * delay){
    switch (addr)
    {
    case LIGHT_ON:
        gpio_put(PICO_DEFAULT_LED_PIN, 1);
        break;
    case LIGHT_OFF:
        gpio_put(PICO_DEFAULT_LED_PIN, 0);
        break;
    case BOARD_SLEEP:
        sleep_ms(data.u);
        break;
    default:
        /* Unknown opcode */
        break;
    }
}