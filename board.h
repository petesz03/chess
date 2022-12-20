#ifndef _BOARD_
#define _BOARD_

#include <vector>
#include "posn.h"
#include <string>

class TextDisplay;

class Board{
  public:
    // toMove = true for White, false for Black
    bool toMove, whiteCastle, blackCastle;
    size_t draw50; // counter for 50 move draw
    std::vector<std::vector<char>> board;

    Board();
    // Everything is stack allocated:
    ~Board(){}

    // Converts a chessboard location to a 
    //   vector coordinates:
    Posn convertToVec(std::string command);

    void movePiece(char piece, std::string ogLocation, std::string destination);
    bool isLegal(char piece, Posn start, Posn dest);
    // Check if a piece can be taken by any other piece:
    bool dangerCheck(char piece, Posn loc);
    bool kingInDanger(char piece);

    void placePiece(char piece, Posn position);
    char locate(Posn position);
    bool ownPiece();


};

#endif
