// Copyright (c) 2026 Alfredo Maria Luigi Sammartino (Nitroghast)
// SPDX-License-Identifier: MPL-2.0

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <errno.h>
 
#define ALPHABET_SIZE   26
#define NUM_ROTORS_POOL 5
#define NUM_ROTORS_USED 3 

static const int plugboardSwaps = 10;
static uint64_t rngState;

static void rngSeed(uint64_t seed);
static uint64_t rngNext(void);
static uint32_t rngBelow(uint32_t n);
static void shuffle(int *arr, int len);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <seed>\n", argv[0]);
        return 1;
    }

    if (plugboardSwaps < 0 || plugboardSwaps > ALPHABET_SIZE / 2) {
        fprintf(stderr, "Error: plugboardSwaps must be between 0 and %d\n",
            ALPHABET_SIZE / 2);
            return 1;
        }

    char *end = NULL;
    errno = 0;
    unsigned long long seedParsed = strtoull(argv[1], &end, 10);
    if (errno != 0 || end == argv[1] || *end != '\0' || argv[1][0] == '-') {
        fprintf(stderr, "Error: seed must be a non-negative integer\n");
        return 1;
    }
    rngSeed((uint64_t)seedParsed);

    int rotorPool[NUM_ROTORS_POOL];
    for (int i = 0; i < NUM_ROTORS_POOL; i++) rotorPool[i] = i + 1;
    shuffle(rotorPool, NUM_ROTORS_POOL);
    int rotors[NUM_ROTORS_USED];
    for (int i = 0; i < NUM_ROTORS_USED; i++) rotors[i] = rotorPool[i];

    char positions[NUM_ROTORS_USED];
    char rings[NUM_ROTORS_USED];
    for (int i = 0; i < NUM_ROTORS_USED; i++)
    positions[i] = (char)('A' + rngBelow(ALPHABET_SIZE));
    for (int i = 0; i < NUM_ROTORS_USED; i++)
    rings[i] = (char)('A' + rngBelow(ALPHABET_SIZE));

    int letters[ALPHABET_SIZE];
    for (int i = 0; i < ALPHABET_SIZE; i++) letters[i] = i;
    shuffle(letters, ALPHABET_SIZE);
    const char reflector = (char)('A' + rngBelow(3));

    char filename[64];
    snprintf(filename, sizeof(filename), "enigma_settings_%llu.txt", seedParsed);

    FILE *f = fopen(filename, "w");
    if (!f) {
        perror("Error opening output file");
        return 1;
    }

    fprintf(f, "ROTORS: %d %d %d\n", rotors[0], rotors[1], rotors[2]);
    fprintf(f, "ROTOR POSITIONS: %c %c %c\n",
    positions[0], positions[1], positions[2]);
    fprintf(f, "RING SETTINGS: %c %c %c\n", rings[0], rings[1], rings[2]);

    fprintf(f, "PLUGBOARD:");
    for (int i = 0; i < plugboardSwaps; i++) {
        fprintf(f, " %c%c", 'A' + letters[2 * i], 'A' + letters[2 * i + 1]);
    }
    fprintf(f, "\n");

    fprintf(f, "REFLECTOR: %c\n", reflector);

    fclose(f);
    printf("Settings written to %s\n", filename);
    return 0;
}

static void rngSeed(uint64_t seed) {
    rngState = seed;
}
    
static uint64_t rngNext(void) {
    uint64_t z = (rngState += 0x9E3779B97F4A7C15ULL);
    z = (z ^ (z >> 30)) * 0xBF58476D1CE4E5B9ULL;
    z = (z ^ (z >> 27)) * 0x94D049BB133111EBULL;
    return z ^ (z >> 31);
}

static uint32_t rngBelow(uint32_t n) {
    uint64_t limit = UINT64_MAX - (UINT64_MAX % n);
    uint64_t r;
    do {
        r = rngNext();
    } while (r >= limit);
    return (uint32_t)(r % n);
}

static void shuffle(int *arr, int len) {
    for (int i = len - 1; i > 0; i--) {
        int j = (int)rngBelow((uint32_t)(i + 1));
        int tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
    }
}