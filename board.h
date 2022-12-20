#ifndef _BOARD_
#define _BOARD_

#include <vector>
#include "posn.h"
#include <string>

class TextDisplay;

class Board{
    
    public:
    std::vector<std::vector<char>> board;

    Board();
    // Everything is stack allocated:
    ~Board(){}

    // Converts a chessboard location to a 
    //   vector coordinates:
    Posn convertToVec(std::string command);

    void movePiece(char piece, std::string ogLocation, std::string destination);
    void placePiece(char piece, Posn position);
    char locate(Posn position);
    bool ownPiece();


};

#endif
