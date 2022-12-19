#include "board.h"
#include "piece.h"
#include "posn.h"

class Pawn: public Piece{
    
    public:
    void move(Posn destination) override;
};