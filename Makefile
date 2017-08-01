CXX = g++
CXXFLAGS = -g -Wall -std=c++11
PATH = objects
DEPEND = piece.o king.o tile.o board.o
OBJ = $(PATH)/piece.o $(PATH)/king.o $(PATH)/tile.o $(PATH)/board.o

all: makeFolder checkers deleteDSYM

makeFolder:
	mkdir objects

checkers: Checkers.cpp $(DEPEND)
	$(CXX) $(CXXFLAGS) Checkers.cpp $(OBJ) -o Checkers

piece.o: Piece.cpp Piece.h
	$(CXX) $(CXXFLAGS) -c Piece.cpp -o $(PATH)/piece.o

king.o: King.cpp King.h
	$(CXX) $(CXXFLAGS) -c King.cpp -o $(PATH)/king.o

tile.o: Tile.cpp Tile.h
	$(CXX) $(CXXFLAGS) -c Tile.cpp -o $(PATH)/tile.o

board.o: Board.cpp Board.h
	$(CXX) $(CXXFLAGS) -c Board.cpp -o $(PATH)/board.o

deleteDSYM:
	rm -rf Checkers.dSYM

clean:
	rm -rf objects
	rm Checkers
