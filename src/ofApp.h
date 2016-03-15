#pragma once

#include "ofMain.h"
#include "ofxOsc.h"

#define PORT 5000

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void mouseEntered(int x, int y);
    void mouseExited(int x, int y);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofxOscReceiver  oscReceiver;
    ofSerial mySerial;
    const string deviceName = "cu.usbmodem1421";
    string devicePath = "";
    bool indefinite = true;
    bool open = false;
    unsigned char angle_open[4] = "90";
    unsigned char angle_close[4] = "180";
};
