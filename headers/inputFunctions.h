// Copyright (c) 2026 Alfredo Maria Luigi Sammartino (Nitroghast)
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "errorTypes.h"

int openFile (FILE** input, FILE** config, FILE** output, char *inputPath, char *configPath, char *outputPath);
int readRotorOrder (FILE* input, int *rotorOrder);
int readRotorPositions (FILE* input, char *rotorPosition);
int readRingSettings (FILE* input, char *ringSettings);
int readPlugboard(FILE *input, char swapPairs[][3], size_t *actualSwapCount);
int readReflector (FILE* input, char *reflectorType);