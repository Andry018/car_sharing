ifeq ($(OS),Windows_NT)   #Controlla se il sistema operativo è Windows. Se è Windows, usa il comando 'del' per rimuovere i file
	
    RM = del /Q
    EXE = .exe
else
    RM = rm -f
    EXE =
endif

car_sharing$(EXE): main.o vehicle.o prenotazioni.o fasceorarie.o
	gcc -Wall -Wextra -g -o car_sharing$(EXE) main.o vehicle.o prenotazioni.o fasceorarie.o
	$(RM) *.o

main.o: main.c
	gcc -Wall -Wextra -g -c main.c

vehicle.o: vehicle.c vehicle.h
	gcc -Wall -Wextra -g -c vehicle.c

prenotazioni.o: prenotazioni.c prenotazioni.h
	gcc -Wall -Wextra -g -c prenotazioni.c

fasceorarie.o: fasceorarie.c fasceorarie.h
	gcc -Wall -Wextra -g -c fasceorarie.c

clean:  									# Pulizia dei file oggetto e dell'eseguibile manuale tramite il comando 'make clean'
	$(RM) *.o car_sharing$(EXE)

