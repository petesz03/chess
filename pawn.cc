#include "posn.h"
#include "board.h"
#include "piece.h"
#include "pawn.h"

void Pawn::move(Posn destination){
    Posn temp{position.row, position.col};
    Board* opponent = board->getOpponent();

    // Check if trying to move forward by 1:
    (temp.x)++;
    if (destination == temp){
        // If there are mine OR opponent's piece there, cannot move!!!
        if (opponent->pieceAt(temp) != nullptr){ return; }
        if (board->pieceAt(temp) != nullptr){ return; }
        position = destination;
    }

    // Check if trying to take diagonally:
    (temp.y)++;
    if (destination == temp){
        // If there are opponent's piece there, move is legal, remove the
        //   taken piece from opponent's "Pieces":
        Piece* opponentPiece = (opponent->pieceAt(temp));
        // Cannot move if there is no piece there:
        if (opponentPiece == nullptr){ return; }
        // Move + Take:
        opponent->detach(opponentPiece);
        position == destination;
    }
}