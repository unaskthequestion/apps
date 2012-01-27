//
//  VPaint.h
//  llumalaveu_2_3
//
//  Created by roger on 25/01/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#pragma once

#include "ofMain.h"
#include "NanoKtl.h"
#include "ofxOpenCv.h"

class VPaint: public NanoKtl{
public:
    void setup();
    void update();
    void draw(int x=0, int y=0);
    
    void setVideoGrabber(ofVideoGrabber &vg);
    
    void mapMidiInput();
    ofImage filterBlack(ofxCvGrayscaleImage &gi);
//    void setColorImage(ofxCvColorImage &ci);
//    void setFilteredImage(ofxCvColorImage &ci);
//    void setGrayImage(ofxCvGrayscaleImage &gi);
//    void setGrayBg(ofxCvGrayscaleImage &gi);
//    void setGrayDiff(ofxCvGrayscaleImage &gi);
    
    bool bLiveVideo;
    
    int red, green, blue, alpha;
    int hue, sat, val;
    bool bBrushDown, bStamp;
    int canvasWidth, canvasHeight;
    int width, height;
    
    ofFbo fbo;
    ofVideoGrabber      vidGrabber;
    ofxCvColorImage     colorImage;
    ofxCvColorImage     filteredImage;
    ofxCvGrayscaleImage grayImage;
    ofxCvGrayscaleImage grayBg;
    ofxCvGrayscaleImage grayDiff;
    ofxCvContourFinder  contourFinder;
    
};