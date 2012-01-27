//
//  VPaint.cpp
//  llumalaveu_2_3
//
//  Created by roger on 25/01/2012.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "VPaint.h"

void VPaint::setup(){
    canvasWidth = 640;
    canvasHeight = 480;
    bLiveVideo = true;
    bBrushDown = false;
    red = green = blue = alpha = 128;
    fbo.allocate(canvasWidth, canvasHeight);
}

void VPaint::update(){
    
}

void VPaint::draw(int x, int y){
    vidGrabber.draw(x,y,width,height);
}

void VPaint::mapMidiInput(){
    
}

ofImage VPaint::filterBlack(ofxCvGrayscaleImage &_grayImage){
    unsigned char * filterPixels = _grayImage.getPixels();
    unsigned char * alphaPixels = new unsigned char [canvasWidth * canvasHeight * 4];
	
	for (int i =0 ; i < canvasWidth * canvasHeight; i++) {
		
		alphaPixels[i*4]   = filterPixels[i];
		alphaPixels[i*4+1] = filterPixels[i];
		alphaPixels[i*4+2] = filterPixels[i];
		
		if (filterPixels[i] > 0) {
			alphaPixels[i*4+3] = 255;
		}else {
			alphaPixels[i*4+3] = 0;
		}
		
    }
    
    ofImage alphaImage;
	alphaImage.setFromPixels(alphaPixels, canvasWidth, canvasHeight, OF_IMAGE_COLOR_ALPHA, true);
    delete alphaPixels;
    
    return alphaImage;
}

void VPaint::setVideoGrabber(ofVideoGrabber &vg){
    vidGrabber = vg;
    width = vidGrabber.getWidth();
    height = vidGrabber.getHeight();
}