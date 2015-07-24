OBJS = rtable.o dest.o rentry.o
LDDIR = -L../sha1
LDMODULE = -lsha1

all: $(OBJS)

$(OBJS) : %.o : %.cpp
	g++ -g -c $< -o $@ $(LDDIR) $(LDMODULE) 
	ar rc libroute.a $@

clean : 
	rm *.o
	rm *.a
