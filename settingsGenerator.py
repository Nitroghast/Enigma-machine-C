from random import randint, shuffle, choices, sample
import string

def generateRotors():
    return tuple(sample(range(1,6), 3))

def generateRingsPositions():
    a = randint(0, 25)
    b = randint(0, 25)
    c = randint(0, 25)
    a = chr(ord("A") + a)
    b = chr(ord("A") + b)
    c = chr(ord("A") + c)
    return a, b, c

def linear_weighted_random(start, end):
    population = list(range(start, end + 1))
    weights = [i - start + 1 for i in population]
    chosen = choices(population, weights=weights, k=1)[0]
    return chosen

def generatePlugboard(swapNumber):
    letters = list(string.ascii_uppercase)
    shuffle(letters)
    
    swaps = []
    for i in range(swapNumber):
        pair = letters[i * 2] + letters[i * 2 + 1]
        swaps.append(pair)
    return swaps


def generateReflector():
    return chr(ord("A") + randint(0, 2))

def main():
    rotorOrder = list(generateRotors())
    ringSettings = list(generateRingsPositions())
    rotorPosition = list(generateRingsPositions())
    #swaps = generatePlugboard(linear_weighted_random(0, 6))
    swaps = generatePlugboard(10)

    print("ROTORS: ", end= "")
    for item in rotorOrder:
        print(item, end= "")
    print()

    print("ROTOR POSITIONS: ", end= "")
    for item in rotorPosition:
        print(item, end= "")
    print()

    print("RING SETTINGS: ", end= "")
    for item in ringSettings:
        print(item, end = "")
    print()

    print("PLUGBOARD: ", end= "")
    for item in swaps:
        print(item, end= "")
    
    print(f"\nREFLECTOR: {generateReflector()}")

main()