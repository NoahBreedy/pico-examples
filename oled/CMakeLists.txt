add_executable(oled
        common.c
        gfx/ssd1351.c
        oled.c 
        )

pico_set_program_name(oled "oled")
pico_set_program_version(oled "0.1")

target_link_libraries(oled pico_stdlib hardware_spi hardware_dma)
pico_add_extra_outputs(oled)

# add url via pico_set_program_url
example_auto_set_url(oled)
