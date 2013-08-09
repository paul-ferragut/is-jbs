#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    //GLOBAL
    ofSetLogLevel(OF_LOG_NOTICE);
    //ofSetLogLevel(OF_LOG_WARNING);
    setupGUI();
    
    lastUserCount=0;
    totalUserCount=0;
    
    //OPENNI
    openNIDevices.setup();
    openNIDevices.addDepthGenerator();
    openNIDevices.addImageGenerator();
    openNIDevices.addUserGenerator();
    openNIDevices.setRegister(true);
    openNIDevices.setMirror(true);
    openNIDevices.start();
    
    
    openNIDevices.setMaxNumUsers(MAX_USER); // default is 4
    
    ofAddListener(openNIDevices.userEvent, this, &testApp::userEvent);
    
    ofxOpenNIUser user;
    user.setUseMaskTexture(true);
    user.setUsePointCloud(true);
    user.setPointCloudDrawSize(2); // this is the size of the glPoint that will be drawn for the point cloud
    user.setPointCloudResolution(2); // this is the step size between points for the cloud -> eg., this sets it to every second point
    openNIDevices.setBaseUserClass(user); // this becomes the base class on which tracked users are created
    // allows you to set all tracked user properties to the same type easily
    // and allows you to create your own user class that inherits from ofxOpenNIUser
    
    //bool connected = client.connect( "echo.websocket.org", true );
    bool connected = client.connect( "echo.websocket.org" );

    
    // Uncomment this to connect to the server example!
    
    /*
     ofxLibwebsockets::ClientOptions options = ofxLibwebsockets::defaultClientOptions();
     options.port = 9092;
     options.protocol = "of-protocol";
     bool connected = client.connect( options );
    */
    
    client.addListener(this);
    
    
}

//--------------------------------------------------------------
void testApp::update(){
    openNIDevices.update();
    updateGUI();
    //client.send("Hello");

    
    //int numUsers = openNIDevices.getNumTrackedUsers();
    
    for (int i=0; i<persons.size(); i++) {
    ofxOpenNIUser & user = openNIDevices.getTrackedUser(i);
        persons[i].centerOfMass=user.getCenter();
    }
    
    /*
    persons.clear();
    
    
        ofxOpenNIUser & user = openNIDevices.getTrackedUser(i);
        
        persona tempPerson;
        tempPerson.centerOfMass=user.getCenter();
        tempPerson.tempId=user.getXnID();
        persons.push_back(tempPerson);
    }
    */


    /*
    
    int currentUserNumber=0;
    vector<persona>updatedUser;
    
    for (int i=0; i<numUsers; i++) {
        ofxOpenNIUser & user = openNIDevices.getTrackedUser(i);

        //if (getCenter.x!=0 && getCenter.y!=0 && getCenter.z!=0) {
        
            persona tempUser;
            tempUser.centerOfMass=user.getCenter();
            tempUser.tempId=user.getXnID();
            updatedUser.push_back(tempUser);
        
        IDuser.push_back(user.getXnID());
        cout<<"user"<<user.getXnID()<<endl;
        
            currentUserNumber++;
        //}
    }
        
    //NUMBER OF USER AND ID
    if (lastUserNumber!=currentUserNumber){//if the number of users changed
        
        if (lastUserNumber>currentUserNumber) {//user left
            int diff=lastUserNumber-currentUserNumber;
            cout<<diff<<" user left"<<endl;
            for(int i=0;i<diff;i++){
                
                
                int corresponding=0;
                
                
                for (int i=0; i<IDuser.size(); i++) {
                    bool isStaying=false;
                    for (int j=0; j<updatedUser.size(); j++) {
                        if (IDuser[i]==updatedUser[j].tempId) {
                            isStaying=true;
                        }
                    }
                    if (isStaying==false) {
                        corresponding=i;
                        cout<<"ID LEFT"<<corresponding<<endl;
                    }
                }
                
                IDuser.erase(IDuser.begin()+corresponding);
                updatedUser.erase(updatedUser.begin()+corresponding);// erase the 6th element myvector.erase (myvector.begin()+5);
               
                
            }
        }
        */
        /*
        if (lastUserNumber<currentUserNumber) {//user arrived
            int add=currentUserNumber-lastUserNumber;
            cout<<add<<" user arrived"<<endl;
            for(int i=0;i<add;i++){
                
                //+1
                totalUserNumber++;
                
                //find corresponding userID and position
                int corresponding=0;
                for (int i=0; i<IDuser.size(); i++) {
                    bool isArrived=false;
                    for (int j=0; j<updatedUser.size(); j++) {
                        if (IDuser[i]==updatedUser[j].tempId) {
                            isArrived=true;
                        }
                    }
                    if (isArrived==false) {
                        corresponding=i;
                        cout<<"ID ARRIVED"<<corresponding<<endl;
                    }
                }
                updatedUser[corresponding].idNumber=totalUserNumber;
                
                //userCount.push_back(updatedUser[]);
                //IDuser.push_back(userCount[userCount.size()].idNumber);
            }
        }
         
        
        if (currentUserNumber>0 && lastUserNumber==currentUserNumber) { //if same user number track normally
            for (int i=0; i<userCount.size(); i++) {
                userCount[i]=updatedUser[i];
            }
        }
        
        //update
        lastUserNumber=currentUserNumber;
    }
         */
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(0, 0, 10);
    ofSetColor(255, 255, 255);
    
    if(debugDepth){
        openNIDevices.drawDepth(0, 0, 640, 480);
        
        for (int i=0; i<persons.size(); i++) {
          openNIDevices.drawSkeleton(0, 0, 640, 480,i);
            ofDrawBitmapString("temp ID:"+ofToString(persons[i].tempId)+" ID:"+ofToString(persons[i].idNumber)+" center:"+ofToString(persons[i].centerOfMass), 20,490+(i*20));
        }
    }
    
    if(debugRGB){
        openNIDevices.drawImage(640, 0, 640, 480);

        
    }
    

    for(int i=0;i<persons.size();i++){
        //ofDrawBitmapString("User:"+ofToString(persons[i].idNumber)+" Position"+ofToString(persons[i].centerOfMass), 20,490+(i*20));
    }
    ofDrawBitmapString("Total visitors"+ofToString(totalUserCount), 660,490);
    
    gui.draw();
}

//--------------------------------------------------------------
void testApp::exit(){
    //GUI.saveSettings(<#string xmlFile#>);
    openNIDevices.stop();
}

//--------------------------------------------------------------
void testApp::userEvent(ofxOpenNIUserEvent & event){
    //ofLogNotice() << getUserStatusAsString(event.userStatus) << "for user" << event.id << "from device" << event.deviceID;
    
    int currentUserCount=openNIDevices.getNumTrackedUsers();
    

    if(event.userStatus==USER_TRACKING_STARTED)
    {
        cout<<"new user in"<<endl;
        for(int i=0;i<openNIDevices.getNumTrackedUsers();i++){
        ofxOpenNIUser & user=openNIDevices.getTrackedUser(i);
   //cout<<"event.id"<<event.id<<" user.getXnID"<<user.getXnID()<<endl;
            if(user.getXnID()==event.id){
                persona tempPerson;
                tempPerson.centerOfMass=user.getCenter();
                tempPerson.tempId=user.getXnID();
                
                totalUserCount++;
                tempPerson.idNumber=totalUserCount;
                
                //calculate average color
                //calculate height
                
                persons.push_back(tempPerson);
            }
        }
    }
    
    if(event.userStatus==USER_TRACKING_STOPPED)
    {
        cout<<"user out"<<endl;
        
        ofxOpenNIUser & user = openNIDevices.getTrackedUser(event.id);
        
        for(int i=0;i<persons.size();i++){
            if (persons[i].tempId==user.getXnID()){
                persons.erase(persons.begin()+i);
                cout<<"delete:"<<i<<endl;
            }
        }
    }
    
        /*
        USER_TRACKING_STOPPED,
        USER_TRACKING_STARTED,
        USER_CALIBRATION_STOPPED,
        USER_CALIBRATION_STARTED,
        USER_SKELETON_LOST,
        USER_SKELETON_FOUND
        */
}
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
