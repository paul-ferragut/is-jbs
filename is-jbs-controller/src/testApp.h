#pragma once


#include "ofxOpenNI.h"
#include "ofMain.h"
#include "ofxControlPanel.h"

#include "ofxLibwebsockets.h"


#define MAX_USER 4



struct persona{
    
    public:
    ofPoint centerOfMass;
    //ofPoint floorPos;//2D
    float height;
    ofColor averageColor;
    int tempId;
    int idNumber;
    
};

class testApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
        void exit();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    
    //GUI VARS
    ofxControlPanel gui;
    void setupGUI();
    void updateGUI();
    
    bool debugRGB;
    bool debugDepth;
    
    
    
    // OPENNI
    ofxOpenNI openNIDevices;
    ofTrueTypeFont verdana;
    
    void userEvent(ofxOpenNIUserEvent & event);
    
    //OUTPUT VARS
    vector<persona>persons;
    
    vector<int>IDuser;
    
    int lastUserCount;
    int totalUserCount;
    
    void formatData(vector<persona>);
    void send(int rate);
    
    
    ofxLibwebsockets::Client client;
    
    // websocket methods
    void onConnect( ofxLibwebsockets::Event& args );
    void onOpen( ofxLibwebsockets::Event& args );
    void onClose( ofxLibwebsockets::Event& args );
    void onIdle( ofxLibwebsockets::Event& args );
    void onMessage( ofxLibwebsockets::Event& args );
    void onBroadcast( ofxLibwebsockets::Event& args );
    
    
    
};
