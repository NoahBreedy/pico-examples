add_executable(teenyboy
        gfx/ssd1351.c
        common.c
        teenyat.c 
        teenyboy.c 
        )
        

# pull in common dependencies
target_link_libraries(teenyboy pico_stdlib hardware_spi hardware_dma)

# create map/bin/hex file etc.
pico_add_extra_outputs(teenyboy)

# add url via pico_set_program_url
example_auto_set_url(teenyboy)