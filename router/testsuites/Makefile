INCDIR = -I../../include
LDDIR = -L../ -L../../external -L../../sha1
LDMOULE = -lroute -lgtest -lsha1

OBJS = testrentry.o

$(OBJS): %.o: %.cpp
	g++ -g $< -o $@ $(INCDIR) $(LDDIR) $(LDMOULE)
	#./$@

clean : 
	rm *.o
