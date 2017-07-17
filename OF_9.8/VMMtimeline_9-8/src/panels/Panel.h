//
//  Panel.h
//  PATTERN_shared_ptr
//
//  Created by Robert White III on 6/8/17.
//
//
#pragma once

#ifndef Panel_h
#define Panel_h

#include "ofMain.h"

#endif /* Panel_h */

class Panel{
    
public:
    
    virtual void setup(int x, int y, int width, int height, ofBaseApp* appPtr){};
    virtual void update() =0;
    virtual void draw() =0;
    virtual void exit() =0;
        
    void drawBackground(){
        ofPushStyle();
        ofSetColor(getBackgroundColor());
        ofDrawRectangle(_x, _y, _w, _h);
        ofPopStyle();
    }
    
    void drawPanel(){
        ofPushStyle();
        ofSetColor(getBackgroundColor(), 50);
        ofDrawRectRounded(_x, _y, _w, _h, 4.0);
        
        ofSetColor(getBorderColor());
        ofSetLineWidth(getBorderWidth());
        ofNoFill();
        ofDrawRectRounded(_x, _y, _w, _h, 4.0);
        ofPopStyle();
        
    }
    
    //setters
    void setPosition(ofVec2f pos){_x = pos.x; _y = pos.y;}
    void setWidth(int w){_w = w ;}
    void setHeight(int h){_h = h;}
    void setBackgroundColor(ofColor col){_bckgColor = col;}
    void setBorderColor(ofColor col){_borderColor = col;}
    void setBorderWidth(int w){_borderWidth = w;}
    
    //getters
    ofVec2f getPosition(){return ofVec2f(_x, _y);}
    int getWidth(){return _w;}
    int getHeight(){return _h;}    
    ofColor getBackgroundColor(){return _bckgColor;}
    ofColor getBorderColor(){return _borderColor;}
    int getBorderWidth(){return _borderWidth;}
    
    
protected:
    
    int _x, _y;
    int _w, _h;
    ofColor _bckgColor;
    ofColor _borderColor;
    int _borderWidth;
    
    
};
