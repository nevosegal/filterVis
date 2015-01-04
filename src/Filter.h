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

class Filter{
public:
    Filter();
    Filter(int x, int y, string type);
    
    void draw();
    double process(double sample);
    void setResValue(double value);
    void setCutOffValue(double value);
    bool isInBounds(int x, int y);
    
    int x,y,w,h;
    int resValue, resRange;
    int cutOffValue, cutOffRange;
    string type;
    maxiFilter fil;
};

#endif /* defined(__filterVis__Filter__) */
