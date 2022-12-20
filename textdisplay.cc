#include "board.h"
#include "textdisplay.h"
#include <iostream>
#include <vector>

void TextDisplay::render(){
    std::cout << " --------" << std::endl;
    for (int i = 1; i <= 8; i++){
        std::cout << i;
        for (int j = 1; j <= 8; j++){
            std::cout << board[i-1][j-1];
        }
        std::cout << std::endl;
    }
    std::cout << " --------" << std::endl;
}