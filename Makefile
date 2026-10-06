CC = gcc
CFLAGS = -Wall -Wextra -Iheaders

enigma.exe: main.o libraries/errorFunctions.o libraries/inputFunctions.o libraries/encodingFunctions.o
	$(CC) main.o libraries/errorFunctions.o libraries/inputFunctions.o libraries/encodingFunctions.o -o enigma.exe

main.o: main.c headers/errorTypes.h headers/errorFunctions.h headers/inputFunctions.h headers/encodingFunctions.h headers/utilityStructs.h
	$(CC) $(CFLAGS) -c main.c

libraries/errorFunctions.o: libraries/errorFunctions.c headers/errorFunctions.h headers/errorTypes.h
	$(CC) $(CFLAGS) -c libraries/errorFunctions.c -o libraries/errorFunctions.o

libraries/inputFunctions.o: libraries/inputFunctions.c headers/inputFunctions.h headers/errorTypes.h
	$(CC) $(CFLAGS) -c libraries/inputFunctions.c -o libraries/inputFunctions.o

libraries/encodingFunctions.o: libraries/encodingFunctions.c headers/encodingFunctions.h headers/rotors.h headers/reflectors.h headers/utilityStructs.h
	$(CC) $(CFLAGS) -c libraries/encodingFunctions.c -o libraries/encodingFunctions.o

clean:
	Remove-Item -Force -ErrorAction SilentlyContinue *.o, libraries/*.o, enigma.exe