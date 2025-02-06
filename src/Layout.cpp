#include "include/Layout.h"
#include <vector>
#include "include/Square.h"

#include "include/Line.h"
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

std::vector<Line> lines = {
	Line(0, 0, 0, SCREEN_HEIGHT),
	Line(SCREEN_WIDTH, 0, 0, SCREEN_HEIGHT),
	Line(0, 0, SCREEN_WIDTH, 0),
	Line(0, SCREEN_HEIGHT, SCREEN_WIDTH, 0),
	Line((SCREEN_WIDTH + 300) / 2, (SCREEN_HEIGHT + 300) / 2, 50, 50),
	Line((SCREEN_WIDTH - 400) / 2, (SCREEN_HEIGHT) / 2, 1, 200),
	Line((SCREEN_WIDTH - 400) / 2, (SCREEN_HEIGHT) / 2, 200, 1),
	Line((SCREEN_WIDTH) / 2, (SCREEN_HEIGHT - 400) / 2, 1, 200)};
void Layout::layout() {
    for(Line line : lines){
            square.update(line);
            line.render(renderer);
        }

}
