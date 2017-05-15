CC=gcc
ICSOS_ROOT=../..
SDK=../../sdk
CFLAGS=-m32 -nostdlib -fno-builtin -static
LIBS=$(SDK)/tccsdk.c $(SDK)/libtcc1.c $(SDK)/crt1.c 
EXE=quizbee.exe
PKMNEASY=pez.txt
PEPE=pokemone.txt

$(EXE): quizbee.c
	$(CC) $(CFLAGS) -o${EXE} quizbee.c $(LIBS)

install: $(EXE)
	cp $(EXE) $(ICSOS_ROOT)/apps
	cp $(PKMNEASY) $(ICSOS_ROOT)/apps

uninstall:
	rm $(ICSOS_ROOT)/apps/$(EXE)
	rm $(ICSOS_ROOT)/apps/$(PEPE) 
	rm $(ICSOS_ROOT)/apps/$(PKMNEASY)

clean:
	rm $(EXE)


