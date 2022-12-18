#include "posn.h"

bool Posn::operator==(Posn posn){
        return (row == posn.row && col = posn.col);
}

bool Posn::valid(){
        return (row >= 1 && row <= 8 && col >= 1 && col <= 8);
}