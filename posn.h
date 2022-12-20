#ifndef _POSN_
#define _POSN_
struct Posn{
    int x, y;

    Posn(int x, int y): x{x}, y{y} {}
    ~Posn(){}

    // == operator overload for comparison:

    bool operator==(Posn posn);
    bool valid();

};

#endif

