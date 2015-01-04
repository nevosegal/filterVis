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
    resValue = 1;
    cutOffRange = 15000;
    resRange = 100;
    if(type == "lores"){
        cutOffValue = 15000;
    }
    else if(type == "hires"){
        cutOffValue = 0;
    }
}

void Filter::draw(){
    ofNoFill();
    ofSetColor(200, 0, 0);
    ofRect(x, y, w, h);
    ofSetColor(200, 200, 200);
    ofCircle(x + w*((float)cutOffValue/cutOffRange), y + h - h*((float)resValue/resRange), 4);
    ofDrawBitmapString("Frequency", x + 60, y + h + 15);
    ofDrawBitmapString("Resonance", x - 80, y + h/2);
}

double Filter::process(double sample){
    if(type == "lores"){
        sample = fil.lores(sample, cutOffValue, resValue);
    }
    else if(type == "hires"){
        sample = fil.hires(sample, cutOffValue, resValue);
    }
    else{
//        sample = fil.bandpass(sample, 15000, 50);
    }
    return sample;
}

void Filter::setResValue(double value){
    cout << "res: ";
    cout << value <<endl;
    if(value < resRange && value > 1){
        resValue = value;
    }
}

void Filter::setCutOffValue(double value){
    cout << "cutoff: ";
    cout << value << endl;
    if(value < cutOffRange && value > 0){
        cutOffValue = value;
    }

}

bool Filter::isInBounds(int x, int y){
    if(x > this->x && x < this->x+w && y > this->y && y < this->y + h){
        return true;
    }
    return false;
}