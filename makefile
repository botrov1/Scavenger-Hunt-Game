CC=gcc
CFLAGS=-I. -g
OBJ = MacUILib.o myStringLib.o PPA3.o 
DEPS = *.h
EXEC = PPA3

ifeq (${OS}, Windows_NT)
	OSSETTING = -DWINDOWS
else
	OSSETTING = -DPOSIX
	POSTLINKER = -lncurses
endif

%.o: %.c $(DEPENDS)
	$(CC) ${OSSETTING} -c -o $@ $< $(CFLAGS)

${EXEC} : $(OBJ)
	$(CC) ${OSSETTING} -o $@ $^ $(CFLAGS) ${POSTLINKER}

clean :
	rm -r ${OBJ} ${EXEC} ${EXEC}.exe
	

