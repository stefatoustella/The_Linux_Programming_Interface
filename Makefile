CC = gcc
CFLAGS = -Wall -Wextra -I.
LDFLAGS = 

# Library objects
ERR_OBJS = error_functions.o
UGID_OBJS = ugid_functions.o

# Libraries
LIBS = libugid.a liberr.a

# Main program
PROG = idshow

all: $(LIBS) $(PROG)

libugid.a: $(UGID_OBJS)
	ar cr $@ $^

liberr.a: $(ERR_OBJS)
	ar cr $@ $^

$(PROG): $(PROG).o $(LIBS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o $(PROG) $(LIBS)