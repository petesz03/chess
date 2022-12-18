#include <iostream>
#include <vector>
#include "board.h"
#include "posn.h"

// Plan: Piece is an abstract class for all the different chess pieces
class Piece{

    protected:
    Board* board;
    Posn position;

    public:
    Piece(Board* board): board{board}{}
    ~Piece(){}
    Board* getBoard();
    void setBoard(Board* board);

    // When moving, checkLegal will be given the 
    virtual void move(Posn destination) = 0;

};