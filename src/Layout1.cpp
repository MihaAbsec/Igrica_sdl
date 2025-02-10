#include "include/Layout1.h"

#include <vector>

#include "include/Collision.h"
#include "include/Line.h"
#include "include/Player.h"


Layout1::Layout1(int width, int height)
    : SCREEN_WIDTH(width), SCREEN_HEIGHT(height),
      lines{ 
          Line(0, 0, 0, SCREEN_HEIGHT),                                    
          Line(SCREEN_WIDTH, 0, 0, SCREEN_HEIGHT),                         
          Line(0, 0, SCREEN_WIDTH, 0),                                     
          Line(0, SCREEN_HEIGHT, SCREEN_WIDTH, 0),                         
          Line((SCREEN_WIDTH + 300) / 2, (SCREEN_HEIGHT + 300) / 2, 50, 50),
          Line((SCREEN_WIDTH - 400) / 2, (SCREEN_HEIGHT) / 2, 1, 200),     
          Line((SCREEN_WIDTH - 400) / 2, (SCREEN_HEIGHT) / 2, 200, 1),    
          Line((SCREEN_WIDTH) / 2, (SCREEN_HEIGHT - 400) / 2, 1, 200)      
      } 
{}

