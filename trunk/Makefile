# Project: enigma

CPP  = g++
CC   = gcc
LIBS =
COMPFLAGS = -g
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
	$(CPP) $(COMPFLAGS) $(OBJ) -o $(BIN) $(LIBS)

$(WINBIN): $(OBJ)
	$(CPP) $(COMPFLAGS) $(OBJ) -o $(WINBIN) $(LIBS)

disk.o: disk.cpp disk.hpp layer.hpp global.hpp
	$(CPP) $(COMPFLAGS) -c disk.cpp -o disk.o

enigma.o: enigma.cpp enigma.hpp level.hpp trigger.hpp layer.hpp offsets.hpp switch.hpp stack.hpp shuffle.hpp disk.hpp flipdisk.hpp option.hpp global.hpp homebrew.hpp
	$(CPP) $(COMPFLAGS) -c enigma.cpp -o enigma.o

flipdisk.o: flipdisk.cpp flipdisk.hpp layer.hpp global.hpp
	$(CPP) $(COMPFLAGS) -c flipdisk.cpp -o flipdisk.o

global.o: global.cpp global.hpp
	$(CPP) $(COMPFLAGS) -c global.cpp -o global.o

homebrew.o: homebrew.cpp homebrew.hpp level.hpp trigger.hpp layer.hpp global.hpp
	$(CPP) $(COMPFLAGS) -c homebrew.cpp -o homebrew.o

layer.o: layer.cpp layer.hpp global.hpp
	$(CPP) $(COMPFLAGS) -c layer.cpp -o layer.o

level.o: level.cpp level.hpp trigger.hpp layer.hpp option.hpp global.hpp
	$(CPP) $(COMPFLAGS) -c level.cpp -o level.o

offsets.o: offsets.cpp offsets.hpp layer.hpp global.hpp
	$(CPP) $(COMPFLAGS) -c offsets.cpp -o offsets.o

option.o: option.cpp option.hpp global.hpp
	$(CPP) $(COMPFLAGS) -c option.cpp -o option.o

shuffle.o: shuffle.cpp shuffle.hpp layer.hpp global.hpp
	$(CPP) $(COMPFLAGS) -c shuffle.cpp -o shuffle.o

stack.o: stack.cpp stack.hpp layer.hpp global.hpp
	$(CPP) $(COMPFLAGS) -c stack.cpp -o stack.o

switch.o: switch.cpp switch.hpp layer.hpp global.hpp
	$(CPP) $(COMPFLAGS) -c switch.cpp -o switch.o

trigger.o: trigger.cpp trigger.hpp layer.hpp global.hpp
	$(CPP) $(COMPFLAGS) -c trigger.cpp -o trigger.o
