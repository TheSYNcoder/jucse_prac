IDIR =include
CC=gcc
CFLAGS=-I$(IDIR)
SRC=src
ODIR=build
# LDIR =../lib

# LIBS=-lm

SOURCE = $(wildcard $(SRC)/*.c)
OBJECTS = $(patsubst $(SRC)/%.c, $(ODIR)/%.o, $(SOURCE))

$(info    OBJECTS is $(OBJECTS))
$(info    SOURCE is $(SOURCE))


$(ODIR)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) -c $< -o $@ 



# shell: $(OBJECTS)
shell : $(ODIR)/main.o
	$(CC) -o $@ $^ $(CFLAGS)

.PHONY: clean

# ~ means to ignore all the warings if file is not present

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 




#############


# shorter version

# CC=gcc
# CFLAGS=-I.
# DEPS = shell.h

# # $@ directs the output to the left 

# # %.o: %.c 
# # #$(DEPS)

# %.o: %.c 
# 	$(CC) -c -o $@ $< $(CFLAGS)

# shell: main.o  
# 	$(CC) -o shell main.o 



