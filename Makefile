CC = gcc
CFLAGS = -Wall -Wextra -Iheaders

enigma.exe: main.o libraries/errorFunctions.o libraries/inputFunctions.o
	$(CC) main.o libraries/errorFunctions.o libraries/inputFunctions.o -o enigma.exe

main.o: main.c headers/errorFunctions.h headers/inputFunctions.h headers/errorTypes.h
	$(CC) $(CFLAGS) -c main.c

libraries/errorFunctions.o: libraries/errorFunctions.c headers/errorFunctions.h headers/errorTypes.h
	$(CC) $(CFLAGS) -c libraries/errorFunctions.c -o libraries/errorFunctions.o

libraries/inputFunctions.o: libraries/inputFunctions.c headers/inputFunctions.h headers/errorTypes.h
	$(CC) $(CFLAGS) -c libraries/inputFunctions.c -o libraries/inputFunctions.o

clean:
	Remove-Item -Force -ErrorAction SilentlyContinue *.o, libraries/*.o, enigma.exe