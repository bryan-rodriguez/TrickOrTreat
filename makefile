#bryan rodriguez : 1001647248
SRC1 = Code4_1001647248.cpp
SRC2 = TrickOrTreater.cpp
SRC3 = House.cpp
OBJ1 = $(SRC1:.cpp=.o)
OBJ2 = $(SRC2:.cpp=.o)
OBJ3 = $(SRC3:.cpp=.o)
EXE = $(SRC1:.cpp=.e)

HFLAGS = TrickOrTreater.h House.h

CFLAGS = -g -std=c++11 -pthread

all : $(EXE)
 
$(EXE): $(OBJ1) $(OBJ2) $(OBJ3)
	g++ $(CFLAGS) $(OBJ1) $(OBJ2) $(OBJ3) -o $(EXE) 

$(OBJ1) : $(SRC1) $(HFLAGS)
	g++ -c $(CFLAGS) $(SRC1) -o $(OBJ1) 

$(OBJ2) : $(SRC2) $(HFLAGS)
	g++ -c $(CFLAGS) $(SRC2) -o $(OBJ2) 

$(OBJ3) : $(SRC3) $(HFLAGS)
	g++ -c $(CFLAGS) $(SRC3) -o $(OBJ3) 