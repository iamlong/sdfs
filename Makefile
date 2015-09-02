# Project: sdfs
# Makefile created by Dev-C++ 5.11

CPP      = g++.exe -g
CC       = gcc.exe -g
OBJ      = router/dest.o router/droute.o router/rentity.o router/rtable.o sha1/sha1.o util/utils.o fs/sinode.o fs/siblock.o fs/processlist.o fs/blocklist.o util/serializer.o util/serialize.o
LINKOBJ  = router/dest.o router/droute.o router/rentity.o router/rtable.o sha1/sha1.o util/utils.o fs/sinode.o fs/siblock.o fs/processlist.o fs/blocklist.o util/serializer.o util/serialize.o
LIBS     = 
INCS     =
CXXINCS  = 
BIN      = libsdfs.a
CXXFLAGS = $(CXXINCS) 
CFLAGS   = $(INCS) 
RM       = rm.exe -f


.PHONY: all all-before all-after clean clean-custom

all: all-before $(BIN) all-after

clean: clean-custom
	${RM} $(OBJ) $(BIN)

$(BIN): $(LINKOBJ)
	ar r $(BIN) $(LINKOBJ)
	ranlib $(BIN)

router/dest.o: router/dest.cpp
	$(CPP) -c router/dest.cpp -o router/dest.o $(CXXFLAGS)

router/droute.o: router/droute.cpp
	$(CPP) -c router/droute.cpp -o router/droute.o $(CXXFLAGS)

router/rentity.o: router/rentity.cpp
	$(CPP) -c router/rentity.cpp -o router/rentity.o $(CXXFLAGS)

router/rtable.o: router/rtable.cpp
	$(CPP) -c router/rtable.cpp -o router/rtable.o $(CXXFLAGS)

sha1/sha1.o: sha1/sha1.cpp
	$(CPP) -c sha1/sha1.cpp -o sha1/sha1.o $(CXXFLAGS)

util/utils.o: util/utils.cpp
	$(CPP) -c util/utils.cpp -o util/utils.o $(CXXFLAGS)

fs/sinode.o: fs/sinode.cpp
	$(CPP) -c fs/sinode.cpp -o fs/sinode.o $(CXXFLAGS)

fs/processlist.o: fs/processlist.cpp
	$(CPP) -c fs/processlist.cpp -o fs/processlist.o $(CXXFLAGS)

fs/siblock.o: fs/siblock.cpp
	$(CPP) -c fs/siblock.cpp -o fs/siblock.o $(CXXFLAGS)

fs/blocklist.o: fs/blocklist.cpp
	$(CPP) -c fs/blocklist.cpp -o fs/blocklist.o $(CXXFLAGS)


util/serializer.o: util/serializer.cpp
	$(CPP) -c util/serializer.cpp -o util/serializer.o $(CXXFLAGS)

util/serialize.o: util/serialize.cpp
	$(CPP) -c util/serialize.cpp -o util/serialize.o $(CXXFLAGS)


