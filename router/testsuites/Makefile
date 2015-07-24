INCDIR = -I../../include
LDDIR = -L../ -L../../external -L../../sha1
LDMOULE = -lroute -lgtest -lsha1

OBJS = testrtable.o testdest.o testrentry.o

all: $(OBJS)

$(OBJS): %.o: %.cpp
	g++ -g $< -o $@ $(INCDIR) $(LDDIR) $(LDMOULE)
	#./$@

clean : 
	rm -f *.o
