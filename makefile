ifeq ($(OS),Windows_NT)   
    RM = del
    EXE = .exe
    MKDIR = if not exist $(OBJDIR) mkdir $(OBJDIR)
    RMDIR = rmdir /s /q
    SEP = \\
    COMPILE_FLAGS = -Wall -Wextra -g
    ICON = resources$(SEP)icon.ico
else
    RM = rm -f
    EXE =
    MKDIR = mkdir -p $(OBJDIR)
    RMDIR = rm -rf
    SEP = /
    COMPILE_FLAGS = -Wall -Wextra -g
    PREFIX = $(HOME)/.local
    DESKTOP_FILE = car_sharing.desktop
    ICON = resources$(SEP)icon.png
endif

SRCDIR = src
OBJDIR = obj
RESDIR = resources

# Crea la directory obj se non esiste (viene eliminata con il comando 'make clean')
$(shell $(MKDIR))

# Lista dei file oggetto
OBJS = $(OBJDIR)/main.o \
       $(OBJDIR)/vehicle.o \
       $(OBJDIR)/prenotazioni.o \
       $(OBJDIR)/fasceorarie.o \
       $(OBJDIR)/utenti.o \
       $(OBJDIR)/hash.o \
       $(OBJDIR)/tariffe.o \
       $(OBJDIR)/data_sistema.o

# Aggiungi resource.res solo su Windows
ifeq ($(OS),Windows_NT)
OBJS += $(OBJDIR)/resource.res
endif

car_sharing$(EXE): $(OBJS)
	gcc $(COMPILE_FLAGS) -o car_sharing$(EXE) $(OBJS)
ifeq ($(OS),Windows_NT)
	$(RM) $(OBJDIR)\\*.o
	$(RMDIR) $(OBJDIR)
else
	$(RM) $(OBJDIR)/*.o
	$(RMDIR) $(OBJDIR)
	# Crea la directory per le icone se non esiste
	mkdir -p $(PREFIX)/share/icons/hicolor/256x256/apps
	mkdir -p $(PREFIX)/share/applications
	# Copia l'icona nella directory appropriata
	cp $(ICON) $(PREFIX)/share/icons/hicolor/256x256/apps/car_sharing.png
	# Crea il file .desktop
	echo "[Desktop Entry]" > $(DESKTOP_FILE)
	echo "Name=Car Sharing" >> $(DESKTOP_FILE)
	echo "Exec=$(shell pwd)/car_sharing" >> $(DESKTOP_FILE)
	echo "Icon=car_sharing" >> $(DESKTOP_FILE)
	echo "Type=Application" >> $(DESKTOP_FILE)
	echo "Categories=Utility;" >> $(DESKTOP_FILE)
	# Installa il file .desktop
	mv $(DESKTOP_FILE) $(PREFIX)/share/applications/
	# Aggiorna la cache delle icone
	-update-desktop-database $(PREFIX)/share/applications
	-gtk-update-icon-cache -f -t $(PREFIX)/share/icons/hicolor
endif

$(OBJDIR)/main.o: $(SRCDIR)/main.c
	gcc -Wall -Wextra -g -c $(SRCDIR)/main.c -o $(OBJDIR)/main.o

$(OBJDIR)/vehicle.o: $(SRCDIR)/vehicle.c $(SRCDIR)/vehicle.h
	gcc -Wall -Wextra -g -c $(SRCDIR)/vehicle.c -o $(OBJDIR)/vehicle.o

$(OBJDIR)/prenotazioni.o: $(SRCDIR)/prenotazioni.c $(SRCDIR)/prenotazioni.h
	gcc -Wall -Wextra -g -c $(SRCDIR)/prenotazioni.c -o $(OBJDIR)/prenotazioni.o

$(OBJDIR)/fasceorarie.o: $(SRCDIR)/fasceorarie.c $(SRCDIR)/fasceorarie.h
	gcc -Wall -Wextra -g -c $(SRCDIR)/fasceorarie.c -o $(OBJDIR)/fasceorarie.o

$(OBJDIR)/utenti.o: $(SRCDIR)/utenti.c $(SRCDIR)/utenti.h
	gcc -Wall -Wextra -g -c $(SRCDIR)/utenti.c -o $(OBJDIR)/utenti.o

$(OBJDIR)/hash.o: $(SRCDIR)/hash.c $(SRCDIR)/hash.h
	gcc -Wall -Wextra -g -c $(SRCDIR)/hash.c -o $(OBJDIR)/hash.o

$(OBJDIR)/tariffe.o: $(SRCDIR)/tariffe.c $(SRCDIR)/tariffe.h
	gcc -Wall -Wextra -g -c $(SRCDIR)/tariffe.c -o $(OBJDIR)/tariffe.o

$(OBJDIR)/data_sistema.o: $(SRCDIR)/data_sistema.c $(SRCDIR)/data_sistema.h
	gcc -Wall -Wextra -g -c $(SRCDIR)/data_sistema.c -o $(OBJDIR)/data_sistema.o

$(OBJDIR)/resource.res: $(RESDIR)/resource.rc
	windres $(RESDIR)/resource.rc -O coff -o $(OBJDIR)/resource.res

clean:  									
ifeq ($(OS),Windows_NT)
	$(RM) $(OBJDIR)\\*.o
	$(RM) car_sharing$(EXE)
	$(RMDIR) $(OBJDIR)
else
	$(RM) $(OBJDIR)/*.o car_sharing$(EXE)
	$(RMDIR) $(OBJDIR)
	$(RM) $(PREFIX)/share/applications/$(DESKTOP_FILE)
	$(RM) $(PREFIX)/share/icons/hicolor/256x256/apps/car_sharing.png
endif

