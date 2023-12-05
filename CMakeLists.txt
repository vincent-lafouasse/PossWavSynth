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
src/third_party
src/wav.h
src/wavetable.h
src/third_party/lib/BaseChunk.cpp
src/third_party/lib/BaseChunk.h
src/third_party/lib/Event.cpp
src/third_party/lib/Event.h
src/third_party/lib/HeaderChunk.cpp
src/third_party/lib/HeaderChunk.h
src/third_party/lib/MTrkEvent.cpp
src/third_party/lib/MTrkEvent.h
src/third_party/lib/MetaEvent.cpp
src/third_party/lib/MetaEvent.h
src/third_party/lib/Midi.cpp
src/third_party/lib/Midi.h
src/third_party/lib/MidiEvent.cpp
src/third_party/lib/MidiEvent.h
src/third_party/lib/Options.h
src/third_party/lib/ReadNumber.cpp
src/third_party/lib/ReadNumber.h
src/third_party/lib/SysExEvent.cpp
src/third_party/lib/SysExEvent.h
src/third_party/lib/TrackChunk.cpp
src/third_party/lib/TrackChunk.h
src/third_party/lib/VLQ.cpp
src/third_party/lib/VLQ.h
src/third_party/lib/list.h
src/third_party/lib/types.h
)

# LSP stuff, don't worry about it
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)
