#include "include/Layout1.h"

#include <vector>

#include "include/Collision.h"
#include "include/Line.h"
#include "include/Player.h"

Layout1::Layout1(float width, float height)
	: lines{
		  Line(0, 0, 0, height),
		  Line(width, 0, 0, height),
		  Line(0, 0, width, 0),
		  Line(0, height, width, 0),
		  Line((width + 300) / 2, (height + 300) / 2, 50, 50),
		  Line((width - 400) / 2, (height) / 2, 1, 200),
		  Line((width - 400) / 2, (height) / 2, 200, 1),
		  Line((width) / 2, (height - 400) / 2, 1, 200)} {
}
