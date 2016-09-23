#pragma once
#include "ofAppGlutWindow.h"
#include "ofMain.h"
#include "oscRouter.h"
#include "objFileLoader.h"
#include "vboMeshObj.h"
//#include "trackParams.h"//Why if I comment this out does it work?
#include "bwUtil.h"

#include "ofxSyphon.h"
//#include "ofxAutoReloadedShader.h"
#include "ofxGui.h"
#include "ofxUI.h"
#include "ofxOsc.h"
#include "ofxTween.h"
#include "ofxJSON.h"


//default 21
#define NUM_TRACKS 11
#define PORT 7000

class ofApp : public ofBaseApp{

	public:
    
        enum TEST_SEQENCES{
            BANDTUBE = 1,
            BASSSTAR = 2,
            BLOCKSTAR = 3,
            BOXSTAR = 4,
            UNBLOCKERBASS = 5,
            TRACERS = 6,
            STARBURST = 7,
            WIERDARMS3 = 8,
            WIERDARMS2 = 9,
            WIERDARMS1 = 10,
            LIGHTNING10 = 11,
            LIGHTNING9 = 12,
            LIGHTNING8 = 13,
            LIGHTNING7 = 14,
            LIGHTNING6 = 15,
            EXTRUDETRI = 16,
            EXTRUDESTAR = 17,
            EXTRUDEBALL = 18,
            DIAMONDLAYERS = 19,
            RIPTIDETEST = 20
        };
    
        //JSON
        ofxJSONElement result;
        
        //SYPHON
        ofxSyphonServer mainOutputSyphonServer;
        ofxSyphonClient mClient;
    
        ofEasyCam cam;
    
        //matcap Shader
        ofImage matCap;
        ofImage matCap2;
        ofImage matCap3;
        ofShader shader;
        
        //modifier keys
        bool modkey;
        bool ctrlKey;
        bool rAltKey;
        bool lAltKey;
        bool rShiftKey;

        //1. get paths to the obj files.
        objFileLoader appFileLoader;
        
        //2. load obj files to separate vbomeshes. FOR NOW :)
        vector<vboMeshObj> tracks;
        int selectedTrack;
    
        //MASTER LIGHT
        ofLight light0;
    
        //GUI(MATCAP)
        //ofxPanel matcapGui;
        //bool matcapGui_minimized;
    
    
        //GUI(DEBUG)
        ofxPanel gui;
        bool minimized;
        ofParameterGroup parameters;
        ofXml settings;
    
        //ofxUI
        ofxUITabBar *guiTabBar;
        vector<ofxUICanvas *> guis;
    
        ofxUICanvas* trackGui;//not used -- test
    
    
        //ofxOSC
        ofxOscReceiver receiver;
    
        //myBass
        float amplitude;
    
        void setup();
		void update();
		void draw();
        void exit();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        void drawLights();
        void guiTabEvent(ofxUIEventArgs &e);
        int currentSelectedTrack(string _name);
    
        //OSC
        void OSChandler();
    
        oscRouter router;
    
    
        
        //TEMP VARIABLE FOR TESTING
        int playedNotes = 0;
    
    
};
