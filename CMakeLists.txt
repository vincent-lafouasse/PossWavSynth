cmake_minimum_required(VERSION 3.22)

project(PossWavSynth)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -Wpedantic)
add_compile_options(-g3)

add_executable(PossWavSynth)
target_sources(PossWavSynth PRIVATE
	src/main.cpp

	src/midi/parse_midi.cpp
	src/midi/MidiTempo.cpp
	src/midi/MidiMelody.cpp

	src/synth/wavetable.cpp
	src/synth/oscillator.cpp
	src/synth/Synth.cpp

	src/DSP/Signal.cpp
	src/DSP/MonoSignalSmoother.hpp

	src/wav/wav.cpp
	src/wav/Data.cpp

	src/melody/melody.cpp
)
target_include_directories(PossWavSynth PUBLIC src)
