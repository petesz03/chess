#include "posn.h"

bool Posn::operator==(Posn posn){
        return (x == posn.x && y == posn.y);
}

bool Posn::valid(){
        return (x >= 0 && x <= 7 && y >= 0 && y <= 7);
}
