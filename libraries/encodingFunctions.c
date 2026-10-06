#include "encodingFunctions.h"

void stepRotors(enigmaMachine *machine) {
    Rotor *left = &machine->rotors[0];
    Rotor *middle = &machine->rotors[1];
    Rotor *right = &machine->rotors[2];

    int left_notch = left->notch - 'A';
    int middle_notch = middle->notch - 'A';
    int right_notch = right->notch - 'A';

    int middle_at_notch = (middle->position == middle_notch);
    int right_at_notch = (right->position == right_notch);

    right->position = (right->position + 1) % 26;

    if (right_at_notch || middle_at_notch) {
        middle->position = (middle->position + 1) % 26;
    }

    if (middle_at_notch) {
        left->position = (left->position + 1) % 26;
    }
}

char applyPlugboard(enigmaMachine *machine, char c) {
    for (int i = 0; i < 13; i++) {
        if (machine->plugboard[i][0] == '\0') {
            break;
        }
        if (machine->plugboard[i][0] == c) {
            return machine->plugboard[i][1];
        }
        if (machine->plugboard[i][1] == c) {
            return machine->plugboard[i][0];
        }
    }
    return c;
}

char rotorFwd(Rotor *rotor, char c) {
    int input_idx = c - 'A';
    int shift = rotor->position - rotor->ring;
    
    int idx = (input_idx + shift + 26) % 26;
    char substituted = rotor->forward[idx];
    int sub_idx = substituted - 'A';
    int output_idx = (sub_idx - shift + 26) % 26;

    return 'A' + output_idx;
}

char rotorRev(Rotor *rotor, char c) {
    int input_idx = c - 'A';
    int shift = rotor->position - rotor->ring;
    
    // Apply offset, look up reverse wiring, un-offset
    int idx = (input_idx + shift + 26) % 26;
    char substituted = rotor->reverse[idx];
    int sub_idx = substituted - 'A';
    int output_idx = (sub_idx - shift + 26) % 26;
    
    return 'A' + output_idx;
}

char reflectorTransform(enigmaMachine *machine, char c) {
    int idx = c - 'A';
    return machine->reflector[idx];
}