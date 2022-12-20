#include "posn.h"

bool Posn::operator==(Posn posn){
        return (row == posn.row && col == posn.col);
}

bool Posn::valid(){
        return (row >= 0 && row <= 7 && col >= 0 && col <= 7);
}
