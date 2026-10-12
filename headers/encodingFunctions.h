// Copyright (c) 2026 Alfredo Maria Luigi Sammartino (Nitroghast)
// SPDX-License-Identifier: MPL-2.0

#pragma once
#include <stdio.h>
#include "utilityStructs.h"

void stepRotors(enigmaMachine *machine);
char rotorFwd(Rotor *rotor, char c);
char rotorRev(Rotor *rotor, char c);
char applyPlugboard(enigmaMachine *machine, char c);
char reflectorTransform(enigmaMachine *machine, char c);