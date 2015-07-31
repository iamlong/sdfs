OBJS = rtable.o dest.o rentry.o
LDDIR = -L../sha1 -L../util
LDMODULE = -lsha1 -lutils

all: $(OBJS)

$(OBJS) : %.o : %.cpp
	g++ -g -c $< -o $@ $(LDDIR) $(LDMODULE) 
	ar rc libroute.a $@

clean : 
	rm -f *.o
	rm -f *.a
