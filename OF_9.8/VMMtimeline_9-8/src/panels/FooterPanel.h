//
//  FooterPanel.h
//  PATTERN_shared_ptr
//
//  Created by Robert White III on 6/8/17.
//
//
#pragma once

#ifndef FooterPanel_h
#define FooterPanel_h

#include "ofMain.h"
#include "Panel.h"

#endif /* FooterPanel_h */

class FooterPanel : public Panel{
    
public:
    
    void setup(int x, int y, int width, int height, ofBaseApp* appPtr);
    void update();
    void draw();
    void exit(){};
    
    void keyPressed(int key);
    
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);

private:
    
    ofTrueTypeFont	verdana;
    ofColor bordCol;
    int bordWidth;

    
    
};
