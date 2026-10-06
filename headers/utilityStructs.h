#pragma once

typedef struct {
    char forward[27];
    char reverse[27];
    char notch;
    int position;
    int ring;
} Rotor;

typedef struct {
    Rotor rotors[3]; // Index 0: Left, Index 1: Middle, Index 2: Right
    char reflector[27];
    char plugboard[13][3];
} enigmaMachine;