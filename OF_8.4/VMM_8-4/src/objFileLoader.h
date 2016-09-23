#pragma once

#include "ofMain.h"
#include "bwUtil.h"
#include "ofxJSON.h"

class objFileLoader {
    
    public:

    //meshes and objects
    struct extObjFile {
        ofxJSONElement jsonData;
        bool jsonParsed;
        string jsonFile;
        string name;
        string path;
        int numFiles;
        vector<ofFile> objs;
        vector<ofFile> mtls;
    };
    
    //constructor
    objFileLoader();
    
    void setup(); 
    void loadObjFiles(string _path);
    vector<extObjFile> externalObjFiles;
    vector<string> availObjSeq;
    
    void loadMatCapFiles(string _path);
    vector<string> externalMatCapFiles;
    
    private:
    
};