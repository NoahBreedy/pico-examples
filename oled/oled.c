#include <stdio.h>
#include "pico/stdlib.h"
#include "common.h"


int main() {

    stdio_init_all();
    
    gpio_init(PICO_DEFAULT_LED_PIN);
    gpio_set_dir(PICO_DEFAULT_LED_PIN, GPIO_OUT);
    gpio_put(PICO_DEFAULT_LED_PIN,1);
    ssd1351_init();
    gpio_put(PICO_DEFAULT_LED_PIN,0);

    gpio_init(A_BUTTON);
    gpio_set_dir(A_BUTTON, GPIO_IN);

    gpio_init(B_BUTTON);
    gpio_set_dir(B_BUTTON, GPIO_IN);

    gpio_init(UP_BUTTON);
    gpio_set_dir(UP_BUTTON, GPIO_IN);

    gpio_init(LEFT_BUTTON);
    gpio_set_dir(LEFT_BUTTON, GPIO_IN);

    gpio_init(DOWN_BUTTON);
    gpio_set_dir(DOWN_BUTTON, GPIO_IN);

    gpio_init(RIGHT_BUTTON);
    gpio_set_dir(RIGHT_BUTTON, GPIO_IN);

    splash_screen();
    game_selection();
    fade_in();
    while(1){
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
        }
        sleep_ms(10);
    }
}
