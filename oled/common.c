// SPDX-License-Identifier: GPL-2.0

#include "common.h"
uint current_selected = 0;

void show_qr(const uint8_t* img, const unsigned int img_len, const char *text)
{
    ssd1351_clear();
    ssd1351_set_contrast(255);
    ssd1351_load_image_1bpp(BUFFER_TYPE_DISPLAY, img, img_len);
    uint16_t colour = ssd1351_make_colour(0x00, 0x00, 0x00);
    point_t text_pos = {16, 118};
    ssd1351_write_text(BUFFER_TYPE_DISPLAY, text, text_pos, colour, FONT_IBM, true, false);
    ssd1351_refresh();
    sleep_ms(10000);
    ssd1351_clear();
}

void scroll_loop(scroll_direction direction)
{
    for (uint16_t i = 0; i < 64; i++)
    {
        ssd1351_scroll_buffered(2, direction);
        ssd1351_refresh();
    }
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


void line_test()
{
    uint16_t colour = ssd1351_make_colour(0x7f, 0x7f, 0xff);
    ssd1351_clear();
    ssd1351_draw_line(BUFFER_TYPE_DISPLAY, colour, (point_t){0, 0}, (point_t){128, 128});
    ssd1351_draw_line(BUFFER_TYPE_DISPLAY, colour, (point_t){128, 0}, (point_t){0, 128});
    ssd1351_draw_line(BUFFER_TYPE_DISPLAY, colour, (point_t){64, 0}, (point_t){64, 128});
    ssd1351_draw_line(BUFFER_TYPE_DISPLAY, colour, (point_t){0, 32}, (point_t){128, 96});
    ssd1351_draw_line(BUFFER_TYPE_DISPLAY, colour, (point_t){0, 96}, (point_t){128, 32});
    colour = ssd1351_make_colour(0x00, 0xff, 0x00);
    ssd1351_draw_rectangle(BUFFER_TYPE_DISPLAY, colour, (point_t){10, 10}, (point_t){90, 40}, false);
    ssd1351_draw_rectangle(BUFFER_TYPE_DISPLAY, colour, (point_t){90, 90}, (point_t){110, 120}, true);
    colour = ssd1351_make_colour(0xff, 0x7f, 0x7f);
    ssd1351_draw_circle(BUFFER_TYPE_DISPLAY, colour, (point_t){64, 64}, 20, true);
    colour = ssd1351_make_colour(0xff, 0xff, 0x00);
    ssd1351_draw_triangle(BUFFER_TYPE_DISPLAY, colour, (point_t){20, 70}, (point_t){30, 85}, (point_t){40, 60}, false);
    ssd1351_draw_triangle(BUFFER_TYPE_DISPLAY, colour, (point_t){80, 40}, (point_t){90, 90}, (point_t){120, 60}, true);

    point_t text_pos;
    text_pos = (point_t){33, 20};
    ssd1351_write_text(BUFFER_TYPE_DISPLAY, "TeenyAT's", text_pos, 0, FONT_IBM, true, true);
    text_pos = (point_t){35, 40};
    ssd1351_write_text(BUFFER_TYPE_DISPLAY, "TeenyBoy", text_pos, 0, FONT_IBM, true, true);
}

void colour_pattern(){
    
    ssd1351_clear();

    point_t pos = {0, 0};
    point_t text_pos;
    for(int y = 0; y < HEIGHT; y++){
        pos.y = y;
        for(int x = 0; x < WIDTH; x++){
            pos.x = x;
            uint16_t col = ssd1351_make_colour(x*2,y*2,255-x*2);
            ssd1351_draw_pixel(BUFFER_TYPE_DISPLAY, col, pos);
        }
    }
    
    text_pos = (point_t){33, 40};
    ssd1351_write_text(BUFFER_TYPE_DISPLAY, "TeenyAT's", text_pos, 0, FONT_IBM, true, true);
    text_pos = (point_t){35, 60};
    ssd1351_write_text(BUFFER_TYPE_DISPLAY, "TeenyBoy", text_pos, 0, FONT_IBM, true, true);
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

