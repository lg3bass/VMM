#pragma once

#include "ofMain.h"
#include "abletonlink.h"

//panels
#include "HeaderPanel.h"
#include "timelinePanel.h"
#include "FooterPanel.h"

#define HEADER_PANEL_HEIGHT 0.16
#define BODY_PANEL_HEIGHT 0.74
#define FOOTER_PANEL_HEIGHT 0.1

struct appData {
    string selected_panel_name;
    ofColor txt_color;
};



class ofApp : public ofBaseApp{
    
public:
    
    abletonLinkEngine AL;
    
    appData myAppData;
    
    //ofApp.cpp
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    
    //ofAppRouter.cpp
    //timePanel functions
    
    void setControllerData(string name, int data);
    void addTLTrack(string name, int type);
    void remTLTrack();
    
    void nextKey();
    void prevKey();
    void setKeyVal(int _val);
    
    //headerPanel functions
    void setBreadcrumb();
    void displayKeyValue(int _val);
    void selectChannel(int _index);
    
    void passTextValue(string _name, string _val);
    void setLinkSlider(int _beat);
    
private:
    
    //panels
    HeaderPanel headerPanel;
    timelinePanel timePanel;
    FooterPanel footerPanel;
    

};
