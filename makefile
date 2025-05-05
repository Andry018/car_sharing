car_sharing: main.o vehicle.o
	gcc -Wall -Wextra -g -o car_sharing main.o vehicle.o
	del *.o

main.o: main.c
	gcc -Wall -Wextra -g -c main.c

vehicle.o: vehicle.c vehicle.h
	gcc -Wall -Wextra -g -c vehicle.c

clean:
	del *.o car_sharing.exe

