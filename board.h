#include <vector>
#include "posn.h"
#include <string>

class TextDisplay;

class Board{

    std::vector<std::vector<char>> board;
    public:

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
