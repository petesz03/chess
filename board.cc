#include "board.h"
#include <iostream>

void Board::setTextDisplay(TextDisplay* display){
    textdisplay = display;
}

/****** Attach and detach for pieces ******/
void Board::attach(Piece* piece){
    pieces.push_back(piece);
}

void Board::detach(Piece* piece){
    for (auto it = pieces.begin(); it != pieces.end(); it++){
        if ((*it).position == pieces) // *it is the ptr
        {
            delete (*it);
            *it == nullptr;
            pieces.erase(it);
        }
    }
}

// movePiece calls the move function for the respective Piece:
void Board::movePiece(Posn pieceAt, Posn pieceTo){
    if (!(pieceAt->valid()) || !(pieceTo->valid())){
        std::cout << "Invalid range" << std::cout;
        return;
    }
    for (auto it = pieces.begin(); it != pieces.end(); it++){
        if ((*it).position == pieceAt){ // Posn overloaded ==
            it->move(pieceTo);
        }
    }
}

// Returns the piece at pieceAt, if there is nothing there,
//   return nullptr:
Piece* Board::pieceAt(Posn pieceAt){
    for (auto it = pieces.begin(); it != pieces.end(); it++){
        if ((*it)->position == pieceAt){ // Posn overloaded ==
            return *it;
        }
        return nullptr;
    }
}