# Enigma

A command-line Enigma machine simulator written in C. It encrypts (and decrypts) text files using a three-rotor machine with ring settings, a plugboard, and a reflector.

Standard C only, no dependencies. Builds on Linux, macOS (Intel and Apple Silicon) and Windows.

## Features

- Rotors I to V, chosen and ordered freely (three at a time)
- Configurable rotor start positions and ring settings
- Plugboard with up to 13 letter pairs
- Reflectors A, B and C
- Faithful stepping, including the middle-rotor double step
- Reads its whole setup from a plain-text config file

## Requirements

You need a C compiler and `make`.

| OS | Install |
|---|---|
| Debian / Ubuntu | `sudo apt install build-essential` |
| Fedora | `sudo dnf install gcc make` |
| macOS | `xcode-select --install` |
| Windows | Install [MSYS2](https://www.msys2.org/), open the **UCRT64** terminal, then `pacman -S mingw-w64-ucrt-x86_64-gcc make` |

## Build

```
make
```

This produces `enigma` (or `enigma.exe` on Windows). Run `make clean` to remove build files.

## Usage

```
./enigma <input.txt> <config.txt> <output.txt>
```

On Windows: `./enigma.exe <input.txt> <config.txt> <output.txt>`

- **input**: the text to encode. Only letters are used; spaces, digits and punctuation are skipped, and lowercase is converted to uppercase.
- **config**: the machine settings (format below).
- **output**: where the result is written. It is overwritten if it exists.

The output is grouped in blocks of four letters.

### Example

Input (`hello.txt`):

```
HELLO WORLD
```

Output with the sample `config.txt` from this repo:

```
BBCP CGJG EE
```

Because Enigma is reciprocal, running the output through the same config returns the original letters (`HELL OWOR LD`).

## Config file format

The file has five lines, in this order:

```
ROTORS: 5 2 3
ROTOR POSITIONS: F A C
RING SETTINGS: Q Z D
PLUGBOARD: DY EQ RB KV NX AL MS ZG OC TJ
REFLECTOR: A
```

| Line | Meaning | Rules |
|---|---|---|
| `ROTORS` | Rotor numbers, left to right | Three different numbers from 1 to 5 |
| `ROTOR POSITIONS` | Starting letter of each rotor | Letters A to Z |
| `RING SETTINGS` | Ring setting of each rotor | Letters A to Z |
| `PLUGBOARD` | Swapped letter pairs, separated by spaces | Up to 13 pairs, each letter used at most once |
| `REFLECTOR` | Reflector type | A, B or C |

Formatting is strict: one space after each colon, one space between items, and no trailing spaces. The program prints an explanation if a line is invalid.

## Settings generator

`enigma_gen.c` generates a random but reproducible set of machine settings from a numeric seed. The same seed always produces the same settings, on any platform.

### Build

```
gcc -std=c99 -o enigma_gen enigma_gen.c
```

### Usage

```
./enigma_gen <seed>
```

On Windows: `./enigma_gen.exe <seed>`

- **seed**: a non-negative integer (up to 64 bits).

The settings are written to `enigma_settings_<seed>.txt` in the current directory, in the same format as the config file described above. An existing file with the same name is overwritten. You can pass the result straight to the simulator:

```
./enigma_gen 42
./enigma input.txt enigma_settings_42.txt output.txt
```

### What gets generated

| Setting           | How it is chosen                                          |
| ----------------- | --------------------------------------------------------- |
| `ROTORS`          | Three different rotors from I to V, in random order       |
| `ROTOR POSITIONS` | A random letter for each rotor                            |
| `RING SETTINGS`   | A random letter for each rotor                            |
| `PLUGBOARD`       | `plugboardSwaps` pairs, with each letter used at most once |
| `REFLECTOR`       | One of A, B or C                                          |

The number of plugboard pairs is set by the `plugboardSwaps` constant at the top of `enigma_gen.c` (currently 10, maximum 13).

### How it stays deterministic

The generator uses its own small pseudo-random generator (SplitMix64) instead of `rand()`, whose output differs between compilers and operating systems. Bounded values are drawn with rejection sampling to avoid modulo bias.

This is not cryptographically secure, so don't use it to generate real keys.

## Project layout

```
main.c                     program entry point and encoding loop
headers/                   header files (rotor and reflector wiring, structs, error codes)
libraries/                 config parsing, error messages, rotor and plugboard logic
Makefile                   build instructions
input.txt                  sample input
config.txt                 sample configuration
output.txt                 output obtained by running sample input with sample config thru
decrypted.txt              output obtained by running output.txt with sample config thru
enigmaSettingsGenerator.c  generates deterministically random settings based on input seed
```

## Testing

Enigma encrypts and decrypts with the same settings, so a quick check is a round trip:

```
./enigma input.txt config.txt out.txt
./enigma out.txt config.txt back.txt
```

`back.txt` should contain the letters of `input.txt` in uppercase, in groups of four.

## Notes

- This is a hobby and learning project. It is not suitable for real cryptography.
- Wiring tables are the standard Enigma I rotors I to V and reflectors UKW-A, B and C.
- The settings generator (`enigma_gen.c`) was initially drafted with Claude (Anthropic), then reviewed and modified by me.