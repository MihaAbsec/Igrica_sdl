#ifndef LINE_H
#define LINE_H

#include <SDL2/SDL.h>
#include "GameObject.h"

class Line:public GameObject {

public:
  Line(float, float, int, int);
};

#endif
