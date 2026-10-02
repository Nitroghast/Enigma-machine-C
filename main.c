#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "errorFunctions.h"
#include "errorTypes.h"
#include "inputFunctions.h"


int inputFunc(char *argv[], FILE** input, FILE** config, FILE** output, int *rotorOrder, char *rotorPosition, char *ringSettings, char swapPairs[][3], size_t *swapNumber, char *reflectorType);

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
    char swapPairs[13][3];
    size_t swapAmount = 0;
    char reflector;

    int returnValue = inputFunc(argv, &input, &config, &output, rotorOrder, rotorPosition, ringSettings, swapPairs, &swapAmount, &reflector);
    if (returnValue) return 1;

    /*
    int test = 0;
    printf("Test sui rotori [0/1]? ");
    scanf("%d", &test); 
    if (test) {
        for (size_t i = 0; i < 3; i++) {
            fprintf(output, "%d ", rotorOrder[i]);
        }
    }
    */
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