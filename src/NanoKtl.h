//
//  NanoKtl.h
//  
//  Maps input from a Korg NanoKontrol to whatever you tell it to.
//  Make your class inherit from this one and implement mapMidiInput()
//  You may access the midi data using this variable names: 
//      nanoPort, nanoChannel, nanoId, nanoValue and nanoTimestamp

//  TODO --
//  -   For now it just works on scene 1.  Needs to integrate the others.
//
//  Created by wú::unaskTheQuestion() on 24/01/2012.

#pragma once

#include "ofMain.h"
#include "ofxMidi.h"

#define PORT "nanoKONTROL SLIDER/KNOB"

enum KtlNumbers {
    REC = 44,
    PLAY,
    STOP,
    REW,
    FFW,
    LOOP,
    SCENE = 66,
    SLIDER_1 = 2,
    SLIDER_2,
    SLIDER_3,
    SLIDER_4,
    SLIDER_5,
    SLIDER_6 = 8,
    SLIDER_7,
    SLIDER_8 = 12,
    SLIDER_9,
    KNOB_1 = 14,
    KNOB_2,
    KNOB_3,
    KNOB_4,
    KNOB_5,
    KNOB_6,
    KNOB_7,
    KNOB_8,
    KNOB_9,
    UPPER_BUTTON_1 = 23,
    UPPER_BUTTON_2,
    UPPER_BUTTON_3,
    UPPER_BUTTON_4,
    UPPER_BUTTON_5,
    UPPER_BUTTON_6,
    UPPER_BUTTON_7,
    UPPER_BUTTON_8,
    UPPER_BUTTON_9,
    LOWER_BUTTON_1 = 33,
    LOWER_BUTTON_2,
    LOWER_BUTTON_3,
    LOWER_BUTTON_4,
    LOWER_BUTTON_5,
    LOWER_BUTTON_6,
    LOWER_BUTTON_7,
    LOWER_BUTTON_8,
    LOWER_BUTTON_9
};

class NanoKtl: public ofxMidiListener{
public:  
    ofxMidiIn midiIn;
    
    int     nanoPort, nanoChannel, nanoId, nanoValue;
    double  nanoTimestamp;
    char    msg[255];
    
    
    void setup(){
        midiIn.listPorts();
        midiIn.openPort(PORT);
        midiIn.addListener(this);
        midiIn.setVerbose(false);
    };
    
    void newMidiMessage(ofxMidiEventArgs & eventArgs){
        nanoId      = eventArgs.byteOne;
        nanoValue   = eventArgs.byteTwo;
        nanoPort    = eventArgs.port;
        nanoTimestamp = eventArgs.timestamp;
        
        mapMidiInput();
    };
    
    virtual void mapMidiInput(){
        /* WRITE YOUR CODE HERE WITH SOMETHING LIKE THIS:
         
        switch (id) {
            case PLAY:
                cout << "Play it!" << endl;
                break;
            case REW:
            case FFW:
            case LOOP:
            case STOP:
            case REC:
            case SLIDER_1:
            case KNOB_1:
            case UPPER_BUTTON_1:
            case LOWER_BUTTON_1:
                cout << "New MIDI event! " << nanoId << ": " << value << endl;
                break;
            default:break;
        }*/
        
    };
};