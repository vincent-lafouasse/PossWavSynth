BUILD_DIR = build
EXEC = $(BUILD_DIR)/PossWavSynth

all: build

update:
	cmake -B "$(BUILD_DIR)" -G Ninja

build: $(EXEC)

$(EXEC):
	cmake --build "$(BUILD_DIR)"

run: build
	./build/PossWavSynth

plot:
	./plot_csv signal.csv

play:
	ffplay wave.wav

.PHONY: all build update run plot play

PHONY: r b u pl plt
r: run
b: build
u: update
pl: play
plt: plot
