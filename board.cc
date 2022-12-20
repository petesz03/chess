#include "board.h"
#include "piece.h"

#include <iostream>
#include <string>

Board::Board(){
    // Note that the top of the board is the white piece and
    //   the bottom is the white piece to facilitate 1 - 8 
    //   increments. 

    // White := UPPER CASE, Black := LOWER CASE

    board.emplace_back(R, N, B, K, Q, B, N, R); // Row 1
    board.emplace_back(P, P, P, P, P, P, P, P); // Row 2
    for (int r = 2; r <= 5; r++) {
        board.emplace_back(EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY, EMPTY);
    }
    board.emplace_back(p, p, p, p, p, p, p, p); // Row 7
    board.emplace_back(r, n, b, k, q, b, n, r); // Row 8
}

// will need a second Board() ctor given a board and a move or smth


// Converts a chessboard location to a 
//   vector coordinates:
Posn Board::convertToVec(std::string command){
    int row = command[1] - '1';
    char col;
    if (isupper(command[0])){
        col = command[0] - 'A';
    } else{
        col = command[0] - 'a';
    }
    
    Posn temp = {row, col};
    return temp;
}

void Board::placePiece(char piece, Posn position){
    int row = position.row;
    int col = position.col;
    board[row][col] = piece;
}

char Board::locate(Posn position){
    int row = position.row;
    int col = position.col;
    return board[row][col];
}

// Not very efficient:
bool Board::dangerCheck(char piece, Posn loc){
    if (islower(piece)){
        for (int row = 0; row <= 7; row++){
            for (int col = 0; col <= 7; col++){
                if (isupper(board[row][col])){
                    Posn temp = {row, col};
                    if (isLegal(board[row][col], temp, loc)){ return true; }
                }
            }
        }
    }
    else{
        for (int row = 0; row <= 7; row++){
            for (int col = 0; col <= 7; col++){
                if (islower(board[row][col])){
                    Posn temp = {row, col};
                    if (isLegal(board[row][col], temp, loc)){ return true; }
                }
            }
        }
    }
    return false;

}
// Can only enter w or W:
bool Board::kingInDanger(char piece){
    if (islower(piece)){
        Posn temp = {-1,-1};
        for (int row = 0; row <= 7; row++){
            for (int col = 0; col <= 7; col++){
                if (board[row][col] == 'w'){ temp = {row, col};}
            }
        }
        if (temp.row == -1 && temp.col == -1){
            std::cout << "Bad checking" << std::endl;
            return false;
        }
        else{
            return (dangerCheck('w',temp));
        }
    }
    else if (isupper(piece)){
        Posn temp = {-1,-1};
        for (int row = 0; row <= 7; row++){
            for (int col = 0; col <= 7; col++){
                if (board[row][col] == 'W'){ temp = {row, col};}
            }
        }
        if (temp.row == -1 && temp.col == -1){
            std::cout << "Bad checking" << std::endl;
            return false;
        }
        else{
            return (dangerCheck('W',temp));
        }
    }
    return false;
}
void Board::movePiece(char piece, std::string ogLocation, std::string destination){
    Posn start = convertToVec(ogLocation);
    Posn dest = convertToVec(destination);
    char og = locate(start);
    char de = locate(dest);

    if (isLegal(piece, start, dest)){
        placePiece(' ', start);
        placePiece(piece, dest);
    }
    else{
        std::cout << "That is not a legal move!" << std::endl;
    }
    // Check if the king is still in check after the move:
    if (islower(piece) && kingInDanger('w')){
        // Undo changes:
        placePiece(og, start);
        placePiece(de, dest);
        std::cout << "Your King will be taken!" << std::endl;
    }
    else if (isupper(piece) && kingInDanger('W')){
        // Undo changes:
        placePiece(og, start);
        placePiece(de, dest);
        std::cout << "Your King is still in check!" << std::endl;
    }
    return;
};

bool Board::isLegal(char piece, Posn start, Posn dest){
    
    // Constants for efficiency:
    int startRow = start.row;
    int startCol = start.col;
    int destRow = dest.row;
    int destCol = dest.col;
    // Error checking first:
    if (piece != locate(start)){ return false;}
    else if (start == dest){ return false; }
    else if (!start.valid() || !dest.valid()){ return false; }

    // Move according to piece:
    /********** Pawn **********/
    if (piece == 'p'){
        // Moving vertically:
        Posn temp = {startRow - 1, startCol};
        if (dest == temp && locate(temp) == ' '){ return true; }
	    temp = {startRow - 2, startCol};
	    if (temp.row == 4 && dest == temp && locate(temp) == ' '){ return true; }

        // Taking, and moving diagonally:
        temp = {startRow - 1, startCol + 1};
        if (dest == temp && isupper(locate(temp))){ return true; }
        temp = {startRow - 1, startCol - 1};
        if (temp.row == 4 && dest == temp && isupper(locate(temp))){ return true; }
        else{ return false; }
    }
    else if (piece == 'P'){
        Posn temp = {startRow + 1, startCol};
        if (dest == temp && locate(temp) == ' '){ return true; }
	    temp = {startRow + 2, startCol};
        if (temp.row == 3 && dest == temp && locate(temp) == ' '){ return true; }

        // Taking, and moving diagonally:
        temp = {startRow + 1, startCol + 1};
        // Checking if there is an opponent's piece at temp:
        if (dest == temp && islower(locate(temp))){ return true;}

        temp = {startRow + 1, startCol - 1};
        // Checking if there is an opponent's piece at temp:
        if (dest == temp && islower(locate(temp))){ return true; }
        else{ return false; }
    }
    /********* ROOK ***********/
    else if (piece == 'r' || piece == 'R'){

        // The two locations are not on the same line, return:
        if (destRow != startRow && destCol != startCol){ return false; }

        if (startCol > destCol){
            for (int i = destCol + 1; i < startCol; i++){
                if (board[startRow][i] != ' '){ return false; }
            }
        }
        else if (startCol < destCol){
            for (int i = startCol + 1; i < destCol; i++){
                if (board[startRow][i] != ' '){ return false; }
            }
        }
        else if (startRow > destRow){
            for (int i = destCol + 1; i < startCol; i++){
                if (board[i][startCol] != ' '){ return false; }

            }
        }
        else if (startRow < destRow){
            for (int i = startRow + 1; i < destRow; i++){
                if (board[i][startCol] != ' '){ return false; }
            }
        }
        // Take or there is your own piece there?
        char curr = locate(dest);
        if (piece == 'r' && islower(curr)){ return false; }
        else if (piece == 'R' && isupper(curr)){ return false; }
        else{ return true; }
    }

    /********** Bishop *********/
    else if (piece == 'b' || piece == 'B'){
        // Check if start and dest is on the same diagonal:
        if (abs(startRow - destRow) != abs(startCol - destCol)){ return false; }
        int numMovesX = startRow - destRow;
        int numMovesY = startCol - destCol;
        if (numMovesX > 0 && numMovesY > 0){
            for (int i = 1; i < abs(numMovesX); i++){
                if (board[startRow - i][startCol - i] != ' '){ return false; }
            }
        }
        if (numMovesX < 0 && numMovesY > 0){
            for (int i = 1; i < abs(numMovesX); i++){
                if (board[startRow + i][startCol - i] != ' '){ return false; }
            }
        }
        if (numMovesX > 0 && numMovesY < 0){
            
            for (int i = 1; i < abs(numMovesX); i++){
                if (board[startRow - i][startCol + i] != ' '){ return false; }
            }
        }
        if (numMovesX < 0 && numMovesY < 0){
            for (int i = 1; i < abs(numMovesX); i++){
                if (board[startRow + i][startCol + i] != ' '){ return false; }
            }
        }

        // Take or there is your own piece there?
        char curr = locate(dest);
        if (piece == 'b' && islower(curr)){ return false; }
        else if (piece == 'B' && isupper(curr)){ return false; }
        else{ return true; }
    }

    /******** Knight ********/
    else if (piece == 'K' || piece == 'k'){
        // For Knight to be a valid move, either one of the following must occur:
        // 1. X value moves by 2 and Y value moves by 1
        // 2. X value moves by 1 and Y value moves by 2

        int numMovesX = startRow - destRow;
        int numMovesY = startCol - destCol;

        if (abs(numMovesX) == 1 && abs(numMovesY) == 2){}
        else if (abs(numMovesX) == 2 && abs(numMovesY) == 1){}
        else{ return false; }

        // Knight do not have to check if there are anything along the way:
        // Take or there is your own piece there:
        char curr = locate(dest);
        if (piece == 'k' && islower(curr)){ return false; }
        else if (piece == 'K' && isupper(curr)){ return false; }
        else{ return true; }
    }

    /********* Queen *********/
    else if (piece == 'Q' || piece == 'q'){
        int numMovesX = startRow - destRow;
        int numMovesY = startCol - destCol;
        // Moving horizontally:
        if (numMovesX == 0 || numMovesY == 0){
            if (startCol > destCol){
                for (int i = destCol; i < startCol; i++){
                    if (board[startRow][i] != ' '){ return false; }
                }
            }
            else if (startCol < destCol){
                for (int i = startCol + 1; i < destCol; i++){
                    if (board[startRow][i] != ' '){ return false; }
                }
            }
            else if (startRow > destRow){
                for (int i = destCol + 1; i < startRow; i++){
                    if (board[i][startCol] != ' '){ return false; }
                }
            }
            else if (startRow < destRow){
                for (int i = startCol + 1; i < destRow; i++){
                    if (board[i][startCol] != ' '){ return false; }
                }
            }
            // Take or there is your own piece there?
            char curr = locate(dest);
            if (piece == 'q' && islower(curr)){ return false; }
            else if (piece == 'Q' && isupper(curr)){ return false; }
            else{ return true; }
        }
        else if (abs(startRow - destRow) != abs(startCol - destCol)){
            if (numMovesX > 0 && numMovesY > 0){
                for (int i = 1; i < abs(numMovesX); i++){
                    if (board[startRow - i][startCol - i] != ' '){ return false; }
                }
            }
            if (numMovesX < 0 && numMovesY > 0){
                for (int i = 1; i < abs(numMovesX); i++){
                    if (board[startRow + i][startCol - i] != ' '){ return false; }
                }
            }
            if (numMovesX > 0 && numMovesY < 0){
                for (int i = 1; i < abs(numMovesX); i++){
                    if (board[startRow - i][startCol + i] != ' '){ return false; }
                }
            }
            if (numMovesX < 0 && numMovesY < 0){
                for (int i = 1; i < abs(numMovesX); i++){
                    if (board[startRow + i][startCol + i] != ' '){ return false; }
                }
            }

            // Take or there is your own piece there?
            char curr = locate(dest);
            if (piece == 'q' && islower(curr)){ return false; }
            else if (piece == 'Q' && isupper(curr)){ return false; }
            else{ return true; }
        }
        else{ return false; }
    }
    
    /******** King **********/
    else if (piece == 'W' || piece == 'w'){
        // For the move to be valid for king, the difference
        //   between the x and the y value can only be 1:
        int numMovesX = startRow - destRow;
        int numMovesY = startCol - destCol;

        if (abs(numMovesX) != 1 && abs(numMovesY) != 1){
            return false;
        }
        // Knight do not have to check if there are anything along the way:
        // Take or there is your own piece there?
        char curr = locate(dest);
        if (piece == 'w' && islower(curr)){
            return false;
        }
        else if (piece == 'W' && isupper(curr)){
            return false;
        }
        else{ return true; } 
    }
    else{ return false; }
}

/*
void Board::setTextDisplay(TextDisplay* display){
    textdisplay = display;
}

****** Attach and detach for pieces *****
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

*/
