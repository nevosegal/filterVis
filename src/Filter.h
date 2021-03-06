//
//  Filter.h
//  filterVis
//
//  Created by Nevo Segal on 04/01/2015.
//
//

#ifndef __filterVis__Filter__
#define __filterVis__Filter__

#include <stdio.h>
#include "ofMain.h"
#include "ofxMaxim.h"
#include "Button.h"

class Filter{
public:
    
    //constructors
    Filter();
    Filter(int x, int y, string type);
    
    //class methods
    void draw();
    double process(double sample);
    void setResValue(double value);
    void setCutOffValue(double value);
    bool isInBounds(int x, int y);
    void activate();
    void deactivate();
    bool isActivated();
    
    //class variables
    int x,y,w,h;
    int resValue, resRange;
    int cutOffValue, cutOffRange;
    string type;
    maxiFilter fil;
    bool active;
    float circleX, circleY;
};

#endif /* defined(__filterVis__Filter__) */
