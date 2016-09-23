//
//  trackParams.h
//  ofxObjLoader_test10
//
//  Created by White, Bob on 4/29/16.
//
//

#include "ofMain.h"
#include "ofxTween.h"

struct guiParams {
    
    string title;
    string sequenceName;
    
    int trackIndex;                 //Which obj sequence is loaded.
    
    bool playAll;                   //play all the buffers to the next segment
    bool playAllFinalize;           //play all the buffers to the end of object sequence
    bool trackAssigned;
    bool isSelected;
    bool isLoaded;
    bool isPlaying;
    int instancePlayingId;
    int lastInstancePlayed;
    bool still;
    bool oscControlled;
    bool mirrored;
    bool mirrorX;
    bool mirrorY;
    bool mirrorZ;
    int tweenType;
    bool playNoteOff;
    string type;
    int numOfSeg;
    
    //tweens
    //bool randGlobalPosBool[3] = {false, false, false};
    //vector<bool> randGlobalPosBool;
    bool randGlobalPosBoolX;
    bool randGlobalPosBoolY;
    bool randGlobalPosBoolZ;
    
    //vector<bool>randGlobalRotBool;
    bool randGlobalRotBoolX;
    bool randGlobalRotBoolY;
    bool randGlobalRotBoolZ;
    
    //vector<bool> randLocalPosBool;
    bool randLocalPosBoolX;
    bool randLocalPosBoolY;
    bool randLocalPosBoolZ;
    
    //vector<bool>randLocalRotBool;
    bool randLocalRotBoolX;
    bool randLocalRotBoolY;
    bool randLocalRotBoolZ;
    
    //vector<bool>randObjRotBool;
    bool randObjRotBoolX;
    bool randObjRotBoolY;
    bool randObjRotBoolZ;

    float mirror_distance;
    //int currentSegment;
    vector<int> cuePoints;
    vector<int> durrationPoints;
    vector<int> midpointCues;
    vector<int> segmentLengths;
    int stillFrame;
    int totalFrames;
    int testSpeed;//speed
    
    bool spinX;
    bool spinY;
    bool spinZ;
    ofVec3f spin;
    ofVec3f spinRange;
    int ltransMod;
    
    //mod params
    //global
    int g_copies;
    bool gScale;
    float g_scale;
    float gScaleMod;
    float gScaleModVal;

    bool gTransX;
    bool gTransY;
    bool gTransZ;
    ofVec3f g_trans;
    ofVec3f gTransMod;
    ofVec3f gTransModVal;
    ofVec3f lastGlobalTrans;

    bool gRotX;
    bool gRotY;
    bool gRotZ;
    ofVec3f g_rotate;
    ofVec3f gRotateMod;
    ofVec3f gRotateModVal;
    ofVec3f lastGlobalRot;
    
    //local
    int l_copies;
    int l_slices;
    bool lScale;
    float l_scale;
    float lScaleMod;
    float lScaleModVal;

    bool lRotX;
    bool lRotY;
    bool lRotZ;
    ofVec3f l_rotate;
    ofVec3f lRotateMod;
    ofVec3f lRotateModVal;
    ofVec3f lastLocRot;
    
    bool lTransX;
    bool lTransY;
    bool lTransZ;
    ofVec3f l_trans;
    ofVec3f lTransMod;
    ofVec3f lTransModVal;
    ofVec3f lastLocTrans;

    //object
    bool oRotX;
    bool oRotY;
    bool oRotZ;
    //vector<bool> oRot;//test boolean vector
    ofVec3f o_rotate;
    ofVec3f oRotateMod;
    ofVec3f oRotateModVal;
    ofVec3f lastObjRot;
    
};

class trackParams {

    
    
    
public:

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
    
    trackParams();
    
    void setDefault(guiParams &params);

    void reportParams(guiParams &params, int _index);
    
    void setOSCtoggle(guiParams &params, string paramName, bool isActive);
    
    void setOSCtween(guiParams &params, ofxTween &tween, string paramName, ofxEasing &easingCurve, float _rotX, float _duration);
    
    void setOSCdial(guiParams &params, string paramName, float _value);
    
    
};



