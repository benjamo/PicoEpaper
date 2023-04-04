file(GLOB *.cpp *.h FILES)

add_library(ePaper epdspi.cpp epdspi.h gdey027t91.cpp gdey027t91.h)
target_link_libraries(ePaper pico_stdlib hardware_spi)
