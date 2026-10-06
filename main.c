#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "errorTypes.h"
#include "errorFunctions.h"
#include "inputFunctions.h"
#include "encodingFunctions.h"
#include "utilityStructs.h"
#include "rotors.h"
#include "reflectors.h"
#include <stdlib.h>

#ifdef _WIN32
    #define RESOLVE(path, buf) _fullpath((buf), (path), sizeof(buf))
    #define PATHCMP _stricmp
#else
    #include <limits.h>
    #define RESOLVE(path, buf) realpath((path), (buf))
    #define PATHCMP strcmp
#endif


#define LETTERS_PER_WORD 4
#define WORDS_PER_LINE 10


int inputFunc(char *argv[], FILE** input, FILE** config, FILE** output, int *rotorOrder, char *rotorPosition, char *ringSettings, char swapPairs[][3], size_t *swapNumber, char *reflectorType);
char encodeChar(enigmaMachine *machine, char plainText);
static bool samePath(const char *a, const char *b);

int main(int argc, char *argv[]) {

    if (argc != 4) {
        fprintf(stderr, "Format: path/to/the/file.exe path/to/input.txt path/to/configuration.txt path/to/output.txt\n");
        return 1;
    }

    if (samePath(argv[1], argv[3]) || samePath(argv[2], argv[3])) {
    fprintf(stderr, "Output file must be different from the input and config files.\n");
    return 1;
    }

    //File handling
    FILE* input = NULL;
    FILE* config = NULL;
    FILE* output = NULL;

    int rotorOrder[3];
    char rotorPosition[3];
    char ringSettings[3];
    char swapPairs[13][3] = {'\0'};
    size_t swapAmount = 0;
    char reflector;

    int returnValue = inputFunc(argv, &input, &config, &output, rotorOrder, rotorPosition, ringSettings, swapPairs, &swapAmount, &reflector);
    if (returnValue == 2) {
        return 1;
    } else if (returnValue) {
        fclose(input);
        fclose(config);
        fclose(output);
        return 1;
    }

    enigmaMachine machineState = {
        .rotors = {
            rotors[rotorOrder[0]],
            rotors[rotorOrder[1]],
            rotors[rotorOrder[2]]
        }
    };

    for (size_t i = 0; i < 3; i++) {
        machineState.rotors[i].ring = ringSettings[i] - 'A';
        machineState.rotors[i].position = rotorPosition[i] - 'A';
    }
    strcpy(machineState.reflector, reflectors[reflector - 'A']);
    memcpy(machineState.plugboard, swapPairs, sizeof(swapPairs));

    char plainText;
    for (size_t wordCounter = 0, lineCounter = 0; fscanf(input, "%c", &plainText) != EOF;) {
        if (!isalpha((unsigned char) plainText)) continue;
        if (wordCounter == LETTERS_PER_WORD) {
            lineCounter++;
            if (lineCounter == WORDS_PER_LINE) {
                fprintf(output, "\n");
                lineCounter = 0;
            }else {
                fprintf(output, " ");
            }
            wordCounter = 0;
        }
        fprintf(output, "%c", encodeChar(&machineState, toupper(plainText)));
        wordCounter++;
    }

fclose(input);
fclose(config);
fclose(output);
return 0;
}

int inputFunc(char *argv[], FILE** input, FILE** config, FILE** output, int *rotorOrder, char *rotorPosition, char *ringSettings, char swapPairs[][3], size_t *swapNumber, char *reflectorType) {
    int readResult = openFile(input, config, output, argv[1], argv[2], argv[3]);
    if (readResult){
        handleFileError(readResult, *input, *config);
        return 2;
    }

    //Rotor settings
    readResult = readRotorOrder(*config, rotorOrder);
    if (readResult) {
        handleRotorError(readResult);
        return 1;
    }


    //Rotor starting position 
    readResult = readRotorPositions(*config, rotorPosition);
    if (readResult) {
        handlePositionError(readResult);
        return 1;
    }


    //Ring settings
    readResult = readRingSettings(*config, ringSettings);
    if (readResult) {
        handleRingError(readResult);
        return 1;
    }

    //Plugboard settings
    readResult = readPlugboard(*config, swapPairs, swapNumber);
    if (readResult) {
        handlePlugboardError(readResult);
        return 1;
    }

    //Reflector
    readResult = readReflector(*config, reflectorType);
    if (readResult) {
        handleReflectorError(readResult);
        return 1;
    }

    return 0;
}

char encodeChar(enigmaMachine *machine, char plainText) {
    stepRotors(machine);

    char current = applyPlugboard(machine, plainText);

    current = rotorFwd(&machine->rotors[2], current); // Right Rotor
    current = rotorFwd(&machine->rotors[1], current); // Middle Rotor
    current = rotorFwd(&machine->rotors[0], current); // Left Rotor

    current = reflectorTransform(machine, current);

    current = rotorRev(&machine->rotors[0], current); // Left Rotor
    current = rotorRev(&machine->rotors[1], current); // Middle Rotor
    current = rotorRev(&machine->rotors[2], current); // Right Rotor

    current = applyPlugboard(machine, current);

    return current;
}

static bool samePath(const char *a, const char *b) {
    char ra[4096], rb[4096];
    if (PATHCMP(a, b) == 0) return true;
    if (!RESOLVE(a, ra) || !RESOLVE(b, rb)) return false;
    return PATHCMP(ra, rb) == 0;
}