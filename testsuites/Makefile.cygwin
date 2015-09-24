INCDIR = -I../include/cygwin
LDDIR = -L../ -L../external/cygwin 
LDMOULE = -lsdfs -lgtest

OBJS = testrtable.o testdest.o testrentity.o testSerializer.o testprocesslist.o testSiBlock.o testBlocklist.o testTrunk.o testcommandQ.o

all: $(OBJS)

$(OBJS): %.o: %.cpp
	g++ -g -std=gnu++11 $< -o $@ $(INCDIR) $(LDDIR) $(LDMOULE) 
	./$@

clean : 
	rm -f *.o
