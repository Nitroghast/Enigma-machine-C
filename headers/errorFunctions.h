// Copyright (c) 2026 Alfredo Maria Luigi Sammartino (Nitroghast)
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include <stdio.h>
#include "errorTypes.h"

void handleFileError (int readResult, FILE* input, FILE* config);
void handleRotorError (int readResult);
void handlePositionError(int readResult);
void handleRingError (int readResult);
void handlePlugboardError (int readResult);
void handleReflectorError (int readResult);