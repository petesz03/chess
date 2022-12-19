#include "board.h"
#include "piece.h"

Board* Piece::getBoard(){
    return board;
}

void Piece::setBoard(Board* board){
    this->board = board;
}

