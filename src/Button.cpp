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
    
    //initial stuff.
    this->x = x;
    this->y = y;
    w = 40;
    h = 25;
    this->type = type;
    active = false;
    
    //choosing the image according to the type.
    if(type == "lores"){
        img.loadImage("lowpass.png");
    }else{
        img.loadImage("highpass.png");
    }

}

//drawing the button
void Button::draw(){
    if(active){
        ofSetColor(220);
    }else{
        ofSetColor(80);
    }
    ofRect(x,y,w,h);
    img.draw(x, y, w,h);
}

//checking if the button is hovered.
bool Button::isInBounds(int x, int y){
    if(x > this->x && x < this->x+w && y > this->y && y < this->y + h){
        return true;
    }
    return false;
}

//activating the button
void Button::activate(){
    active = true;
}

//deactivating the button
void Button::deactivate(){
    active = false;
}

//checking if the button is activated.
bool Button::isActivated(){
    return active;
}