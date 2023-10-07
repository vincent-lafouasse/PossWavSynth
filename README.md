# PossDSP

An exploration of digital audio, the `wav` audio format and wavetable synthesis disguised as a non real-time synth using only standard C++17

Following roughly [this tutorial](https://blog.demofox.org/diy-synthesizer/)

## todo

- polyphonic capabilities (summing `FloatData` instances)
- Band limited wavetables (using the additive engine + brushing up on Fourier series)
- loading `mid` info (thanks to @MStefan99's [parser](https://github.com/MStefan99/Midi-Parser/tree/master))
- VCA envelopes
- maybe write some algorithmic reverb to make it sound good _good_
- a sequencer maybe ??

## done

- write to `wav`
- basic wavetable engine with the classic wavetables
- basic additive engine using pure sine wavetables
- compose and load some basic melodies into it

## ressources that helped me

- [the tutorial this is based on](https://blog.demofox.org/diy-synthesizer/)

## LICENSE

```
            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
                    Version 2, December 2004

 Copyright (C) 2012 Romain Lespinasse <romain.lespinasse@gmail.com>

 Everyone is permitted to copy and distribute verbatim or modified
 copies of this license document, and changing it is allowed as long
 as the name is changed.

            DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
   TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION

  0. You just DO WHAT THE FUCK YOU WANT TO.
```
