//
//  Filter.cpp
//  filterVis
//
//  Created by Nevo Segal on 04/01/2015.
//
//

#include "Filter.h"

Filter::Filter(){
    
}

Filter::Filter(int x, int y, string type){
    this->x = x;
    this->y = y;
    this->type = type;
    w = h = 200;
}

void Filter::draw(){
    ofNoFill();
    ofSetColor(200, 0, 0);
    ofRect(x, y, w, h);
}

double Filter::process(double sample){
    if(type == "lores"){
        sample = fil.lores(sample, 1500, 10);
    }
    else if(type == "hires"){
        sample = fil.hires(sample, 15000, 2);
    }
    else{
//        sample = fil.bandpass(sample, 15000, 50);
    }
    return sample;
}

void Filter::setResValue(double value){
    
}

void Filter::setCutOffValue(double value){
    
}

bool Filter::isInBounds(int x, int y){
    if(x > this->x && x < this->x+w && y > this->y && y < this->y + h){
        return true;
    }
    return false;
}