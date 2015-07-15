OBJS = rentry.o
LDDIR = -L../sha1
LDMODULE = -lsha1

$(OBJS): %.o: %.cpp
	g++ -g -c $< -o $@ $(LDDIR) $(LDMODULE) 
	ar rc libroute.a $@

clean : 
	rm *.o
	rm *.a
