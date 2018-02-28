#pragma once

#include "ofMain.h"
#include "abletonlink.h"
#include "oscHandler.h"

//panels
#include "HeaderPanel.h"
#include "TimelinePanel.h"
#include "FooterPanel.h"



#define HEADER_PANEL_HEIGHT 0.17
#define BODY_PANEL_HEIGHT 0.73
#define FOOTER_PANEL_HEIGHT 0.1

#define HOST "localhost"
#define rPORT 7006 //recieve from AbletonLive
#define sPORT 7005 //send to VMM.


struct appData {
    string selected_panel_name;
    ofColor txt_color;
};

class ofApp : public ofBaseApp{
    
public:
    
    bool ctrlKeyPressed = false;
    
    abletonLinkEngine AL;
    appData myAppData;
    
    #pragma mark - ofApp.cpp

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
    
    #pragma mark - ofAppRouter.cpp
    //timePanel functions

    void enableOscOut();
    
    void setControllerData(string name, int data);
    
    void addChannel(string name, int type);
    void remChannel();
    
    #pragma mark - ofAppRouter.cpp save/load functions
    void setTLProject(string dialogMsg);
    
    void saveTLPage();
    void saveTLTrackPages();
    void saveTLAllTracks();
    
    void loadTLPage();
    void loadTLTrackPages();
    void loadTLAllTracks();
    
    void nextKey();
    void prevKey();
    void setKeyVal(int _val);
    
    void setTimePanelEnabled(bool _val);
    
    
    //headerPanel functions
    void setBreadcrumb();
    void displayKeyValue(int _val);
    void selectChannel(int _index);
    
    void passTextValue(string _name, string _val);
    void setLinkSlider(int _beat);
    void setFramesUI();
    
    void playTLclip(int _track, int _clip);
    void stopTLclip(int _clip);                     //_clip does NOTHING
    
    //panels
    HeaderPanel headerPanel;
    TimelinePanel timePanel;
    FooterPanel footerPanel;
    
    #pragma mark - OSC
    ofxOscReceiver receiver_timeline;
    ofxOscSender sender;
    oscHandler router;
    
    void OscReciever();
    void OSCsendToVMM(int _track, string _address, float _value);
    
    void OSCnoteOnAndPlay(int _track, string _address, string _value);
    /*
    void oscEvent(OscMsgEvent &e);
    void anotherEvent(anotherOscMsgEvent &e);
    */
    void OscSendEvent(VMMOscMessageEvent &e);
    
    void OSCsendMessage(int track, string address, string message);

    void sendOSCtestData(int track, int clip);
    
private:
    

    

};
