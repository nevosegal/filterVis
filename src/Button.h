//
//  Button.h
//  filterVis
//
//  Created by Nevo Segal on 04/01/2015.
//
//

#ifndef __filterVis__Button__
#define __filterVis__Button__

#include <stdio.h>
#include "ofMain.h"

class Button{
public:
    Button();
    Button(int x,int y, string type);
    
    void draw();
    bool isInBounds(int x, int y);
    void activate();
    void deactivate();
    bool isActivated();
    
    int x,y,w,h;
    bool active;
    string type;
};
#endif /* defined(__filterVis__Button__) */
