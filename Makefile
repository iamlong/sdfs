# Project: sdfs
# Makefile created by Dev-C++ 5.11

CPP      = g++ -g
CC       = gcc -g
OBJ      = router/dest.o router/droute.o router/rentity.o router/rtable.o sha1/sha1.o util/utils.o fs/sinode.o fs/siblock.o fs/processlist.o fs/blocklist.o \
			util/serializer.o util/serialize.o util/network.o storage/trunk.o storage/storcmdq.o
LINKOBJ  = router/dest.o router/droute.o router/rentity.o router/rtable.o sha1/sha1.o util/utils.o fs/sinode.o fs/siblock.o fs/processlist.o fs/blocklist.o \
			util/serializer.o util/serialize.o util/network.o storage/trunk.o storage/storcmdq.o
LIBS     = 
INCS     =
CXXINCS  = 
BIN      = libsdfs.a
CXXFLAGS = $(CXXINCS) -std=c++11
CFLAGS   = $(INCS) -std=c++11
RM       = rm -f


.PHONY: all all-before all-after clean clean-custom

all: all-before $(BIN) all-after

clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(LINKOBJ)
	ar r $(BIN) $(LINKOBJ)
	ranlib $(BIN)

router/dest.o: router/dest.cpp router/dest.h
	$(CPP) -c router/dest.cpp -o router/dest.o $(CXXFLAGS)

router/droute.o: router/droute.cpp router/droute.h
	$(CPP) -c router/droute.cpp -o router/droute.o $(CXXFLAGS)

router/rentity.o: router/rentity.cpp router/rentity.h
	$(CPP) -c router/rentity.cpp -o router/rentity.o $(CXXFLAGS)

router/rtable.o: router/rtable.cpp router/rtable.h
	$(CPP) -c router/rtable.cpp -o router/rtable.o $(CXXFLAGS)

sha1/sha1.o: sha1/sha1.cpp sha1/sha1.h
	$(CPP) -c sha1/sha1.cpp -o sha1/sha1.o $(CXXFLAGS)

util/utils.o: util/utils.cpp util/utils.h
	$(CPP) -c util/utils.cpp -o util/utils.o $(CXXFLAGS)

fs/sinode.o: fs/sinode.cpp fs/sinode.h
	$(CPP) -c fs/sinode.cpp -o fs/sinode.o $(CXXFLAGS)

fs/processlist.o: fs/processlist.cpp fs/processlist.h
	$(CPP) -c fs/processlist.cpp -o fs/processlist.o $(CXXFLAGS)

fs/siblock.o: fs/siblock.cpp fs/siblock.h
	$(CPP) -c fs/siblock.cpp -o fs/siblock.o $(CXXFLAGS)

fs/blocklist.o: fs/blocklist.cpp fs/blocklist.h
	$(CPP) -c fs/blocklist.cpp -o fs/blocklist.o $(CXXFLAGS)


util/serializer.o: util/serializer.cpp util/serializer.h
	$(CPP) -c util/serializer.cpp -o util/serializer.o $(CXXFLAGS)

util/serialize.o: util/serialize.cpp util/serialize.h
	$(CPP) -c util/serialize.cpp -o util/serialize.o $(CXXFLAGS)

util/network.o: util/network.cpp util/network.h
	$(CPP) -c util/network.cpp -o util/network.o $(CXXFLAGS)

storage/trunk.o: storage/trunk.cpp storage/trunk.h
	$(CPP) -c storage/trunk.cpp -o storage/trunk.o $(CXXFLAGS)

storage/commandq.o: storage/storcmdq.cpp storage/storcmdq.h
	$(CPP) -c storage/storcmdq.cpp -o storage/storcmdq.o $(CXXFLAGS)
