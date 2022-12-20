#include <iostream>
#include <vector>
#include "posn.h"
#include "board.h"
#include <string>
#include "textdisplay.h"

int main(){
    Board* field = new Board{};
    std::string command;
    TextDisplay* textdisplay = new TextDisplay{field}; 
    textdisplay->render();
    while (std::cin >> command){
        if (command == "move"){
            char piece;
            std::string og;
            std::string dest;
            std::cin >> piece >> og >> dest;
            field->movePiece(piece, og, dest);
            textdisplay->render();
        }
    }
}