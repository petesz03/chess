#include "board.h"
#include <iostream>
#include <string>

Board::Board(){
    // Note that the top of the board is the white piece and
    //   the bottom is the white piece to facilitate 1 - 8 
    //   increments. 

    // Note that capital letters are whites piece
    // Lower letters are black pieces:
    // Note that W and w are Kings 

    // Row 1:
    std::vector<char> temp = {'R','K','B','W','Q','B','K','R'};
    board.push_back(temp);
    // Row 2:
    std::vector<char> temp2 = {'P','P','P','P','P','P','P','P'};
    board.push_back(temp2);
    for (int i = 0; i <= 3; i++){
        std::vector<char> temporary;
        for (int j = 0; j <= 7; j++){
            char tempChar = ' ';
            temporary.push_back(tempChar);
        }
        board.push_back(temporary);
    }
    // Row 7:
    std::vector<char> temp3 = {'p','p','p','p','p','p','p','p'};
    board.push_back(temp3);
    // Row 8:
    std::vector<char> temp4 = {'r','k','b','w','q','r','k','r'};
    board.push_back(temp4);
}

// Converts a chessboard location to a 
//   vector coordinates:
Posn Board::convertToVec(std::string command){
    int row = command[1] - '1';
    char col = command[0];

    Posn temp = {row, col - 'a'};
    return temp;
}

void Board::placePiece(char piece, Posn position){
    int x = position.x;
    int y = position.y;
    board[x][y] = piece;
}

char Board::locate(Posn position){
    int x = position.x;
    int y = position.y;
    return board[x][y];
}
void Board::movePiece(char piece, std::string ogLocation, std::string destination){
    // Logic:
    // If there are multiple of the same type of piece that can
    //   move there, ask the user to indicate which one it wants
    //   to move:
    Posn start = convertToVec(ogLocation);
    Posn dest = convertToVec(destination);
    // Error checking first:
    if (piece != locate(start)){
        std::cout << "That piece is not there!" << std::endl;
        return;
    }
    else if (start == dest){
        std::cout << "You are not moving any pieces!" << std::endl;
        return;
    }
    else if (!start.valid() || !dest.valid()){
        std::cout << "Those are not valid positions";
        return;
    }

    // Move according to piece:
    /********** Pawn **********/
    if (piece == 'p'){
        // Moving vertically:
        Posn temp = {start.x - 1, start.y};
        if (dest == temp && locate(temp) == ' '){
            placePiece(' ', start);
            placePiece('p', dest);
            return;
        }
	temp = {start.x - 2, start.y};
	if (dest == temp && locate(temp) == ' '){
            placePiece(' ', start);
            placePiece('p', dest);
            return;
        }
        // Taking, and moving diagonally:
        temp = {start.x - 1, start.y + 1};
        if (dest == temp && isupper(locate(temp))){
            // Checking if there is an opponent's piece at temp:
            placePiece(' ', start);
            placePiece('p', dest);
            return;
        }
        temp = {start.x - 1, start.y - 1};
        if (temp.x == 5 && dest == temp && isupper(locate(temp))){
            // Checking if there is an opponent's piece at temp:
            placePiece(' ', start);
            placePiece('p', dest);
            return;
        }
        else{
            std::cout << "That is an invalid move for Pawn" << std::endl;
            return;
        }
    }
    else if (piece == 'P'){
        Posn temp = {start.x + 1, start.y};
        if (dest == temp && locate(temp) == ' '){
            placePiece(' ', start);
            placePiece('P', dest);
            return;
        }
	temp = {start.x + 2, start.y};
        if (temp.x == 4 && dest == temp && locate(temp) == ' '){
            placePiece(' ', start);
            placePiece('P', dest);
            return;
        }
        // Taking, and moving diagonally:
        temp = {start.x + 1, start.y + 1};
        // Checking if there is an opponent's piece at temp:
        if (dest == temp && islower(locate(temp))){
            placePiece(' ', start);
            placePiece('P', dest);
            return;
        }
        temp = {start.x + 1, start.y - 1};
        // Checking if there is an opponent's piece at temp:
        if (dest == temp && islower(locate(temp))){
            placePiece(' ', start);
            placePiece('P', dest);
            return;
        }
        else{
            std::cout << "That is an invalid move for Pawn" << std::endl;
            return;
        }
    }
    /********* ROOK ***********/
    else if (piece == 'r' || piece == 'R'){

        // The two locations are not on the same line, return:
        if (dest.x != start.x && dest.y != start.y){
            std::cout << "That is an invalid move for Rook" << std::endl;
            return;
        }

        if (start.y > dest.y){
            for (int i = dest.y + 1; i < start.y; i++){
                if (board[start.x][i] != ' '){
                    std::cout << "There are pieces along the way" << std::endl;
                    return;
                }
            }
        }
        else if (start.y < dest.y){
            for (int i = start.y + 1; i < dest.y; i++){
                if (board[start.x][i] != ' '){
                    std::cout << "There are pieces along the way" << std::endl;
                    return;
                }
            }
        }
        else if (start.x > dest.x){
            for (int i = dest.y + 1; i < start.x; i++){
                if (board[i][start.y] != ' '){
                    std::cout << "There are pieces along the way" << std::endl;
                    return;
                }
            }
        }
        else if (start.x < dest.x){
            for (int i = start.y + 1; i < dest.x; i++){
                if (board[i][start.y] != ' '){
                    std::cout << "There are pieces along the way" << std::endl;
                    return;
                }
            }
        }
        // Take or there is your own piece there?
        char curr = locate(dest);
        if (piece == 'r' && islower(curr)){
            std::cout << "Cannot move there, your own piece is there!" << std::endl;
            return;
        }
        else if (piece == 'R' && isupper(curr)){
            std::cout << "Cannot move there, your own piece is there!" << std::endl;
        }
        else{
            placePiece(' ', start);
            placePiece(piece, dest);
        }
    }

    /********** Bishop *********/
    else if (piece == 'b' || piece == 'B'){
        // Check if start and dest is on the same diagonal:
        if (start.x - dest.x != start.y - dest.y){
            std::cout << "That is not a valid move for Bishop!" << std::endl;
            return;
        }

        int numMovesX = start.x - dest.x;
        int numMovesY = start.y - dest.y;
        if (numMovesX > 0 && numMovesY > 0){
            for (int i = 1; i < abs(numMovesX); i++){
                if (board[dest.x + i][dest.y + i] != ' '){
                    std::cout << "There are pieces along the way!" << std::endl;
                    return;
                }
            }
        }
        if (numMovesX < 0 && numMovesY > 0){
            for (int i = 1; i < abs(numMovesX); i++){
                if (board[start.x + i][dest.y + i] != ' '){
                    std::cout << "There are pieces along the way!" << std::endl;
                    return;
                }
            }
        }
        if (numMovesX > 0 && numMovesY < 0){
            for (int i = 1; i < abs(numMovesX); i++){
                if (board[dest.x + i][start.y + i] != ' '){
                    std::cout << "There are pieces along the way!" << std::endl;
                    return;
                }
            }
        }
        if (numMovesX < 0 && numMovesY < 0){
            for (int i = 1; i < abs(numMovesX); i++){
                if (board[start.x + i][start.y + i] != ' '){
                    std::cout << "There are pieces along the way!" << std::endl;
                    return;
                }
            }
        }

        // Take or there is your own piece there?
        char curr = locate(dest);
        if (piece == 'b' && islower(curr)){
            std::cout << "Cannot move there, your own piece is there!" << std::endl;
            return;
        }
        else if (piece == 'B' && isupper(curr)){
            std::cout << "Cannot move there, your own piece is there!" << std::endl;
        }
        else{
            placePiece(' ', start);
            placePiece(piece, dest);
        }
    }

    /******** Knight ********/
    else if (piece == 'K' || piece == 'k'){
        // For Knight to be a valid move, either one of the following must occur:
        // 1. X value moves by 2 and Y value moves by 1
        // 2. X value moves by 1 and Y value moves by 2

        int numMovesX = start.x - dest.x;
        int numMovesY = start.y - dest.y;

        if (abs(numMovesX) == 1 && abs(numMovesY) == 2){}
        else if (abs(numMovesX) == 2 && abs(numMovesY) == 1){}
        else{
            std::cout << "That is not a valid move for Knight!" << std::endl;
            return;
        }
        // Knight do not have to check if there are anything along the way:
        // Take or there is your own piece there?
        char curr = locate(dest);
        if (piece == 'k' && islower(curr)){
            std::cout << "Cannot move there, your own piece is there!" << std::endl;
            return;
        }
        else if (piece == 'K' && isupper(curr)){
            std::cout << "Cannot move there, your own piece is there!" << std::endl;
        }
        else{
            placePiece(' ', start);
            placePiece(piece, dest);
        }
    }

    /********* Queen *********/
    else if (piece == 'Q' || piece == 'q'){
        int numMovesX = start.x - dest.x;
        int numMovesY = start.y - dest.y;
        // Moving horizontally:
        if (numMovesX == 0 || numMovesY == 0){
            if (start.y > dest.y){
                for (int i = dest.y; i < start.y; i++){
                    if (board[start.x][i] != ' '){
                        std::cout << "There are pieces along the way" << std::endl;
                        return;
                    }
                }
            }
            else if (start.y < dest.y){
                for (int i = start.y + 1; i < dest.y; i++){
                    if (board[start.x][i] != ' '){
                        std::cout << "There are pieces along the way" << std::endl;
                        return;
                    }
                }
            }
            else if (start.x > dest.x){
                for (int i = dest.y + 1; i < start.x; i++){
                    if (board[i][start.y] != ' '){
                        std::cout << "There are pieces along the way" << std::endl;
                        return;
                    }
                }
            }
            else if (start.x < dest.x){
                for (int i = start.y + 1; i < dest.x; i++){
                    if (board[i][start.y] != ' '){
                        std::cout << "There are pieces along the way" << std::endl;
                        return;
                    }
                }
            }
            // Take or there is your own piece there?
            char curr = locate(dest);
            if (piece == 'q' && islower(curr)){
                std::cout << "Cannot move there, your own piece is there!" << std::endl;
                return;
            }
            else if (piece == 'Q' && isupper(curr)){
                std::cout << "Cannot move there, your own piece is there!" << std::endl;
            }
            else{
                placePiece(' ', start);
                placePiece(piece, dest);
            }
        }
        else if (numMovesX == numMovesY){
            if (numMovesX > 0 && numMovesY > 0){
                for (int i = 1; i < abs(numMovesX); i++){
                    if (board[dest.x + i][dest.y + i] != ' '){
                        std::cout << "There are pieces along the way!" << std::endl;
                        return;
                    }
                }
            }
            if (numMovesX < 0 && numMovesY > 0){
                for (int i = 1; i < abs(numMovesX); i++){
                    if (board[start.x + i][dest.y + i] != ' '){
                        std::cout << "There are pieces along the way!" << std::endl;
                        return;
                    }
                }
            }
            if (numMovesX > 0 && numMovesY < 0){
                for (int i = 1; i < abs(numMovesX); i++){
                    if (board[dest.x + i][start.y + i] != ' '){
                        std::cout << "There are pieces along the way!" << std::endl;
                        return;
                    }
                }
            }
            if (numMovesX < 0 && numMovesY < 0){
                for (int i = 1; i < abs(numMovesX); i++){
                    if (board[start.x + i][start.y + i] != ' '){
                        std::cout << "There are pieces along the way!" << std::endl;
                        return;
                    }
                }
            }

            // Take or there is your own piece there?
            char curr = locate(dest);
            if (piece == 'q' && islower(curr)){
                std::cout << "Cannot move there, your own piece is there!" << std::endl;
                return;
            }
            else if (piece == 'Q' && isupper(curr)){
                std::cout << "Cannot move there, your own piece is there!" << std::endl;
            }
            else{
                placePiece(' ', start);
                placePiece(piece, dest);
            }
        }\
        else{
            std::cout << "That is not a valid move for Queen" << std::endl;
        }
        
    }
    
    /******** King **********/
    else if (piece == 'W' || piece == 'w'){
        // For the move to be valid for king, the difference
        //   between the x and the y value can only be 1:
        int numMovesX = start.x - dest.x;
        int numMovesY = start.y - dest.y;

        if (abs(numMovesX) != 1 && abs(numMovesY) != 1){
            std::cout << "That is not a valid move for Knight!" << std::endl;
            return;
        }
        // Knight do not have to check if there are anything along the way:
        // Take or there is your own piece there?
        char curr = locate(dest);
        if (piece == 'w' && islower(curr)){
            std::cout << "Cannot move there, your own piece is there!" << std::endl;
            return;
        }
        else if (piece == 'W' && isupper(curr)){
            std::cout << "Cannot move there, your own piece is there!" << std::endl;
        }
        else{
            placePiece(' ', start);
            placePiece(piece, dest);
        }     
    }
    
};

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
