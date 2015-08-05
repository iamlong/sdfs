# Project: sdfs
# Makefile created by Dev-C++ 5.11

CPP      = g++.exe
CC       = gcc.exe
OBJ      = router/dest.o router/droute.o router/rentity.o router/rtable.o sha1/sha1.o util/utils.o
LINKOBJ  = router/dest.o router/droute.o router/rentity.o router/rtable.o sha1/sha1.o util/utils.o
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
