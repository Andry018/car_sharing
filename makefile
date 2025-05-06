car_sharing: main.o vehicle.o prenotazioni.o
	gcc -Wall -Wextra -g -o car_sharing main.o vehicle.o prenotazioni.o
	del *.o

main.o: main.c
	gcc -Wall -Wextra -g -c main.c

vehicle.o: vehicle.c vehicle.h
	gcc -Wall -Wextra -g -c vehicle.c

prenotazioni.o: prenotazioni.c prenotazioni.h
	gcc -Wall -Wextra -g -c prenotazioni.c

fasceorarie.o: fasceorarie.c fasceorarie.h
	gcc -Wall -Wextra -g -c fasceorarie.c

clean:
	del *.o car_sharing.exe

