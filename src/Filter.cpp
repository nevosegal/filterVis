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
    
    //initial stuff
    this->x = x;
    this->y = y;
    this->type = type;
    w = h = 200;
    resValue = 1;
    cutOffRange = 18000;
    resRange = 100;
    active = false;
    
    //some setup according to the filter type.
    if(type == "lores"){
        cutOffValue = cutOffRange;
    }
    else if(type == "hires"){
        cutOffValue = 0;
    }
}

//filter draw function
void Filter::draw(){
    ofNoFill();
    
    //drawing the box
    ofSetColor(200, 0, 0);
    ofRect(x, y, w, h);
    
    //drawing the circle that indicates the cutoff/resonance values.
    ofSetColor(200, 200, 200);
    circleX = x + w*((float)cutOffValue/cutOffRange);
    circleY = y + h - h*((float)resValue/resRange);
    ofCircle(circleX, circleY, 4);
    
    //drawing the values next to the circle
    ofDrawBitmapString("(" + ofToString(cutOffValue) + "," + ofToString(resValue) + ")", circleX+10, circleY+5);
    
    //drawing the title according to the filter type
    if(type == "lores"){
        ofDrawBitmapString("Low-pass filter", x+45, y-15);
    }else{
        ofDrawBitmapString("High-pass filter", x+45, y-15);
    }
    
    //drawing the axis labels
    ofDrawBitmapString("Cutoff Frequency (Hz)", x + 20, y + h + 15);
    ofDrawBitmapString("Resonance", x - 80, y + h/2);
    
}

//the process function, where the filtering happens.
double Filter::process(double sample){
    if(type == "lores"){
        sample = fil.lores(sample, cutOffValue, resValue);
    }
    else if(type == "hires"){
        sample = fil.hires(sample, cutOffValue, resValue);
    }
    return sample;
}

//setters
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

//checking if the filter box is hovered.
bool Filter::isInBounds(int x, int y){
    if(x > this->x && x < this->x+w && y > this->y && y < this->y + h){
        return true;
    }
    return false;
}

//activate the filter
void Filter::activate(){
    active = true;
}

//deactivate the filter
void Filter::deactivate(){
    active = false;
}

//check if the filter is activated.
bool Filter::isActivated(){
    return active;
}