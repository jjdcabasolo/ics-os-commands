CC=gcc
ICSOS_ROOT=../..
SDK=../../sdk
CFLAGS=-m32 -nostdlib -fno-builtin -static
LIBS=$(SDK)/tccsdk.c $(SDK)/libtcc1.c $(SDK)/crt1.c 
EXE=quizbee.exe
PKMNEASY=pez.txt
PKMNAVER=pave.txt
PKMNDIFF=pdif.txt
HIGHPKMN=highsp.bin
MOVEASY=mez.txt
MOVAVER=mave.txt
MOVDIFF=mdif.txt
HIGHMOV=highsm.bin

$(EXE): quizbee.c
	$(CC) $(CFLAGS) -o${EXE} quizbee.c $(LIBS)

install: $(EXE)
	cp $(EXE) $(ICSOS_ROOT)/apps
	cp $(PKMNEASY) $(ICSOS_ROOT)/apps
	cp $(PKMNAVER) $(ICSOS_ROOT)/apps
	cp $(PKMNDIFF) $(ICSOS_ROOT)/apps
	cp $(HIGHPKMN) $(ICSOS_ROOT)/apps
	cp $(MOVEASY) $(ICSOS_ROOT)/apps
	cp $(MOVAVER) $(ICSOS_ROOT)/apps
	cp $(MOVDIFF) $(ICSOS_ROOT)/apps
	cp $(HIGHMOV) $(ICSOS_ROOT)/apps

uninstall:
	rm $(ICSOS_ROOT)/apps/$(EXE)
	rm $(ICSOS_ROOT)/apps/$(PKMNEASY)
	rm $(ICSOS_ROOT)/apps/$(PKMNAVER)
	rm $(ICSOS_ROOT)/apps/$(PKMNDIFF)
	rm $(ICSOS_ROOT)/apps/$(HIGHPKMN)
	rm $(ICSOS_ROOT)/apps/$(MOVEASY)
	rm $(ICSOS_ROOT)/apps/$(MOVAVER)
	rm $(ICSOS_ROOT)/apps/$(MOVDIFF)
	rm $(ICSOS_ROOT)/apps/$(HIGHMOV)

clean:
	rm $(EXE)


