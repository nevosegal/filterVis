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
    cutOffRange = 18000;
    resRange = 100;
    active = false;
    
    if(type == "lores"){
        cutOffValue = cutOffRange;
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
    circleX = x + w*((float)cutOffValue/cutOffRange);
    circleY = y + h - h*((float)resValue/resRange);
    ofCircle(circleX, circleY, 4);
    ofDrawBitmapString("(" + ofToString(cutOffValue) + "," + ofToString(resValue) + ")", circleX+10, circleY+5);
    if(type == "lores"){
        ofDrawBitmapString("Low-pass filter", x+45, y-15);
    }else{
        ofDrawBitmapString("High-pass filter", x+45, y-15);
    }
    ofDrawBitmapString("Cutoff Frequency (Hz)", x + 20, y + h + 15);
    ofDrawBitmapString("Resonance", x - 80, y + h/2);
    
}

double Filter::process(double sample){
    if(type == "lores"){
        sample = fil.lores(sample, cutOffValue, resValue);
    }
    else if(type == "hires"){
        sample = fil.hires(sample, cutOffValue, resValue);
    }
    return sample;
}

void Filter::setResValue(double value){
    if(value < resRange && value > 1){
        resValue = value;
    }
}

void Filter::setCutOffValue(double value){
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

void Filter::activate(){
    active = true;
}

void Filter::deactivate(){
    active = false;
}

bool Filter::isActivated(){
    return active;
}