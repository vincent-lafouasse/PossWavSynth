BUILD_DIR = build

all: build

update:
	cmake -B "$(BUILD_DIR)"

build:
	cmake --build "$(BUILD_DIR)"

run: build
	./build/PossWavSynth

plot:
	./plot_csv signal.csv

play:
	ffplay wave.wav

.PHONY: all build update run plot play
