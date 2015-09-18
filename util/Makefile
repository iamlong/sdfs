LDDIR = -L../sha1
LDMODULE = -lsha1

utils.o: utils.cpp utils.h
	g++ $(LDDIR) $(LDMODULE) -g -c utils.cpp -o utils.o 
	ar rc libutils.a utils.o

clean : 
	rm -f *.o
	rm -f *.a
