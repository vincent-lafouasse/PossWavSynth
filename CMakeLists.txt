cmake_minimum_required(VERSION 3.5)

project(PossWavSynth)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -Wpedantic)
add_compile_options(-g3)

add_executable(PossWavSynth
src/data.cpp
src/main.cpp
src/melody.cpp
src/oscillator.cpp
src/wav.cpp
src/wavetable.cpp
src/cool_ints.h
src/data.h
src/melody.h
src/oscillator.h
src/wav.h
src/wavetable.h
)

# LSP stuff, don't worry about it
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
