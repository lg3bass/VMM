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
    
    
    void drawPanelBgAndBorder(bool state){
        if(state){
            ofPushStyle();
            //draw the background
            ofSetColor(getBackgroundColor(), 80);
            ofDrawRectRounded(_x, _y, _w, _h, 4.0);
            
            //draw the border
            if(getPanelFocus()){
                ofSetColor(getBorderColorHighlight());
                ofSetLineWidth(getBorderWidth()+2);
            } else {
                ofSetColor(getBorderColor());
                ofSetLineWidth(getBorderWidth());
            }

            ofNoFill();
            ofDrawRectRounded(_x, _y, _w, _h, 4.0);
            ofPopStyle();
            
            ofDrawBitmapString(panelName + " - enableMouseInput: " + ofToString(getEnableMouseInput() ? "TRUE" : "FALSE"), _w+10, _y+10);
            
            if(isWithinBounds(ofGetMouseX(), ofGetMouseY())){
                ofDrawBitmapString("Inside " + panelName, _w+10, _y+20);
                
            }
            
            
        }
    }
    
    
    bool isWithinBounds(int x, int y){
        if(panelBoundingBox.inside(x,y)){
            return true;
        } else {
            return false;
        }
    }
    
    //setters
    void setPanelName(string name){panelName = name;}
    void setPosition(ofVec2f pos){_x = pos.x; _y = pos.y;}
    void setWidth(int w){_w = w ;}
    void setHeight(int h){_h = h;}
    void setBackgroundColor(ofColor col){backgroundColor = col;}
    void setBorderColor(ofColor col){borderColor = col;}
    void setBorderColorHighligh(ofColor col){borderColorHighlight = col;}
    void setBorderWidth(int w){borderWidth = w;}
    void setPanelFocus(bool focused) {panelFocused = focused;}
    void setEnableMouseInput(bool mouse) {enableMouseInput = mouse;}
    
    
    //getters
    string getPanelName(){return panelName;}
    ofVec2f getPosition(){return ofVec2f(_x, _y);}
    int getWidth(){return _w;}
    int getHeight(){return _h;}    
    ofColor getBackgroundColor(){return backgroundColor;}
    ofColor getBorderColor(){return borderColor;}
    ofColor getBorderColorHighlight(){return borderColorHighlight;}
    int getBorderWidth(){return borderWidth;}
    bool getPanelFocus(){return panelFocused;}
    bool getEnableMouseInput(){return enableMouseInput;}
    
    
    ofRectangle panelBoundingBox;

    
protected:
    bool panelFocused;
    bool enableMouseInput = true;
    
    
    string panelName;
    int _x, _y;
    int _w, _h;
    
    //default colors
    ofColor backgroundColor = ofColor::darkGray;
    ofColor borderColor = ofColor::white;
    ofColor borderColorHighlight = ofColor::orangeRed;
    int borderWidth = 2;
    
    
    
};

