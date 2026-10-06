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


int inputFunc(char *argv[], FILE** input, FILE** config, FILE** output, int *rotorOrder, char *rotorPosition, char *ringSettings, char swapPairs[][3], size_t *swapNumber, char *reflectorType);
char encodeChar (enigmaMachine *machine, char plainText);

int main(int argc, char *argv[]) {
    
    if (argc != 4) {
        fprintf(stderr, "Format: path/to/the/file.exe path/to/input.txt path/to/configuration.txt path/to/output.txt\n");
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
    if (returnValue) return 1;

    enigmaMachine machineState = {
        .rotors = {
            rotors[rotorOrder[0]],
            rotors[rotorOrder[1]],
            rotors[rotorOrder[2]]
        }
    };

    strcpy(machineState.reflector, reflectors[reflector - 'A']);
    memcpy(machineState.plugboard, swapPairs, sizeof(swapPairs));

    char plainText;
    for (size_t counter = 0; fscanf(input, "%c", &plainText) != EOF;) {
        if (counter == 4) {
            fprintf(output, " ");
            counter = 0;
        }
        if (plainText == ' ' || plainText == '\n') {
            continue;
        }
        fprintf(output, "%c", encodeChar(&machineState, toupper(plainText)));
        counter++;
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
        return 1;
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