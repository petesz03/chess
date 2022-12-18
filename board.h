#include "piece.h"
#include <vector>
#include "posn.h"

class TextDisplay;

class Board{

    std::vector<Piece* > pieces;
    TextDisplay* textdisplay;
    // Opponent is needed for checking legal move purposes
    //   i.e. Pawns can only move diagonally when taking:
    Board* opponent;

    public:
    Board(Board* opponent): opponentBoard{opponent} {}
    ~Board(){
        for (auto it = pieces.begin(); it != pieces.end(); it++){
            delete *it; 
            // *it is the pointer to the piece since it will first dereference it.
            *it = nullptr;
        }
        delete textdisplay;
    }

    void setTextDisplay(TextDisplay* display);

    void getOpponent();
    void setOpponent(Board* op);

    // Attaches and detaches the piece onto the vector pieces in Board:
    void attach(Piece* piece);
    void detach(Piece* piece);

    // movePiece should search through "pieces" and look for the correct Piece to move,
    //   then it will call the move function for that specific piece,
    //   Must also check if either posn is outside of the bounds:
    void movePiece(Posn pieceAt, Posn pieceTo);
    Piece* pieceAt(Posn pieceAt);

};