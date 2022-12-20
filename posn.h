#ifndef _POSN_
#define _POSN_
struct Posn{
    int row, col;

    Posn(int row, int col): row{row}, col{col} {}
    ~Posn(){}

    // == operator overload for comparison:

    bool operator==(Posn posn);
    bool valid();

};

#endif

