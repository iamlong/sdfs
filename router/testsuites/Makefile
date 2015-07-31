INCDIR = -I../../include
LDDIR = -L../ -L../../external -L../../sha1 -L../../util
LDMOULE = -lroute -lgtest -lsha1 -lutils

OBJS = testrtable.o testdest.o testrentry.o

all: $(OBJS)

$(OBJS): %.o: %.cpp
	g++ -g $< -o $@ $(INCDIR) $(LDDIR) $(LDMOULE)
	#./$@

clean : 
	rm -f *.o
