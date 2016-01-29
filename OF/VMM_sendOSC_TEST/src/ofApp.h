#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

#define HOST "localhost"
#define PORT 7000
#define NUM_MSG_STRINGS 24

//--------------------------------------------------------
class ofApp : public ofBaseApp {

	public:

		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
        //noteOn [track:4, buffer:1, string:1, noteId:4, midiNote:60, velocity:63, durration(last):1000, delta:26422, noteOn|Off:1]
        void noteOn(int track, int buffer, int string, int noteID, int midiNote, int velocity, int duration, int delta, int noteOnOff);
    
        //play [track:4, buffer:1, string:1, noteId:4, midiNote:60, cue:1, duration:601, tween:11]
        void play(int track, int buffer, int string, int noteId, int midiNote, int cue, int duration, int tween);
    
        //noteOff [track:4, string:1, noteId:4, midiNote:60, velocity:0, real-duration:1000, delta:26422, note On|Off:0]
        void noteOff(int track, int string, int noteID, int midiNote, int velocity, int duration, int delta, int noteOnOff);
    
        bool singleKeyDown;

		ofTrueTypeFont font;
		ofxOscSender sender;
    
        string tempString;
    
        int current_msg_string;
        string msg_strings[NUM_MSG_STRINGS];
        float timers[NUM_MSG_STRINGS];
    
        void updateMessages(string msg);
    
        int bufferCounter;
    
};

