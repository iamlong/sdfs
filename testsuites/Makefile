INCDIR = -I../include
LDDIR = -L../ -L../external 
LDMOULE = -lsdfs -lgtest 

OBJS = testrtable.o testdest.o testrentry.o

all: $(OBJS)

$(OBJS): %.o: %.cpp
	g++ -g $< -o $@ $(INCDIR) $(LDDIR) $(LDMOULE)
	#./$@

clean : 
	rm -f *.o
