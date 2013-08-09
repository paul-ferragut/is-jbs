#include "testApp.h"

GLfloat lightOnePosition[] = {40.0, 40, 100.0, 0.0};
GLfloat lightOneColor[] = {0.99, 0.99, 0.99, 1.0};

GLfloat lightTwoPosition[] = {-40.0, 40, 100.0, 0.0};
GLfloat lightTwoColor[] = {0.99, 0.99, 0.99, 1.0};

//--------------------------------------------------------------
void testApp::setup(){
    //GLOBAL
    ofSetLogLevel(OF_LOG_NOTICE);
    //ofSetLogLevel(OF_LOG_WARNING);
    setupGUI();
    
    bool connected = client.connect( "echo.websocket.org" );

    
    // Uncomment this to connect to the server example!
    
    /*
     ofxLibwebsockets::ClientOptions options = ofxLibwebsockets::defaultClientOptions();
     options.port = 9092;
     options.protocol = "of-protocol";
     bool connected = client.connect( options );
    */
    
    client.addListener(this);
    
    
    
    
    ofSetVerticalSync(true);
    
    //some model / light stuff
    glEnable (GL_DEPTH_TEST);
    glShadeModel (GL_SMOOTH);
    
    /* initialize lighting */
    
    glLightfv (GL_LIGHT0, GL_POSITION, lightOnePosition);
    glLightfv (GL_LIGHT0, GL_DIFFUSE, lightOneColor);
    glEnable (GL_LIGHT0);
    glLightfv (GL_LIGHT1, GL_POSITION, lightTwoPosition);
    glLightfv (GL_LIGHT1, GL_DIFFUSE, lightTwoColor);
    glEnable (GL_LIGHT1);
    glEnable (GL_LIGHTING);
    
    glColorMaterial (GL_FRONT_AND_BACK, GL_DIFFUSE);
    glEnable (GL_COLOR_MATERIAL);
    
    //load the squirrel model - the 3ds and the texture file need to be in the same folder
    spaceModel.loadModel("corridor.3ds");
    
    //you can create as many rotations as you want
    //choose which axis you want it to effect
    //you can update these rotations later on
    spaceModel.setRotation(0, 90, 1, 0, 0);
    spaceModel.setRotation(1, 270, 0, 0, 1);
    spaceModel.setScale(0.05, 0.05, 0.05);
    spaceModel.setPosition(ofGetWidth()/2, ofGetHeight()/2, 0);
    
    
}

//--------------------------------------------------------------
void testApp::update(){
    
    updateGUI();

 
    //spaceModel.setRotation(1, 270 + ofGetElapsedTimef() * 60, 0, 0, 1);
    
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(100, 100, 100);
    ofSetColor(255, 255, 255);
    
gui.draw();

    for(int i=0;i<persons.size();i++){
        //ofDrawBitmapString("User:"+ofToString(persons[i].idNumber)+" Position"+ofToString(persons[i].centerOfMass), 20,490+(i*20));
    }
    ofDrawBitmapString("Total visitors"+ofToString(totalUserCount), 660,490);
    
    
    //lets tumble the world with the mouse
    glPushMatrix();
    
    //draw in middle of the screen
    glTranslatef(ofGetWidth()/2,ofGetHeight()/2,0);
    //tumble according to mouse
    glRotatef(-mouseY,1,0,0);
    glRotatef(mouseX,0,1,0);
    glTranslatef(-ofGetWidth()/2,-ofGetHeight()/2,0);
    
    ofSetColor(255, 255, 255, 255);
    spaceModel.draw();

    
    glPopMatrix();

    
    
    
    
    
}

//--------------------------------------------------------------
void testApp::exit(){
    //GUI.saveSettings(<#string xmlFile#>);

}

//--------------------------------------------------------------

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y){
    
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
gui.mouseDragged(x, y, button);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
gui.mousePressed(x,y,button);
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
    gui.mouseReleased();
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}

//--------------------------------------------------------------
void testApp::formatData(vector<persona>){

}

//--------------------------------------------------------------
void testApp::send(int rate){

}

//--------------------------------------------------------------
void testApp::setupGUI(){
    gui.setup("control", 0, 0, ofGetWidth()/2, ofGetHeight()/2);
    gui.addPanel("view", 1);
    gui.addToggle("draw RGB", "DRAWRGB", true);
    gui.addToggle("draw depth map", "DRAWDEPTHMAP", true);
}

//--------------------------------------------------------------
void testApp::updateGUI(){
    gui.update();
    debugRGB=gui.getValueB("DRAWRGB");
    debugDepth=gui.getValueB("DRAWDEPTHMAP");

}

//--------------------------------------------------------------
void testApp::onConnect( ofxLibwebsockets::Event& args ){
    cout<<"on connected"<<endl;
}

//--------------------------------------------------------------
void testApp::onOpen( ofxLibwebsockets::Event& args ){
    cout<<"on open"<<endl;
}

//--------------------------------------------------------------
void testApp::onClose( ofxLibwebsockets::Event& args ){
    cout<<"on close"<<endl;
}

//--------------------------------------------------------------
void testApp::onIdle( ofxLibwebsockets::Event& args ){
    cout<<"on idle"<<endl;
}

//--------------------------------------------------------------
void testApp::onMessage( ofxLibwebsockets::Event& args ){
    cout<<"got message "<<args.message<<endl;
}

//--------------------------------------------------------------
void testApp::onBroadcast( ofxLibwebsockets::Event& args ){
    cout<<"got broadcast "<<args.message<<endl;
}
