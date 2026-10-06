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

## Project layout

```
main.c               program entry point and encoding loop
headers/             header files (rotor and reflector wiring, structs, error codes)
libraries/           config parsing, error messages, rotor and plugboard logic
Makefile             build instructions
input.txt            sample input
config.txt           sample configuration
output.txt           output obtained by running sample input with sample config thru
decrypted.txt        output obtained by running output.txt with sample config thru
settingsGenerator.py generates random settings
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
