#include "include/Layout1.h"

#include <vector>

#include "include/Collision.h"
#include "include/Wall.h"
#include "include/Player.h"

Layout1::Layout1(float width, float height)
	: lines{
		  Wall(0, 0, 0, height),
		  Wall(width, 0, 0, height),
		  Wall(0, 0, width, 0),
		  Wall(0, height, width, 0),
		  Wall((width + 300) / 2, (height + 300) / 2, 50, 50),
		  Wall((width - 400) / 2, (height) / 2, 1, 200),
		  Wall((width - 400) / 2, (height) / 2, 200, 1),
		  Wall((width) / 2, (height - 400) / 2, 1, 200)} {
}
