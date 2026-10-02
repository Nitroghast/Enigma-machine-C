#pragma once
/*

This file contains the definitions of all the error codes
(including NO_ERROR, defined as 0 in every case).
*/

typedef enum {
    NO_FILE_ERROR,
    INPUT_ERROR,
    CONFIG_ERROR,
    OUTPUT_ERROR
} fileOpeningError;

typedef enum {
    NO_ROTOR_ERROR,
    ROTOR_INVALID_INPUT_TYPE,
    ROTOR_NUMBER_OUT_OF_RANGE,
    ROTOR_DUPLICATE
} rotorError;

typedef enum {
    NO_POSITION_ERROR,
    POSITION_INVALID_INPUT_TYPE,
    POSITION_INVALID_CHAR
} positionError;

typedef enum {
    NO_RING_ERROR,
    RING_INVALID_INPUT_TYPE,
    RING_INVALID_CHAR
} ringError;

typedef enum {
    NO_PLUGBOARD_ERROR,
    PLUGBOARD_INVALID_INPUT_TYPE, //Input is not in the form of "PLUGBOARD: <string>\n"
    PLUGBOARD_INVALID_PAIRING, //There is a "pair" that is not actually a pair
    PLUGBOARD_INVALID_CHAR, //There is one char that is not a letter of the alphabet
    PLUGBOARD_INPUT_SWAP_AMOUNT_TOO_BIG,
    PLUGBOARD_DUPLICATE_LETTER
} plugboardError;

typedef enum {
    NO_REFLECTOR_ERROR,
    REFLECTOR_INVALID_INPUT_TYPE,
    REFLECTOR_CHAR_OUT_OF_RANGE
} reflectorError;