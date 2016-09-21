#pragma once

#include "ofMain.h"
#include "ofxQuadWarp.h"

#define NUM 3

class ofApp : public ofBaseApp {
    
public:
		
    void setup();
    void update();
    void draw();
    void exit();

    void keyPressed(int key);


    ofxQuadWarp warper[NUM];
    
    int w[NUM];
    int h[NUM];
    int x = 0;
    int y = 0;
    
    ofImage img[NUM];
    ofFbo fbo[NUM];
    

    ofPoint points[10];
    
    ofImage img_;
    vector<ofImage> image;
    vector<ofxQuadWarp> warper_;
    vector<ofFbo> fbo_;

    

    
    
    
};
