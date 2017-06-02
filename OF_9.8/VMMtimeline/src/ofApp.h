#pragma once

#include "ofMain.h"
#include "ofxTimeline.h"
#include "ofxAbletonLink.h"
#include "ofxOsc.h"

//panels
#include "TimelinePanel.h"
#include "HeaderPanel.h"
#include "TrackButtonPanel.h"

//osc router
#include "OscHandler.h"


#define HOST "localhost"
#define rPORT 7006 //recieve from AbletonLive
#define sPORT 7005 //send to VMM.

#define MAIN_PANEL_HEIGHT 0.15
#define TIME_PANEL_HEIGHT 0.85
#define METER_PANEL_HEIGHT 0.45//not needed

#define BUTTON_PANEL_WIDTH 50;

#define INIT_FPS 30

//TRACKS
#define NUMBER_OF_TRACKS 5

//temporary
#define TIMELINE_SETTINGS_DIR "clip"
#define CLIP_DIR "clip"
#define TRACK_DIR "track"


struct trackData {
    int cued_clip;
    int selected_clip;
    int slices;
    int measures;
    int current_page;
    bool cuedToPlay;
    bool directDrive;                   //flag to turn on sending all OSC out.
    
};

struct appData {
    int selected_track;
    float tempo;
    int meter;    
    vector<trackData> tracks;
    
};


class ofApp : public ofBaseApp{


    
public:
    
    appData myAppData;
    
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

    //panels
    TimelinePanel timePanel;
    HeaderPanel headerPanel;
    TrackButtonPanel buttonPanel;

    
    //getters and setters
    void showMeCurrentTrackClipPage(int _track);
    
    float getGlobalTempo();
    void setGlobalTempo(float _t);
    
    void play(int _track, int _clip);
    void stop(int _track);
    
    void resetAllTrackAndClips();
    
    int getSelectedTrack();
    void setSelectedTrack(int _track);
    
    int getSelectedClip(int _track);
    void setSelectedClip(int _track, int _clip);
    
    int getCurrentPage(int _track);
    void setCurrentPage(int _track, int _page);
    
    bool getIsCuedToPlay(int _track);
    void setCuedToPlay(int _track, bool _val);
    
    void displayTrack(int _track);
    void setClipAndPageButtons(int _track);
        
    //OSC
    ofxOscReceiver receiver_timeline;
    ofxOscSender sender;
    OscHandler router;
    
    void OscReciever();
    void OSCsendToVMM(int _track, string _address, float _value);
    

    
private:
    
    int _frameRate;
    float _tempo;
    
		
};
