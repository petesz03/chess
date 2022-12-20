#include <iostream>
#include <vector>
#include "posn.h"
#include "board.h"
#include <string>

int main(){
    Board* field = new Board{};
    std::string command;
    
    while (std::cin >> command){
        if (command == "move"){
            char piece;
            std::string og;
            std::string dest;
            std::cin >> piece >> og >> dest;
            field->movePiece(piece, og, dest);
        }
    }
}