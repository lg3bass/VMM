#include "objFileLoader.h"

//--------------------------------------------------------------
objFileLoader::objFileLoader(){
    
    
}


//--------------------------------------------------------------
void objFileLoader::setup(){
    
    //GET ALL THE PATHS TO THE OBJ FILES
    loadObjFiles("obj");
    loadMatCapFiles("matCap");
    
}


//--------------------------------------------------------------
void objFileLoader::loadObjFiles(string _path){
    
    //get the directories
    string path = _path;
    ofDirectory dir(path);
    dir.listDir();
    
    //run through the dir to collect all the files.
    for(int j=0;j<dir.numFiles();j++){
        
        int fileCounter = 0;
        
        externalObjFiles.push_back(extObjFile());
        //get metadata on file folders
        
        
        externalObjFiles[j].name = dir.getName(j);
        availObjSeq.push_back(externalObjFiles[j].name);
        
        externalObjFiles[j].path = path+"/"+dir.getName(j)+"/";
        
        ofDirectory objDirectory(dir.getPath(j));
        objDirectory.allowExt("obj");
        objDirectory.allowExt("mtl");
        objDirectory.allowExt("json");
        objDirectory.listDir();
        
        //create a vector of files
        vector<ofFile> objDirectoryFiles = objDirectory.getFiles();
        
        for(int k=0;k<objDirectory.size();k++){
            if(objDirectoryFiles[k].getExtension() == "obj"){
                externalObjFiles[j].objs.push_back(ofFile(objDirectoryFiles[k]));
                fileCounter++;
            }
            if(objDirectoryFiles[k].getExtension() == "mtl"){
                externalObjFiles[j].mtls.push_back(ofFile(objDirectoryFiles[k]));
            }
            if(objDirectoryFiles[k].getExtension() == "json"){
                string fn = objDirectoryFiles[k].getFileName();
                externalObjFiles[j].jsonFile = fn;
            }
        }
        
        ofSort(externalObjFiles[j].objs);
        ofSort(externalObjFiles[j].mtls);
        
        //struct: How many files.
        externalObjFiles[j].numFiles = fileCounter;
        
        //load the JSON
        //========================================
        externalObjFiles[j].jsonParsed = externalObjFiles[j].jsonData.open(externalObjFiles[j].path + externalObjFiles[j].jsonFile);
        
        
        //REPORTING
        ofLogNotice("jsonData")<< "==================================";
        ofLogNotice("jsonData")<< "TRACK: " << j;
        ofLogNotice("jsonData")<< "directory/size=" << externalObjFiles[j].name << ":" << objDirectory.size();
        ofLogNotice("jsonData")<< "Number of obj files=" << externalObjFiles[j].objs.size();
        ofLogNotice("jsonData")<< "Directory parsed=" << externalObjFiles[j].jsonParsed;
        ofLogNotice("jsonData")<< "JSON file=" << externalObjFiles[j].path << externalObjFiles[j].jsonFile;
        
        //report the json data
        ofLogVerbose("jsonData")<< index << ": " << externalObjFiles[j].jsonData.getRawString();
        
        
    }//end loop through directory
    
}

//--------------------------------------------------------------
void objFileLoader::loadMatCapFiles(string _path) {

    //get the directories
    string path = _path;
    ofDirectory dir(path);
    dir.allowExt("png");
    dir.allowExt("jpg");
    dir.listDir();
    
    int fileCounter = 0;

    ofLogVerbose("matcap") << "MATCAPS:";
    
    //create a vector of files
    vector<ofFile> matCapDirectoryFiles = dir.getFiles();
    
    //run through the dir to collect all the files.
    for(int j=0;j<matCapDirectoryFiles.size();j++){

        if(matCapDirectoryFiles[j].getExtension() == "png"){
            externalMatCapFiles.push_back(matCapDirectoryFiles[j].getBaseName()+".png");
            fileCounter++;
        }
        if(matCapDirectoryFiles[j].getExtension() == "jpg"){
            externalMatCapFiles.push_back(matCapDirectoryFiles[j].getBaseName()+".jpg");
            fileCounter++;
        }
        
        ofSort(externalMatCapFiles);
        
        ofLogVerbose("matcap") << externalMatCapFiles[j];
    }
    
}