//
//  LeftPanel.hpp
//  VMMtimeline_9-8
//
//  Created by Bob White on 10/1/18.
//
#pragma once

#ifndef LeftPanel_h
#define LeftPanel_h

#include "ofMain.h"
#include "Panel.h"

#include "ofxDatGui.h"
#include "ofxDatGuiThemesVMM.h"

#endif /* LeftPanel_h */

class LeftPanel : public Panel{
    
public:
    void setup(int x, int y, int width, int height, ofBaseApp* appPtr);
    void update();
    void draw();
    void exit(){};
    
    void keyPressed(int key);
    
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);

    //UI test
    ofxDatGuiButton* small;
    ofxDatGuiButton* large;
    
    void onButtonEvent(ofxDatGuiButtonEvent e);

private:
    
    
};
