# PossWavSynth

An exploration of digital audio, the `wav` audio format and wavetable synthesis disguised as a non real-time synth using only standard C++17

Following roughly [this tutorial](https://blog.demofox.org/diy-synthesizer/)

## todo

- parse tempo from midi
- VCA envelopes
- maybe write some algorithmic reverb to make it sound good _good_
- a sequencer maybe ??

## done

- write to `wav`
- basic wavetable engine with the classic wavetables
- basic additive engine buy summing pure sine wavetables
- compose and load some basic melodies into it
- polyphonic capabilities (summing `Signal` instances)
- Band limited wavetables (using the additive engine + brushing up on Fourier series)
- fetch `mid` events (thanks to @MStefan99's [parser](https://github.com/MStefan99/Midi-Parser/tree/master))
        - partial midi support

## ressources that helped me

- [WAV format specifications](https://www.mmsp.ece.mcgill.ca/Documents/AudioFormats/WAVE/WAVE.html)
- [the tutorial that inspired this](https://blog.demofox.org/diy-synthesizer/)

## LICENSE

```
            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
                    Version 2, December 2004

 Copyright (C) 2023 Vincent Lafouasse

 Everyone is permitted to copy and distribute verbatim or modified
 copies of this license document, and changing it is allowed as long
 as the name is changed.

            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION

  0. You just DO WHAT THE FUCK YOU WANT TO.
```
