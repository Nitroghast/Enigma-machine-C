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


def formatLine(label, items):
    return f"{label}: " + " ".join(str(item) for item in items) + "\n"


def main():
    filename = input("Output file: ")

    rotorOrder = list(generateRotors())
    ringSettings = list(generateRingsPositions())
    rotorPosition = list(generateRingsPositions())
    #swaps = generatePlugboard(linear_weighted_random(0, 6))
    swaps = generatePlugboard(10)
    reflector = generateReflector()

    with open(filename, "w") as f:
        f.write(formatLine("ROTORS", rotorOrder))
        f.write(formatLine("ROTOR POSITIONS", rotorPosition))
        f.write(formatLine("RING SETTINGS", ringSettings))
        f.write(formatLine("PLUGBOARD", swaps))
        f.write(formatLine("REFLECTOR", reflector))

main()