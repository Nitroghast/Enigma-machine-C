#pragma once
#include "utilityStructs.h"

Rotor rotors[5] = {
    // Rotor I
    {
        .forward = "EKMFLGDQVZNTOWYHXUSPAIBRCJ",
        .reverse = "UWYGADFPVZBECKMTHXSLRINQOJ",
        .notch = 'Q',
        .position = 0,
        .ring = 0
    },
    // Rotor II
    {
        .forward = "AJDKSIRUXBLHWTMCQGZNPYFVOE",
        .reverse = "AJPCZWRLFBDKOTYUQGENHXMIVS",
        .notch = 'E',
        .position = 0,
        .ring = 0
    },
    // Rotor III
    {
        .forward = "BDFHJLCPRTXVZNYEIWGAKMUSQO",
        .reverse = "TAGBPCSDQEUFVNZHYIXJWLRKOM",
        .notch = 'V',
        .position = 0,
        .ring = 0
    },
    // Rotor IV
    {
        .forward = "ESOVPZJAYQUIRHXLNFTGKDCMWB",
        .reverse = "HZWVARTNLGUPXQCEJMBSKDYOIF",
        .notch = 'J',
        .position = 0,
        .ring = 0
    },
    //Rotor V
    {
        .forward = "VZBRGITYUPSDNHLXAWMJQOFECK",
        .reverse = "QCYLXWENFTZOSMVJUDKGIARPHB",
        .notch = 'Z',
        .position = 0,
        .ring = 0
    }
};