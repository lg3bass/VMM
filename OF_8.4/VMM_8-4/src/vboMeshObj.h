#pragma once

#include "ofMain.h"
#include "ofxObjLoader.h"
#include "objFileLoader.h"
#include "trackParams.h"
#include "ofParameterGroup.h"
#include "ofParameter.h"
#include "bwUtil.h"
#include "ofxUI.h"
#include "ofxTween.h"
#include "ofxJSON.h"

class vboMeshObj {
    
    public:
    objFileLoader::extObjFile trackData;
    ofxJSONElement jsonTrackData;
    
    vector<ofVboMesh> vboMesh1;
    int index;          //What track number you are as shown in the track labels and GUI
    int objSeqIndex;    //What object sequence is loaded
    int matcapIndex;    //What matcap shader is selected.
    
    //list of Files
    vector<string> availObjSeq;
    
    //------------------------------------
    //ALL OF THE TRACK PARAMETERS.
    trackParams trackParameters;
    
    //------------------------------------
    //ALL OF THE INSTANCES (move to class)
    struct instance {
        bool cued2play;
        bool isPlaying;
        bool isTweening;
        bool playToEnd;
        bool playNoteOff;
        int midiState; // 1=noteOn, 0=noteOff
        int currentSegment;
        int noteID;
        int note;
        int vel;
        int delta;
        int frame;
        int startFrame;
        int midFrame;
        int endFrame;
        int direction; //forward=1, reverse=2;
        int duration;
        int clockedDurration;
        
        
    };
    vector<instance> instances;
    
    //setup the track params.
    guiParams params;
    
    //------------------------------------
    //matCaps
    ofImage matCap;
    ofShader shader;
    vector<string> matcaps;
    
    
    //------------------------------------
    /* Debug parameters ofxgui */
    ofParameterGroup parameters;
    ofParameter<int> gui_buffers;
    ofParameter<int> gui_instancePlayingId;
    
    ofParameter<string> gui_cued2PlayList;
    ofParameter<string> gui_instanceList;
    ofParameter<string> gui_isTweeningList;
    ofParameter<string> gui_isPlayingList;
    ofParameter<string> gui_currentSegment;

    
    //------------------------------------
    // ofxTween
    vector <ofxTween> backTweens;
    vector <ofxTween> bounceTweens;
    vector <ofxTween> circTweens;
    vector <ofxTween> cubicTweens;
    vector <ofxTween> elasticTweens;
    vector <ofxTween> expoTweens;
    vector <ofxTween> quadTweens;
    vector <ofxTween> quartTweens;
    vector <ofxTween> quintTweens;
    vector <ofxTween> sineTweens;
    vector <ofxTween> linearTweens;
    
    ofxTween multitween;
    
    ofxEasingBack       easingback;
    ofxEasingBounce     easingbounce;
    ofxEasingCirc       easingcirc;
    ofxEasingCubic      easingcubic;
    ofxEasingElastic    easingelastic;
    ofxEasingExpo       easingexpo;
    ofxEasingQuad       easingquad;
    ofxEasingQuart      easingquart;
    ofxEasingQuint      easingquint;
    ofxEasingSine       easingsine;
    ofxEasingLinear 	easinglinear;
    
    //global tweens
    //vector<ofxTween> posRandomGlobalRot;
    ofxTween posRandomGlobalRotX;
    ofxTween posRandomGlobalRotY;
    ofxTween posRandomGlobalRotZ;
    
    ofxTween posRandomGlobalX;
    ofxTween posRandomGlobalY;
    ofxTween posRandomGlobalZ;
    
    //local tweens
    ofxTween posRandomLocalRotX;
    ofxTween posRandomLocalRotY;
    ofxTween posRandomLocalRotZ;
    
    ofxTween posRandomLocalX;
    ofxTween posRandomLocalY;
    ofxTween posRandomLocalZ;
    
    //object tweens
    ofxTween posRandomObjRotX;//object rotation X
    ofxTween posRandomObjRotY;//object rotation Y
    ofxTween posRandomObjRotZ;//object rotation Z
    
    
    //constructor
    vboMeshObj();
    
    ofxUICanvas* gui;
    //ofxUICanvas* gui2;

    
    void setup(int _input);
    void loadTrackData(int _index);
    void setTrack(int _index);
    void loadTrack();
    vector<int> parseJSON(string _param);
    vector<ofVboMesh> passObjTwoVboMesh(vector<ofFile> _files);
    void loadVboMesh(const objFileLoader::extObjFile &_input);
    void setMatCap(int _imgIndex);
    void setShader(string _shader);
    void draw();
    void update();
    void KeyboardLaunch(int _string, int _note, int _tweenType, int _instanceId, bool _noteOff = false);
    void setupGui(int _index);
    void updateGui(int _index);
    void setGuiSnapUnits(string _name,float _unit);
    void setIndicator();
    void resetBufferInstance(int _buffer, string _mode);
    void clear();

    
    //OSC
    void bassControl(float &_amp, int _noteLength);
    
    //GUI
    void guiEvent(ofxUIEventArgs &e);
    
    //Computer Keyboard
    void keyPressed(int key);
    void keyReleased(int key);
    
    //Animate
    void advanceInstance();
    void advanceSegment(int _buffer);
    void noteOn(int _buffer, int _noteId, int _note, int _velocity, int _delta);
    void play(int _buffer, int _noteID, int _duration, int _tweenType);
    void noteOff(int _noteId, int _durration);
    void tweenPlayInstance(int _buffer, int _tweenType, int _start, int _end, int _duration, int _delay);
    
    void exit();
    
    private:
};