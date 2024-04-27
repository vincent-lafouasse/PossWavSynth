cmake_minimum_required(VERSION 3.5)

project(PossWavSynth)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -Wpedantic)
add_compile_options(-g3)

add_executable(PossWavSynth)
target_sources(PossWavSynth PRIVATE
	src/main.cpp
	src/Signal.cpp
	src/melody.cpp
	src/oscillator.cpp
	src/wav.cpp
	src/wavetable.cpp
	src/Data.cpp
)
target_include_directories(PossWavSynth PUBLIC src)

add_subdirectory(lib)
target_link_libraries(PossWavSynth libParser)
