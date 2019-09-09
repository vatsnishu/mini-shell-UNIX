CC=g++
CFLAGS=-I.
DEPS = functions.h
OBJ = readcommand.cpp main.cpp tokenize.cpp executecmd.cpp signal_handler.cpp

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

hellomake: $(OBJ)
	g++ -o $@ $^ $(CFLAGS)
