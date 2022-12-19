#include "posn.h"

bool Posn::operator==(Posn posn){
        return (x == posn.x && y = posn.y);
}

bool Posn::valid(){
        return (row >= 0 && row <= 7 && col >= 0 && col <= 7);
}
