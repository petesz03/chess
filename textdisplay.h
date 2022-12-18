#include "board.h"

class TextDisplay{
    Board* subject;

    public:
    TextDisplay(Board* subject): subject{subject}{}

    void render();
};