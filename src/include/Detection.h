#ifndef DETECTION_H
#define DETECTION_H

#include <SDL2/SDL.h>
#include "Line.h"
#include "Square.h"

class Detection:public Line, public Square{
public:
    void contact(Square, Line);
};

#endif

