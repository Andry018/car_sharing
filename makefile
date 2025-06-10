ifeq ($(OS),Windows_NT)   
    RM = del
    EXE = .exe
    MKDIR = if not exist $(OBJDIR) mkdir $(OBJDIR)
    RMDIR = rmdir /s /q
    SEP = \\
    COMPILE_FLAGS = -Wall -Wextra -g -Isrc -Itests
    ICON = resources$(SEP)icon.ico
else
    RM = rm -f
    EXE =
    MKDIR = mkdir -p $(OBJDIR)
    RMDIR = rm -rf
    SEP = /
    COMPILE_FLAGS = -Wall -Wextra -g -Isrc -Itests
    PREFIX = $(HOME)/.local
    DESKTOP_FILE = car_sharing.desktop
    ICON = resources$(SEP)icon.png
endif

SRCDIR = src
OBJDIR = obj
RESDIR = resources
TESTSRCDIR = tests
TESTOBJS = $(OBJDIR)/test_car_sharing.o

# Crea la directory obj se non esiste (viene eliminata con il comando 'make clean')
$(shell $(MKDIR))

# Lista dei file oggetto
OBJS = $(OBJDIR)/main.o \
       $(OBJDIR)/veicolo.o \
       $(OBJDIR)/prenotazioni.o \
       $(OBJDIR)/fasce_orarie.o \
       $(OBJDIR)/utenti.o \
       $(OBJDIR)/hash.o \
       $(OBJDIR)/tariffe.o \
       $(OBJDIR)/data_sistema.o \
       $(OBJDIR)/menu.o \
       $(OBJDIR)/f_utili.o

# Aggiungi resource.res solo su Windows
ifeq ($(OS),Windows_NT)
OBJS += $(OBJDIR)/resource.res
endif

car_sharing$(EXE): $(OBJS)
	$(CC) $(COMPILE_FLAGS) -o car_sharing$(EXE) $(OBJS)
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

$(OBJDIR)/main.o: $(SRCDIR)/main.c $(SRCDIR)/veicolo.h $(SRCDIR)/prenotazioni.h $(SRCDIR)/tariffe.h $(SRCDIR)/utenti.h $(SRCDIR)/fasce_orarie.h $(SRCDIR)/f_utili.h
	$(CC) $(COMPILE_FLAGS) -c $(SRCDIR)/main.c -o $(OBJDIR)/main.o

$(OBJDIR)/veicolo.o: $(SRCDIR)/veicolo.c $(SRCDIR)/veicolo.h $(SRCDIR)/f_utili.h
	$(CC) $(COMPILE_FLAGS) -c $(SRCDIR)/veicolo.c -o $(OBJDIR)/veicolo.o

$(OBJDIR)/prenotazioni.o: $(SRCDIR)/prenotazioni.c $(SRCDIR)/prenotazioni.h $(SRCDIR)/veicolo.h $(SRCDIR)/test_utils.h
	$(CC) $(COMPILE_FLAGS) -c $(SRCDIR)/prenotazioni.c -o $(OBJDIR)/prenotazioni.o

$(OBJDIR)/fasce_orarie.o: $(SRCDIR)/fasce_orarie.c $(SRCDIR)/fasce_orarie.h
	$(CC) $(COMPILE_FLAGS) -c $(SRCDIR)/fasce_orarie.c -o $(OBJDIR)/fasce_orarie.o

$(OBJDIR)/utenti.o: $(SRCDIR)/utenti.c $(SRCDIR)/utenti.h
	$(CC) $(COMPILE_FLAGS) -c $(SRCDIR)/utenti.c -o $(OBJDIR)/utenti.o

$(OBJDIR)/hash.o: $(SRCDIR)/hash.c $(SRCDIR)/hash.h
	$(CC) $(COMPILE_FLAGS) -c $(SRCDIR)/hash.c -o $(OBJDIR)/hash.o

$(OBJDIR)/tariffe.o: $(SRCDIR)/tariffe.c $(SRCDIR)/tariffe.h
	$(CC) $(COMPILE_FLAGS) -c $(SRCDIR)/tariffe.c -o $(OBJDIR)/tariffe.o

$(OBJDIR)/data_sistema.o: $(SRCDIR)/data_sistema.c $(SRCDIR)/data_sistema.h
	$(CC) $(COMPILE_FLAGS) -c $(SRCDIR)/data_sistema.c -o $(OBJDIR)/data_sistema.o

$(OBJDIR)/menu.o: $(SRCDIR)/menu.c $(SRCDIR)/menu.h
	$(CC) $(COMPILE_FLAGS) -c $(SRCDIR)/menu.c -o $(OBJDIR)/menu.o

$(OBJDIR)/f_utili.o: $(SRCDIR)/f_utili.c $(SRCDIR)/f_utili.h
	$(CC) $(COMPILE_FLAGS) -c $(SRCDIR)/f_utili.c -o $(OBJDIR)/f_utili.o

$(OBJDIR)/resource.res: $(RESDIR)/resource.rc
	$(windres) $(RESDIR)/resource.rc -O coff -o $(OBJDIR)/resource.res

$(OBJDIR)/test_car_sharing.o: $(TESTSRCDIR)/test_car_sharing.c $(SRCDIR)/veicolo.h $(SRCDIR)/prenotazioni.h $(SRCDIR)/tariffe.h $(SRCDIR)/utenti.h $(SRCDIR)/fasce_orarie.h $(SRCDIR)/f_utili.h $(SRCDIR)/test_utils.h
	$(CC) $(COMPILE_FLAGS) -DTEST_BUILD -c $(TESTSRCDIR)/test_car_sharing.c -o $(OBJDIR)/test_car_sharing.o

# Solo le librerie necessarie per i test (escludi main.o)
TEST_LIBS = $(OBJDIR)/veicolo.o \
            $(OBJDIR)/prenotazioni.o \
            $(OBJDIR)/fasce_orarie.o \
            $(OBJDIR)/utenti.o \
            $(OBJDIR)/hash.o \
            $(OBJDIR)/tariffe.o \
            $(OBJDIR)/data_sistema.o \
            $(OBJDIR)/f_utili.o

test_car_sharing: test_car_sharing$(EXE)

test_car_sharing$(EXE): $(TESTOBJS) $(TEST_LIBS)
	$(CC) $(COMPILE_FLAGS) -o test_car_sharing$(EXE) $(TESTOBJS) $(TEST_LIBS)

clean:  									
ifeq ($(OS),Windows_NT)
	$(RM) $(OBJDIR)\\*.o
	$(RM) car_sharing$(EXE)
	$(RM) test_car_sharing$(EXE)
	$(RMDIR) $(OBJDIR)
else
	$(RM) $(OBJDIR)/*.o car_sharing$(EXE) test_car_sharing$(EXE)
	$(RMDIR) $(OBJDIR)
	$(RM) $(PREFIX)/share/applications/$(DESKTOP_FILE)
	$(RM) $(PREFIX)/share/icons/hicolor/256x256/apps/car_sharing.png
endif

