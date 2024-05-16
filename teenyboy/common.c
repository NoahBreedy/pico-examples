// SPDX-License-Identifier: GPL-2.0

#include "common.h"
uint current_selected = 0;

void init_all(){
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
}

void sleep_loop(uint a) 
{
    for (uint16_t i = 0; i < a; i++)
    {
        sleep_ms(100);
    }
}

void fade_out()
{
    for (int16_t i = 255; i >= 0; i--)
    {
        sleep_ms(1);
        ssd1351_set_contrast(i);
    }
}

void fade_in()
{
    for (uint16_t i = 0; i <= 255; i++)
    {
        sleep_ms(1);
        ssd1351_set_contrast(i);
    }
}

void game_selection(){
    char* name_buffer[] = {"Pallete","Movement","Flappy","Lorem","ipsum","dolor","noah","amos","aero","baby"};
    ssd1351_clear();
    point_t text_pos = {20,0};
    ssd1351_write_text(BUFFER_TYPE_DISPLAY, "Select Game:", text_pos, 0xF000, FONT_IBM, true, false);

    text_pos = (point_t){10,20};
    int start_index = 0;
    if(current_selected>3){
        start_index = current_selected;
    }
    for(int i = 0; i < 4; i++){

        if(i+start_index > NAME_BUFFER_LENGTH-1) break;

        uint16_t text_col = 0xFFFF;
        char current_name[50];
        sprintf(current_name,"%d. %s",start_index+i+1,name_buffer[start_index+i]);
        if(i+start_index == current_selected){
            text_col = 0x00F0;
        }
        ssd1351_write_text(BUFFER_TYPE_DISPLAY, current_name, text_pos, text_col, FONT_IBM, true, false);
        text_pos.y+=20;
    }
    ssd1351_refresh();
}

void splash_screen(){
    
    ssd1351_clear();
    for(int y = 0; y < OLED_HEIGHT; y++){
        for(int x = 0; x < OLED_WIDTH; x++){
            uint16_t color = ssd1351_make_colour(x*2,y*2,255-x*2);
            ssd1351_draw_pixel(BUFFER_TYPE_DISPLAY,color,(point_t){x,y});
        }
    }

    point_t text_pos = {30,35};
    ssd1351_write_text(BUFFER_TYPE_DISPLAY, "Teeny-Boy", text_pos, 0, FONT_IBM, true, true);
    ssd1351_refresh();
    sleep_loop(15);
    fade_out();

}

