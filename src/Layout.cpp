#include "include/Layout.h"
#include <vector>
#include "include/Square.h"

#include "include/Line.h"
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

void Layout::layout() {
    for(Line line : lines){
            square.update(line);
            line.render(renderer);
        }

}
