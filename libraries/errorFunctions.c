#include "errorFunctions.h"

/*
This file contains the functions used to handle error codes,
i.e. they receive the error code returned by the relative input 
function and print to stderr an explanation of what went wrong
and how to fix it (if the issue does not arise in the file opening part).
The error codes are defined in errorTypes.h.
It's the responsibility of the caller to end the program or to deal in 
some other way with the fact that an error code was returned.
*/

void handleFileError (int readResult, FILE* input, FILE* config) {
    switch(readResult){
        case INPUT_ERROR:
            fprintf(stderr, "Input file opening failed.\n");
            break;
        case CONFIG_ERROR:
            fprintf(stderr, "Config file opening failed.\n");
            fclose(input);
            break;
        case OUTPUT_ERROR:
            fprintf(stderr, "Output file opening failed.\n");
            fclose(input);
            fclose(config);
            break;
        default:
            fprintf(stderr, "Something else went wrong.\n");
            break;
    }
}

void handleRotorError (int readResult) {
    switch(readResult){
        case ROTOR_INVALID_INPUT_TYPE:
            fprintf(stderr, "Format for the rotors should be\n"
            "\"ROTORS: <number> <number> <number>\", with the numbers being arabic numerals\n"
            "with no spaces at the end, only the newline.\n");
            break;
        case ROTOR_NUMBER_OUT_OF_RANGE:
            fprintf(stderr, "Rotor values must be between 1 and 5 (both inclusive).\n");
            break;
        case ROTOR_DUPLICATE:
            fprintf(stderr, "Rotor numbers must be all different numbers.\n");
            break;
        default:
            fprintf(stderr, "Something else went wrong.\n");
            break;
    }
}

void handlePositionError(int readResult) {
    switch (readResult) {
        case POSITION_INVALID_INPUT_TYPE:
            fprintf(stderr, "Format for the rotor initial positions should be\n"
            "\"ROTOR POSITIONS: <letter> <letter> <letter>\",\n"
            "with no spaces at the end, only the newline.\n");
            break;
        case POSITION_INVALID_CHAR:
            fprintf(stderr, "Only valid input is letters of the English alphabet (A-Z).\n");
            break;
        default:
            fprintf(stderr, "Something else went wrong.\n");
            break;
    }
}

void handleRingError (int readResult) {
    switch (readResult) {
        case RING_INVALID_INPUT_TYPE:
            fprintf(stderr, "Format for the ring positions should be\n"
            "\"RING SETTINGS: <letter> <letter> <letter>\",\n"
            "with no spaces at the end, only the newline.\n");
            break;
        case RING_INVALID_CHAR:
            fprintf(stderr, "Only valid input is letters of the English alphabet (A-Z).\n");
            break;
        default:
            fprintf(stderr, "Something else went wrong.\n");
            break;
    }
}

void handlePlugboardError (int readResult) {
    switch (readResult) {
        case PLUGBOARD_INVALID_INPUT_TYPE:
            fprintf(stderr, "Format for the plugboard should be\n"
            "\"PLUGBOARD: <letter pairs separated by spaces>\",\n"
            "with no spaces at the end, only the newline.\n");
            break;
        case PLUGBOARD_INVALID_PAIRING:
            fprintf(stderr, "Letters must be in groups of 2 separated by spaces, there is at least one letter group of length != 2.\n");
            break;
        case PLUGBOARD_INVALID_CHAR:
            fprintf(stderr, "Only valid input is letters of the English alphabet (A-Z) and spaces in between.\n");
            break;
        case PLUGBOARD_INPUT_SWAP_AMOUNT_TOO_BIG:
            fprintf(stderr, "There can be at most 13 swaps (26 letters of the alphabet).\n");
            break;
        case PLUGBOARD_DUPLICATE_LETTER:
            fprintf(stderr, "There can be no duplicates in the plugboard, each letter can be paired to only one other letter.\n");
            break;
        default:
            fprintf(stderr, "Something else went wrong.\n");
            break;
    }
}

void handleReflectorError (int readResult) {
    switch (readResult) {
    case REFLECTOR_INVALID_INPUT_TYPE:
        fprintf(stderr, "Format for the reflector should be\n"
        "\"REFLECTOR: <letter A-C>\",\n"
        "with no spaces at the end, only the newline.\n");
        break;
    case REFLECTOR_CHAR_OUT_OF_RANGE:
        fprintf(stderr, "Input must be a letter A-C.\n");
        break;
    default:
        fprintf(stderr, "Something else went wrong.\n");
        break;
    }
}