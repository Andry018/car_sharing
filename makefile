ifeq ($(OS),Windows_NT)   #Controlla se il sistema operativo è Windows. Se è Windows, usa il comando 'del' per rimuovere i file
	
    RM = del
    EXE = .exe
    MKDIR = if not exist $(OBJDIR) mkdir $(OBJDIR)
    RMDIR = rmdir /s /q
    SEP = \\
else
    RM = rm -f
    EXE =
    MKDIR = mkdir -p $(OBJDIR)
    RMDIR = rm -rf
    SEP = /
endif

SRCDIR = src
OBJDIR = obj

# Crea la directory obj se non esiste (viene eliminata con il comando 'make clean')
$(shell $(MKDIR))

car_sharing$(EXE): $(OBJDIR)/main.o $(OBJDIR)/vehicle.o $(OBJDIR)/prenotazioni.o $(OBJDIR)/fasceorarie.o
	gcc -Wall -Wextra -g -o car_sharing$(EXE) $(OBJDIR)/main.o $(OBJDIR)/vehicle.o $(OBJDIR)/prenotazioni.o $(OBJDIR)/fasceorarie.o
ifeq ($(OS),Windows_NT)
	$(RM) $(OBJDIR)\\*.o
	$(RMDIR) $(OBJDIR)
else
	$(RM) $(OBJDIR)/*.o
	$(RMDIR) $(OBJDIR)
endif

$(OBJDIR)/main.o: $(SRCDIR)/main.c
	gcc -Wall -Wextra -g -c $(SRCDIR)/main.c -o $(OBJDIR)/main.o

$(OBJDIR)/vehicle.o: $(SRCDIR)/vehicle.c $(SRCDIR)/vehicle.h
	gcc -Wall -Wextra -g -c $(SRCDIR)/vehicle.c -o $(OBJDIR)/vehicle.o

$(OBJDIR)/prenotazioni.o: $(SRCDIR)/prenotazioni.c $(SRCDIR)/prenotazioni.h
	gcc -Wall -Wextra -g -c $(SRCDIR)/prenotazioni.c -o $(OBJDIR)/prenotazioni.o

$(OBJDIR)/fasceorarie.o: $(SRCDIR)/fasceorarie.c $(SRCDIR)/fasceorarie.h
	gcc -Wall -Wextra -g -c $(SRCDIR)/fasceorarie.c -o $(OBJDIR)/fasceorarie.o

clean:  									# Pulizia dei file oggetto e dell'eseguibile manuale tramite il comando 'make clean'
ifeq ($(OS),Windows_NT)
	$(RM) $(OBJDIR)\\*.o
	$(RM) car_sharing$(EXE)
	$(RMDIR) $(OBJDIR)
else
	$(RM) $(OBJDIR)/*.o car_sharing$(EXE)
	$(RMDIR) $(OBJDIR)
endif

