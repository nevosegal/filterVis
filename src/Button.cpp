//
//  Button.cpp
//  filterVis
//
//  Created by Nevo Segal on 04/01/2015.
//
//

#include "Button.h"

Button::Button(){
    
}

Button::Button(int x, int y, string type){
    this->x = x;
    this->y = y;
    w = 40;
    h = 25;
    this->type = type;
}

void Button::draw(){
    if(active){
        ofSetColor(200);
    }else{
        ofSetColor(100);
    }
    ofRect(x,y,w,h);
}

bool Button::isInBounds(int x, int y){
    if(x > this->x && x < this->x+w && y > this->y && y < this->y + h){
        return true;
    }
    return false;
}

void Button::activate(){
    active = true;
}

void Button::deactivate(){
    active = false;
}

bool Button::isActivated(){
    return active;
}