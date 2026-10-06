#include "inputFunctions.h"

/*
This file contains the openFile function, that opens the input, config and output files,
and all the functions needed to read the Enigma machine initial settings.
They all return the error codes defined in errorTypes.h (returning a value
that corresponds to 0 if everything goes correctly, so that if(returnValue) can be
used in the main to check if the function didn't work correctly).
*/

static bool isEndOfLine(FILE *input, bool eofIsValid) {
    char character = 0;
    int returnValue = fscanf(input, "%c", &character);

    if (returnValue == EOF) {
        return eofIsValid;
    }
    if (character == '\n') {
        return true;
    }
    if (character == '\r') {
        returnValue = fscanf(input, "%c", &character);
        if (returnValue == EOF) {
            return eofIsValid;
        }
        return character == '\n';
    }
    return false;
}

int openFile (FILE** input, FILE** config, FILE** output, char *inputPath, char *configPath, char *outputPath) {
    if ((*input = fopen(inputPath, "r")) == NULL) {
        return INPUT_ERROR;
    }
    if ((*config = fopen(configPath, "r")) == NULL) {
        return CONFIG_ERROR;
    }
    if ((*output = fopen(outputPath, "w")) == NULL) {
        return OUTPUT_ERROR;
    }
    return NO_FILE_ERROR;
}

int readRotorOrder (FILE* input, int *rotorOrder) {
    char rotors[3];
    int itemsRead = fscanf(input, "ROTORS:%*1[ ]%c%*1[ ]%c%*1[ ]%c", rotors, rotors + 1, rotors + 2);
    if (itemsRead != 4 || !isEndOfLine(input, false)) {
        return ROTOR_INVALID_INPUT_TYPE;
    }
    for (size_t i = 0; i < 3; i++) {
        if (rotors[i] - '0' < 1 || rotors[i] - '0' > 5) {
            return ROTOR_NUMBER_OUT_OF_RANGE;
        } else {
            rotorOrder[i] = rotors[i] - '1';
        }
    }
    if (rotorOrder[0] == rotorOrder[1] || 
        rotorOrder[1] == rotorOrder[2] || 
        rotorOrder[0] == rotorOrder[2]){
        return ROTOR_DUPLICATE;
    }
    return NO_ROTOR_ERROR;
}

int readRotorPositions (FILE* input, char *rotorPosition) {
    int itemsRead = fscanf(input, "ROTOR POSITIONS:%*1[ ]%c%*1[ ]%c%*1[ ]%c", rotorPosition, rotorPosition + 1, rotorPosition + 2);
    if (itemsRead != 3 || !isEndOfLine(input, false)) {
        return POSITION_INVALID_INPUT_TYPE;
    }
    for (size_t i = 0; i < 3; i++){
        if (rotorPosition[i] < 'A' || rotorPosition[i] > 'Z') {
            if (rotorPosition[i] >= 'a' && rotorPosition[i] <= 'z') {
                rotorPosition[i] += 'A' - 'a';
            } else {
                return POSITION_INVALID_CHAR;
            }
        }
    }
    return NO_POSITION_ERROR;
}

int readRingSettings (FILE* input, char *ringSettings) {
    int itemsRead = fscanf(input, "RING SETTINGS: %c %c %c\n", ringSettings, ringSettings + 1, ringSettings + 2);
    if (itemsRead != 3 || !isEndOfLine(input, false)) {
        return RING_INVALID_INPUT_TYPE;
    }
    for (size_t i = 0; i < 3; i++) {
        if (ringSettings[i] < 'A' || ringSettings[i] > 'Z') {
            if (ringSettings[i] >= 'a' && ringSettings[i] <= 'z') {
                ringSettings[i] += 'A' - 'a';
            }
            else {
                return RING_INVALID_CHAR;
            }
        }
    }
    return NO_RING_ERROR;
}

int readPlugboard(FILE *input, char swapPairs[][3], size_t *actualSwapCount) {
    char plugboardPairs[256];
    int prefixLength = 0;
    fscanf(input, "PLUGBOARD:%n", &prefixLength);
    if (prefixLength == 0) {
        return PLUGBOARD_INVALID_INPUT_TYPE;
    }

    int readAmount = fscanf(input, "%*1[ ]%255[^\r\n]", plugboardPairs);
    if (!isEndOfLine(input, false)) {
        return PLUGBOARD_INVALID_INPUT_TYPE;
    }
    if (readAmount != 1) {
        *actualSwapCount = 0;
        return NO_PLUGBOARD_ERROR; 
    }
    if (strlen(plugboardPairs) > 0 && plugboardPairs[strlen(plugboardPairs) - 1] == ' ') {
        return PLUGBOARD_INVALID_INPUT_TYPE;
    }

    size_t count = 0;
    char *token = strtok(plugboardPairs, " ");

    while (token != NULL) {
        if (strlen(token) != 2) {
            return PLUGBOARD_INVALID_PAIRING;
        }
        if (count >= 13) {
            return PLUGBOARD_INPUT_SWAP_AMOUNT_TOO_BIG;
        }
        strcpy(swapPairs[count], token);
        count++;
        token = strtok(NULL, " ");
    }

    size_t letterFreq[26] = {0};

    for (size_t i = 0; i < count; i++) {
        for (size_t j = 0; j < 2; j++) {
            if (!isalpha((unsigned char)swapPairs[i][j])) {
                return PLUGBOARD_INVALID_CHAR;
            }
            char upper = toupper((unsigned char)swapPairs[i][j]);
            swapPairs[i][j] = upper;
            size_t idx = upper - 'A';
            letterFreq[idx]++;
            if (letterFreq[idx] > 1) {
                return PLUGBOARD_DUPLICATE_LETTER;
            }
        }
    }

    *actualSwapCount = count;
    return NO_PLUGBOARD_ERROR;
}

int readReflector (FILE* input, char *reflectorType) {
    int itemsRead = fscanf(input, "REFLECTOR: %c\n", reflectorType);
    if (itemsRead != 1 || isEndOfLine(input, true)) {
        return REFLECTOR_INVALID_INPUT_TYPE;
    }
    if (*reflectorType < 'A' || *reflectorType > 'C') {
        if (*reflectorType >= 'a' && *reflectorType <= 'c') {
            *reflectorType += 'A' - 'a';
        } else {
            return REFLECTOR_CHAR_OUT_OF_RANGE;
        }
    }
    return NO_REFLECTOR_ERROR;
}