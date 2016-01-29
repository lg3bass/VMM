#pragma once

#include "ofMain.h"
#include "ofxTween.h"
#include "ofxOsc.h"

// listen on port 12345
// port 7000 is for my VMM project
#define PORT 7000
#define NUM_MSG_STRINGS 20

class ofApp : public ofBaseApp{

	public:
    
        struct circle {
            int unit;
            int height;
            int radius;
            int x;
            int y;
        };
    
        circle myCircle;
    
    
    
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        void OSClaunch(int _durration);
		
        void DrawCircle(int y,int m, int r);
    
    
    
        float length_float;
    
        unsigned durration;
    
        ofxTween tweenback;
        ofxTween tweenbounce;
        ofxTween tweencirc;
        ofxTween tweencubic;
        ofxTween tweenelastic;
        ofxTween tweenexpo;
        ofxTween tweenlinear;
        ofxTween tweenquad;
        ofxTween tweenquart;
        ofxTween tweenquint;
        ofxTween tweensine;
        
        ofxTween multitween;
        
        ofxEasingBack 	easingback;
        ofxEasingBounce 	easingbounce;
        ofxEasingCirc 	easingcirc;
        ofxEasingCubic 	easingcubic;
        ofxEasingElastic easingelastic;
        ofxEasingExpo 	easingexpo;
        ofxEasingLinear 	easinglinear;
        ofxEasingQuad 	easingquad;
        ofxEasingQuart 	easingquart;
        ofxEasingQuint 	easingquint;
        ofxEasingSine	easingsine;
    
        //OSC
        ofTrueTypeFont font;
        ofxOscReceiver receiver;
        
        int current_msg_string;
        string msg_strings[NUM_MSG_STRINGS];
        float timers[NUM_MSG_STRINGS];
        
        int mouseX, mouseY;
        string mouseButtonState;
        
        ofImage receivedImage;

    
};
