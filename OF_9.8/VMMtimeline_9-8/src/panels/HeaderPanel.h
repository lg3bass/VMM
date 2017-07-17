//
//  HeaderPanel.h
//  PATTERN_shared_ptr
//
//  Created by Robert White III on 6/8/17.
//
//
#pragma once

#ifndef HeaderPanel_h
#define HeaderPanel_h

#include "ofMain.h"
#include "Panel.h"
#include "headerUI.h"

#endif /* HeaderPanel_h */




class HeaderPanel : public Panel{
    
public:

    void setup(int x, int y, int width, int height, ofBaseApp* appPtr);
    void update();
    void draw();
    void exit(){};
    
    void keyPressed(int key);
    
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    
    headerUI mainUI;
    
    void setTrack(int _track);
    void setClip(int _clip);
    void setPage(int _page);

private:
    
    ofTrueTypeFont	verdana;

    
    
    
    
};
