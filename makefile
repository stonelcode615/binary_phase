CC = mpicxx 
LDLAGS = -lm
INCLUDE = header.h
OBJ = testing.o computing.o reading.o fitting.o main.o
EXE = exe

%.o: %.c $(INCLUDE) 
	$(CC) -c -o $@ $<  
$(EXE): $(OBJ)
	$(CC) -o $@ $^ $(LDLAGS)

clean:
	rm -f $(OBJ) $(EXE)
