# Project: enigma

CPP  = g++.exe
CC   = gcc.exe
LIBS =
COMPFLAGS =
START = disk.o flipdisk.o global.o homebrew.o layer.o level.o offsets.o option.o shuffle.o stack.o switch.o trigger.o
OBJ  = $(START) enigma.o
BIN  = enigma
WINBIN = enigma.exe
RM = rm -f

.PHONY: all clean start tidy exe

all: $(BIN)

exe: $(WINBIN)

start: $(START)

clean: 
	${RM} $(OBJ) $(BIN) $(WINBIN)

tidy:
	$(RM) $(OBJ)

$(BIN): $(OBJ)
	$(CPP) $(OBJ) -o $(BIN) $(LIBS)

$(WINBIN): $(OBJ)
	$(CPP) $(OBJ) -o $(WINBIN) $(LIBS)

disk.o: disk.cpp disk.hpp layer.hpp global.hpp
	$(CPP) -c disk.cpp -o disk.o $(COMPFLAGS)

enigma.o: enigma.cpp enigma.hpp level.hpp trigger.hpp layer.hpp offsets.hpp switch.hpp stack.hpp shuffle.hpp disk.hpp flipdisk.hpp option.hpp global.hpp homebrew.hpp
	$(CPP) -c enigma.cpp -o enigma.o $(COMPFLAGS)

flipdisk.o: flipdisk.cpp flipdisk.hpp layer.hpp global.hpp
	$(CPP) -c flipdisk.cpp -o flipdisk.o $(COMPFLAGS)

global.o: global.cpp global.hpp
	$(CPP) -c global.cpp -o global.o $(COMPFLAGS)

homebrew.o: homebrew.cpp homebrew.hpp level.hpp trigger.hpp layer.hpp global.hpp
	$(CPP) -c homebrew.cpp -o homebrew.o $(COMPFLAGS)

layer.o: layer.cpp layer.hpp global.hpp
	$(CPP) -c layer.cpp -o layer.o $(COMPFLAGS)

level.o: level.cpp level.hpp trigger.hpp layer.hpp option.hpp global.hpp
	$(CPP) -c level.cpp -o level.o $(COMPFLAGS)

offsets.o: offsets.cpp offsets.hpp layer.hpp global.hpp
	$(CPP) -c offsets.cpp -o offsets.o $(COMPFLAGS)

option.o: option.cpp option.hpp global.hpp
	$(CPP) -c option.cpp -o option.o $(COMPFLAGS)

shuffle.o: shuffle.cpp shuffle.hpp layer.hpp global.hpp
	$(CPP) -c shuffle.cpp -o shuffle.o $(COMPFLAGS)

stack.o: stack.cpp stack.hpp layer.hpp global.hpp
	$(CPP) -c stack.cpp -o stack.o $(COMPFLAGS)

switch.o: switch.cpp switch.hpp layer.hpp global.hpp
	$(CPP) -c switch.cpp -o switch.o $(COMPFLAGS)

trigger.o: trigger.cpp trigger.hpp layer.hpp global.hpp
	$(CPP) -c trigger.cpp -o trigger.o $(COMPFLAGS)
