#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofBackground(0, 0, 0);
    
    vector<ofSerialDeviceInfo> ofsdi = mySerial.getDeviceList();
    int deviceID = -1;
    for (auto it = ofsdi.begin(); it != ofsdi.end(); it++) {
        if (it->getDeviceName() == deviceName){
            deviceID = it->getDeviceID();
            devicePath = it->getDevicePath();
            break;
        }
    }
    if(deviceID == -1){
        std::cerr << "Device " << deviceName << " not found." << std::endl;
        ofApp::exit();
    }
    mySerial.setup(deviceID, 9600);
    
    oscReceiver.setup(PORT);
}

//--------------------------------------------------------------
void ofApp::update(){
    while (oscReceiver.hasWaitingMessages()) {
        ofxOscMessage m;
        oscReceiver.getNextMessage(m);
        
        if (m.getAddress() == "/projector/open") {
            if (indefinite) indefinite = false;
            open = true;
            bool byteWasWritten = mySerial.writeBytes(angle_open, std::strlen((char*)angle_open) + 1);
            if ( !byteWasWritten )
                printf("byte was not written to serial port");
            
        } else if (m.getAddress() == "/projector/close") {
            if (indefinite) indefinite = false;
            open = false;
            unsigned char buf[4] = "180";
            bool byteWasWritten = mySerial.writeBytes(angle_close, std::strlen((char*)angle_close) + 1);
            if ( !byteWasWritten )
                printf("byte was not written to serial port");
        }
    }
    
    if (mySerial.available() > 0) {
        string buf = "";
        while (mySerial.available() > 0) {
            unsigned char result = mySerial.readByte();
            buf += result;
        }
        ofLog( OF_LOG_NOTICE, buf);
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
    int height = 20;
    ofDrawBitmapString(devicePath, 20, height);
    if (!mySerial.isInitialized()){
        ofDrawBitmapString("Serial port is not initialized. Please reopen this program.", 20, height * 2);
    } else {
        ofDrawBitmapString("Listening OSC at Port " + std::to_string(PORT), 20, height * 2);
        if (indefinite){
            ofDrawBitmapString("indefinite", 20, height * 3);
        } else {
            if (open){
                ofDrawBitmapString("open", 20, height * 3);
            } else {
                ofDrawBitmapString("close", 20, height * 3);
            }
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
