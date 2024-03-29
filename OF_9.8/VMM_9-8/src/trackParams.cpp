//
//  trackParams.cpp
//  ofxObjLoader_test10
//
//  Created by White, Bob on 4/29/16.
//
//

#include "trackParams.h"

trackParams::trackParams(){

    
    
}

//--------------------------------------------------------------
void trackParams::setDefault(guiParams &params){
    
    params.title = "TEST TITLE";
    
    params.sequenceName = "undefined";
    
    params.trackIndex = 0;
    
    params.playAll = false;
    params.playAllFinalize = false;
    params.trackAssigned = false;
    params.isSelected = false;
    params.isLoaded = false;
    params.isPlaying = false;
    params.instancePlayingId = -1;// -1 = all
    params.lastInstancePlayed = -1;
    params.still = false;
    params.oscControlled = true;
    params.mirrored = false;
    params.mirrorX = false;
    params.mirrorY = false;
    params.mirrorZ = false;
    params.tweenType = 11;
    params.playNoteOff = true;  //this is the noteOn/Off switch. On = play only on NoteOn.  Off = play noteOn THEN noteOff.
    params.type = "";
    params.numOfSeg = 1;
    
    params.mirror_distance = 10.0;
    //params.currentSegment = 0;//moved to instances
    
    params.stillFrame = 0;
    params.totalFrames = 0;
    params.testSpeed = 500;
    
    params.spin = ofVec3f(0.0,0.0,0.0);
    params.spinRange = ofVec3f(0.0,0.0,0.0);
    params.spinX = false;
    params.spinY = false;
    params.spinZ = false;
    params.ltransMod = 0;
    
    //global
    params.g_copies = 1;
    params.gScale = false;
    params.g_scale = 20.0;
    params.gScaleMod = 0.0;
    params.gScaleModVal = 0.0;
    params.gTransX = false;
    params.gTransY = false;
    params.gTransZ = false;
    params.g_trans = ofVec3f(0.0,0.0,0.0);
    params.gTransMod = ofVec3f(0.0,0.0,0.0);
    params.gTransModVal = ofVec3f(0.0,0.0,0.0);
    params.lastGlobalTrans = ofVec3f(0.0,0.0,0.0);
    
    params.gRotX = false;
    params.gRotY = false;
    params.gRotY = false;
    params.g_rotate = ofVec3f(0.0,0.0,0.0);
    params.gRotateMod = ofVec3f(0.0,0.0,0.0);
    params.gRotateModVal = ofVec3f(0.0,0.0,0.0);
    params.lastGlobalRot = ofVec3f(0.0,0.0,0.0);
    
    //local
    params.l_copies = 12;
    params.l_slices = 2;
    params.lScale = false;
    params.l_scale = 10.0;
    params.lScaleMod = 0.0;
    params.lScaleModVal = 0.0;

    params.lRotX = false;
    params.lRotY = false;
    params.lRotY = false;
    params.l_rotate = ofVec3f(0.0,0.0,30.0);
    params.lRotateMod = ofVec3f(0.0,0.0,0.0);
    params.lRotateModVal = ofVec3f(0.0,0.0,0.0);
    params.lastLocRot = ofVec3f(0.0,0.0,0.0);
    
    params.lTransX = false;
    params.lTransY = false;
    params.lTransZ = false;
    params.l_trans = ofVec3f(0.0,0.0,0.0);
    params.lTransMod = ofVec3f(0.0,0.0,0.0);
    params.lTransModVal = ofVec3f(0.0,0.0,0.0);
    params.lastLocTrans = ofVec3f(0.0,0.0,0.0);
    
    //object
    params.oRotX = false;
    params.oRotY = false;
    params.oRotZ = false;
    
    params.o_rotate = ofVec3f(0.0,0.0,0.0);
    params.oRotateMod = ofVec3f(0.0,0.0,0.0);
    params.oRotateModVal = ofVec3f(0.0,0.0,0.0);
    params.lastObjRot = ofVec3f(0.0,0.0,0.0);
    
    //save channels
    params.saveChannel = false;
    
}


//--------------------------------------------------------------
void trackParams::reportParams(guiParams &params, int _i){
    
    ofLogVerbose("ofxUI") << "track " << _i << ",----" <<
    "playAll(" << params.playAll << ")," <<
    "playAllFinalize(" << params.playAllFinalize << ")," <<
    "isSelected(" << params.isSelected << ")," <<
    "isLoaded(" << params.isLoaded << ")," <<
    "isPlaying(" << params.isPlaying << ")," <<
    "instancePlayingId(" << params.instancePlayingId << ")," <<
    "lastInstancePlayed(" << params.lastInstancePlayed << ")," <<
    "still(" << params.still << ")," <<
    "oscControlled(" << params.oscControlled << ")," <<
    "mirrored(" << params.mirrored << ")," <<
    "mirrorX(" << params.mirrorX << ")," <<
    "mirrorY(" << params.mirrorY << ")," <<
    "mirrorZ(" << params.mirrorZ << ")," <<
    "tweenType(" << params.tweenType << ")," <<
    "playNoteOff(" << params.playNoteOff << ")," <<
    "numOfSeg(" << params.numOfSeg << ")," <<
    "mirror_distance(" << params.mirror_distance << ")," <<
    "stillFrame(" << params.stillFrame << ")," <<
    "totalFrames(" << params.totalFrames << ")," <<
    "testSpeed(" << params.testSpeed << ")," <<
    "spin(" << params.spin << ")," <<
    "spinRange(" << params.spinRange << ")," <<
    "spinX(" << params.spinX << ")," <<
    "spinY(" << params.spinY << ")," <<
    "spinZ(" << params.spinZ << ")," <<
    "ltransMod(" << params.ltransMod << ")," <<
    "g_copies(" << params.g_copies << ")," <<
    "gScale(" << params.gScale << ")," <<
    "g_scale(" << params.g_scale << ")," <<
    "gScaleMod(" << params.gScaleMod << ")," <<
    "gScaleModVal(" << params.gScaleModVal << ")," <<
    "gTransX(" << params.gTransX << ")," <<
    "gTransY(" << params.gTransY << ")," <<
    "gTransZ(" << params.gTransZ << ")," <<
    "g_trans(" << params.g_trans << ")," <<
    "gTransMod(" << params.gTransMod << ")," <<
    "gTransModVal(" << params.gTransModVal << ")," <<
    "gRotX(" << params.gRotX << ")," <<
    "gRotY(" << params.gRotY << ")," <<
    "gRotY(" << params.gRotY << ")," <<
    "g_rotate(" << params.g_rotate << ")," <<
    "gRotateMod(" << params.gRotateMod << ")," <<
    "gRotateModVal(" << params.gRotateModVal << ")," <<
    "l_copies(" << params.l_copies << ")," <<
    "l_slices(" << params.l_slices << ")," <<
    "lScale(" << params.lScale << ")," <<
    "l_scale(" << params.l_scale << ")," <<
    "lScaleMod(" << params.lScaleMod << ")," <<
    "lScaleModVal(" << params.lScaleModVal << ")," <<
    "lTransX(" << params.lTransX << ")," <<
    "lTransY(" << params.lTransY << ")," <<
    "lTransZ(" << params.lTransZ << ")," <<
    "l_trans(" << params.l_trans << ")," <<
    "lTransMod(" << params.lTransMod << ")," <<
    "lTransModVal(" << params.lTransModVal << ")," <<
    "lRotX(" << params.lRotX << ")," <<
    "lRotY(" << params.lRotY << ")," <<
    "lRotY(" << params.lRotY << ")," <<
    "l_rotate(" << params.l_rotate << ")," <<
    "lRotateMod(" << params.lRotateMod << ")," <<
    "lRotateModVal(" << params.lRotateModVal << ")," <<
    "oRotX(" << params.oRotX << ")," <<
    "oRotY(" << params.oRotY << ")," <<
    "oRotZ(" << params.oRotZ << ")," <<
    "o_rotate(" << params.o_rotate << ")," <<
    "oRotateMod(" << params.oRotateMod << ")," <<
    "oRotateModVal(" << params.oRotateModVal << "),";
    
}

//--------------------------------------------------------------
void trackParams::setOSCtoggle(guiParams &params, string paramName, bool isActive){
    if(paramName == "/butter"){
        params.isLoaded = isActive;
        
        
        
        
    } else if(paramName == "/still"){
        params.still = isActive;
    } else if (paramName == "/playNoteOff"){
        params.playNoteOff = isActive;
    } else if (paramName == "/playAll"){
        params.playAll = isActive;
    } else if (paramName == "/finalize"){
        params.playAllFinalize = true;
    } else if(paramName == "/mirror"){
        params.mirrored = isActive;
    } else if (paramName == "/mirrorX"){
        params.mirrorX = isActive;
    } else if (paramName == "/mirrorY"){
        params.mirrorY = isActive;
    } else if (paramName == "/mirrorZ"){
        params.mirrorZ = isActive;
    }
}


//ORIGINAL VERSION OF FUNCTION
//--------------------------------------------------------------
void trackParams::setOSCtween(guiParams &params, ofxTween &tween, string paramName, ofxEasing &easingCurve, float _ammount, float _duration){
    

    
    if(paramName == "/start"){

    // GLOBAL ROTATE --------------------------------------
    } else if (paramName == "/randGlobalRotX" || paramName == "/tweenGlobalRotX"){
        
        params.lastGlobalRot.x = params.g_rotate.x;    //store the last position
        tween.setParameters(easingCurve, ofxTween::easeOut,params.lastGlobalRot.x,_ammount, _duration,0);
        params.randGlobalRotBoolX = true; //start the animation

    } else if (paramName == "/randGlobalRotY" || paramName == "/tweenGlobalRotY"){
        params.lastGlobalRot.y = params.g_rotate.y;    //store the last position
        tween.setParameters(easingCurve, ofxTween::easeOut,params.lastGlobalRot.y,_ammount, _duration,0);
        params.randGlobalRotBoolY = true; //start the animation
    } else if (paramName == "/randGlobalRotZ" || paramName == "/tweenGlobalRotZ"){
        params.lastGlobalRot.z = params.g_rotate.z;    //store the last position
        tween.setParameters(easingCurve, ofxTween::easeOut,params.lastGlobalRot.z,_ammount, _duration,0);
        params.randGlobalRotBoolZ = true; //start the animation
        
    // GLOBAL TRANSLATE --------------------------------------
    } else if (paramName == "/randGlobalTransX" || paramName == "/tweenGlobalTransX"){
        params.lastGlobalTrans.x = params.g_trans.x;    //store the last position
        tween.setParameters(easingCurve, ofxTween::easeOut,params.lastGlobalTrans.x,_ammount, _duration,0);
        params.randGlobalPosBoolX = true; //start the animation
    } else if (paramName == "/randGlobalTransY" || paramName == "/tweenGlobalTransY"){
        params.lastGlobalTrans.y = params.g_trans.y;    //store the last position
        tween.setParameters(easingCurve, ofxTween::easeOut,params.lastGlobalTrans.y,_ammount, _duration,0);
        params.randGlobalPosBoolY = true; //start the animation
    } else if (paramName == "/randGlobalTransZ" || paramName == "/tweenGlobalTransZ"){
        params.lastGlobalTrans.z = params.g_trans.z;    //store the last position
        tween.setParameters(easingCurve, ofxTween::easeOut,params.lastGlobalTrans.z,_ammount, _duration,0);
        params.randGlobalPosBoolZ = true; //start the animation
        
    // LOCAL ROTATE --------------------------------------
    } else if (paramName == "/randLocalRotX" || paramName == "/tweenLocalRotX"){
        params.lastLocRot.x = params.l_rotate.x;    //store the last position
        tween.setParameters(easingCurve, ofxTween::easeOut,params.lastLocRot.x,_ammount, _duration,0);
        params.randLocalRotBoolX = true; //start the animation
    } else if (paramName == "/randLocalRotY" || paramName == "/tweenLocalRotY"){
        params.lastLocRot.y = params.l_rotate.y;    //store the last position
        tween.setParameters(easingCurve, ofxTween::easeOut,params.lastLocRot.y,_ammount, _duration,0);
        params.randLocalRotBoolY = true; //start the animation
    } else if (paramName == "/randLocalRotZ" || paramName == "/tweenLocalRotZ"){
        params.lastLocRot.z = params.l_rotate.z;    //store the last position
        tween.setParameters(easingCurve, ofxTween::easeOut,params.lastLocRot.z,_ammount, _duration,0);
        params.randLocalRotBoolZ = true; //start the animation
        
    // LOCAL TRANSLATE --------------------------------------     
    } else if (paramName == "/randLocalTransX" || paramName == "/tweenLocalTransX"){
        params.lastLocTrans.x = params.l_trans.x;    //store the last position
        tween.setParameters(easingCurve, ofxTween::easeOut,params.lastLocTrans.x,_ammount, _duration,0);
        params.randLocalPosBoolX = true; //start the animation
    } else if (paramName == "/randLocalTransY" || paramName == "/tweenLocalTransY"){
        params.lastLocTrans.y = params.l_trans.y;    //store the last position
        tween.setParameters(easingCurve, ofxTween::easeOut,params.lastLocTrans.y,_ammount, _duration,0);
        params.randLocalPosBoolY = true; //start the animation
    } else if (paramName == "/randLocalTransZ" || paramName == "/tweenLocalTransZ"){
        params.lastLocTrans.z = params.l_trans.z;    //store the last position
        tween.setParameters(easingCurve, ofxTween::easeOut,params.lastLocTrans.z,_ammount, _duration,0);
        params.randLocalPosBoolZ = true; //start the animation

    // OBJECT ROTATE --------------------------------------
    } else if (paramName == "/randObjRotX" || paramName == "/tweenObjRotX"){
        params.lastObjRot.x = params.o_rotate.x;    //store the last position
        tween.setParameters(easingCurve, ofxTween::easeOut,params.lastObjRot.x,_ammount, _duration,0);
        params.randObjRotBoolX = true; //start the animation
    } else if (paramName == "/randObjRotY" || paramName == "/tweenObjRotY"){
        params.lastObjRot.y = params.o_rotate.y;    //store the last position
        tween.setParameters(easingCurve, ofxTween::easeOut,params.lastObjRot.y,_ammount, _duration,0);
        params.randObjRotBoolY = true; //start the animation
    } else if (paramName == "/randObjRotZ" || paramName == "/tweenObjRotZ"){
        params.lastObjRot.z = params.o_rotate.z;    //store the last position
        tween.setParameters(easingCurve, ofxTween::easeOut,params.lastObjRot.z,_ammount, _duration,0);
        params.randObjRotBoolZ = true; //start the animation
    }
    

    
}


//--------------------------------------------------------------
//20170118 - add easing

void trackParams::setOSCtween2(guiParams &params, ofxTween &tween, string paramName, ofxEasing &easingCurve, float _ammount, float _duration,int _easingType, int _easingCurveSelector){
    
    
    ofxEasing * myEasingCurve;//pointer to my easing curves.  Once out of scope this is deleted.
    float _from; //value at start
    
    
    switch (_easingCurveSelector){
        case 0:
            myEasingCurve = &easingbounce;
            break;
        case 1:
            myEasingCurve = &easingcirc;
            break;
        case 2:
            myEasingCurve = &easingcubic;
            break;
        case 3:
            myEasingCurve = &easingexpo;
            break;
        case 4:
            myEasingCurve = &easinglinear;
            break;
        case 5:
            myEasingCurve = &easingquad;
            break;
        case 6:
            myEasingCurve = &easingquart;
            break;
        case 7:
            myEasingCurve = &easingquint;
            break;
        case 8:
            myEasingCurve = &easingsine;
            break;
        case 9:
            myEasingCurve = &easinglinear;//supposed to be step
            break;
        default:
            myEasingCurve = &easinglinear;
            break;
            
    }
     
    
    if(paramName == "/start"){
        
        // GLOBAL ROTATE --------------------------------------
    } else if (paramName == "/randGlobalRotX" || paramName == "/tweenGlobalRotX" || paramName == "/tweenGRotX"){
        params.lastGlobalRot.x = params.g_rotate.x;    //store the last position
        _from = params.lastGlobalRot.x;
        params.randGlobalRotBoolX = true; //start the animation        
    } else if (paramName == "/randGlobalRotY" || paramName == "/tweenGlobalRotY" || paramName == "/tweenGRotY"){
        params.lastGlobalRot.y = params.g_rotate.y;    //store the last position
        _from = params.lastGlobalRot.y;
        params.randGlobalRotBoolY = true; //start the animation
    } else if (paramName == "/randGlobalRotZ" || paramName == "/tweenGlobalRotZ" || paramName == "/tweenGRotZ"){
        params.lastGlobalRot.z = params.g_rotate.z;    //store the last position
        _from = params.lastGlobalRot.z;
        params.randGlobalRotBoolZ = true; //start the animation
        
        // GLOBAL TRANSLATE --------------------------------------
    } else if (paramName == "/randGlobalTransX" || paramName == "/tweenGlobalTransX" || paramName == "/tweenGTransX"){
        params.lastGlobalTrans.x = params.g_trans.x;    //store the last position
        _from = params.lastGlobalTrans.x;
        params.randGlobalPosBoolX = true; //start the animation
    } else if (paramName == "/randGlobalTransY" || paramName == "/tweenGlobalTransY" || paramName == "/tweenGTransY"){
        params.lastGlobalTrans.y = params.g_trans.y;    //store the last position
        _from = params.lastGlobalTrans.y;
        params.randGlobalPosBoolY = true; //start the animation
    } else if (paramName == "/randGlobalTransZ" || paramName == "/tweenGlobalTransZ" || paramName == "/tweenGTransZ"){
        params.lastGlobalTrans.z = params.g_trans.z;    //store the last position
        _from = params.lastGlobalTrans.z;
        params.randGlobalPosBoolZ = true; //start the animation
        
        // LOCAL ROTATE --------------------------------------
    } else if (paramName == "/randLocalRotX" || paramName == "/tweenLocalRotX" || paramName == "/tweenLRotX"){
        params.lastLocRot.x = params.l_rotate.x;    //store the last position
        _from = params.lastLocRot.x;
        params.randLocalRotBoolX = true; //start the animation
    } else if (paramName == "/randLocalRotY" || paramName == "/tweenLocalRotY" || paramName == "/tweenLRotY"){
        params.lastLocRot.y = params.l_rotate.y;    //store the last position
        _from = params.lastLocRot.y;
        params.randLocalRotBoolY = true; //start the animation
    } else if (paramName == "/randLocalRotZ" || paramName == "/tweenLocalRotZ" || paramName == "/tweenLRotZ"){
        params.lastLocRot.z = params.l_rotate.z;    //store the last position
        _from = params.lastLocRot.z;
        params.randLocalRotBoolZ = true; //start the animation
        
        // LOCAL TRANSLATE --------------------------------------
    } else if (paramName == "/randLocalTransX" || paramName == "/tweenLocalTransX" || paramName == "/tweenLTransX"){
        params.lastLocTrans.x = params.l_trans.x;    //store the last position
        _from = params.lastLocTrans.x;
        params.randLocalPosBoolX = true; //start the animation
    } else if (paramName == "/randLocalTransY" || paramName == "/tweenLocalTransY" || paramName == "/tweenLTransY"){
        params.lastLocTrans.y = params.l_trans.y;    //store the last position
        _from = params.lastLocTrans.y;
        params.randLocalPosBoolY = true; //start the animation
    } else if (paramName == "/randLocalTransZ" || paramName == "/tweenLocalTransZ" || paramName == "/tweenLTransZ"){
        params.lastLocTrans.z = params.l_trans.z;    //store the last position
        _from = params.lastLocTrans.z;
        params.randLocalPosBoolZ = true; //start the animation
        
        // OBJECT ROTATE --------------------------------------
    } else if (paramName == "/randObjRotX" || paramName == "/tweenObjRotX" || paramName == "/tweenORotX"){
        params.lastObjRot.x = params.o_rotate.x;    //store the last position
        _from = params.lastObjRot.x;
        params.randObjRotBoolX = true; //start the animation
    } else if (paramName == "/randObjRotY" || paramName == "/tweenObjRotY" || paramName == "/tweenORotY"){
        params.lastObjRot.y = params.o_rotate.y;    //store the last position
        _from = params.lastObjRot.y;
        params.randObjRotBoolY = true; //start the animation
    } else if (paramName == "/randObjRotZ" || paramName == "/tweenObjRotZ" || paramName == "/tweenORotZ"){
        params.lastObjRot.z = params.o_rotate.z;    //store the last position
        _from = params.lastObjRot.z;
        params.randObjRotBoolZ = true; //start the animation
    }
    
    //set up the tween
    tween.setParameters(*myEasingCurve, static_cast<ofxTween::ofxEasingType>(_easingType) ,_from,_ammount, _duration,0);
    
}




//--------------------------------------------------------------
void trackParams::setOSCdial(guiParams &params, string paramName, float _value){
    //ofLogNotice("OSC") << "trackParams::setOSCdial " << paramName << " " << _value;
    
    if(paramName == "/start"){
    } else if(paramName == "/localCopies"){
        int _copies = int(_value);
        params.l_copies = _copies;
        float sliceAngle = 360.0/_copies;
        params.l_rotate = ofVec3f(0.0,0.0,sliceAngle);
    } else if(paramName == "/globalCopies"){
        params.g_copies = int(_value);
    } else if(paramName == "/localSlices"){
        params.l_slices = int(_value);
    } else if(paramName == "/mirrorDistance"){
        params.mirror_distance = float(_value);
    } else if(paramName == "/localScale"){
        params.l_scale = float(_value);
    } else if(paramName == "/globalScale"){
        params.g_scale = float(_value);
    } else if(paramName == "/stillFrame"){
        params.stillFrame = int(_value);
        //ofLogNotice("OSC") << "params.stillFrame: " << params.stillFrame;
    } else if(paramName == "/setGlobalRotX"){
        params.g_rotate.x = _value;
    } else if(paramName == "/setGlobalRotY"){
        params.g_rotate.y = _value;
    } else if(paramName == "/setGlobalRotZ"){
        params.g_rotate.z = _value;
    } else if(paramName == "/setGlobalTransX"){
        params.g_trans.x = _value;
    } else if(paramName == "/setGlobalTransY"){
        params.g_trans.y = _value;
    } else if(paramName == "/setGlobalTransZ"){
        params.g_trans.z = _value;
    } else if(paramName == "/setLocalRotX"){
        params.l_rotate.x = _value;
    } else if(paramName == "/setLocalRotY"){
        params.l_rotate.y = _value;
    } else if(paramName == "/setLocalRotZ"){
        params.l_rotate.z = _value;
    } else if(paramName == "/setLocalTransX"){
        params.l_trans.x = _value;
    } else if(paramName == "/setLocalTransY"){
        params.l_trans.y = _value;
    } else if(paramName == "/setLocalTransZ"){
        params.l_trans.z = _value;
    } else if(paramName == "/setObjRotX"){
        params.o_rotate.x = _value;
    } else if(paramName == "/setObjRotY"){
        params.o_rotate.y = _value;
    } else if(paramName == "/setObjRotZ"){
        params.o_rotate.z = _value;
    }
    
}
