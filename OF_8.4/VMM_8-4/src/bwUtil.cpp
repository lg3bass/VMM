//
//  bwUtil.cpp
//  ofxObjLoader_test2
//
//  Created by White, Bob on 4/13/15.
//
//

#include "bwUtil.h"

namespace bwUtil
{
    //takes an interger and outputs a string with double digits.
    string dDigiter(int i) {
        string output;
        if(i<10){
            output = "0"+ofToString(i);
        } else {
            output = ofToString(i);
        }
        return output;
    }
    
    float presetMidiNotes(float i){
        float returnedMidiNote;
        
        returnedMidiNote = 80-i;
        
        return returnedMidiNote;
    }
    
    int getUniqueRandomInt(int low, int high, int prev){
        int randTest = (int)ofRandom(low,high);
        
        do {
            randTest = (int)ofRandom(low,high);
        } while (randTest == prev);
        
        return randTest;
        
    }
    
    string shortenString(string _input) {
        string outputString = _input.substr (0,31);//31 max characters allowed in ofxUITextArea -- because of width.
        //cout << "OLD:" << _input << "|NEW:" << outputString << endl;
        return outputString;
        
    }
    
}