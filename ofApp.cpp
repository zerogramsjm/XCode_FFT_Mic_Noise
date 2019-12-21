//JEVON MAHONEY
//CAMFUCK
//LETS DO THIS
//YOUR NOT MY SUPERVISOR

//30/08/16

#include "ofApp.h"

void ofApp::audioReceived     (float * input, int bufferSize, int nChannels){
    // samples are "interleaved"
    for (int i = 0; i < bufferSize; i++){
        rise[i] = input[i*2];
    }
    bufferCounter++;
}

//--------------------------------------------------------------
void ofApp::setup(){
    
    srand((unsigned int)time((time_t *)NULL));
    
    // 0 output channels,
    // 2 input channels
    // 44100 samples per second
    // BUFFER_SIZE samples per buffer
    // 4 num buffers (latency)
    
    ofSoundStreamSetup(0,2,this, 44100 ,BUFFER_SIZE, 4);
    
    rise = new float[BUFFER_SIZE];
    ofToggleFullscreen();
    sphere.setRadius(100);
    sphere.setResolution(50);
    
    sphere.setPosition(ofGetWidth()/2,ofGetHeight()/2,500);
    
    planet = sphere.getMesh();
    
    soundStream.printDeviceList();
    
    soundStream.setDeviceID(0);
    
    //ofHideCursor();
    
    beat.load("sounds/Q.mp3");
    
    beat2.load("sounds/spring.mp3");
    
    beat3.load("sounds/den.mp3");
    
    beat4.load("sounds/for.mp3");
    
    fftSmoothed = new float[8192];
    
    for (int i = 0; i < 8192; i++){
        
    }
    
    for (int i1 = 0; i1 < 8192; i1++){
        
    }
    
    for (int i2 = 0; i2 < 8192; i2++){
        
    }
    
    for (int i3 = 0; i3 < 8192; i3++){
        
    }
    
    for (int i4 = 0; i4 < 8192; i4++){
        
    }
    
    nBandsToGet = 1;
    
    nBandsToGet1 = 6;
    
    nBandsToGet2 =  11;
    
    nBandsToGet3 =  20;
    
    nBandsToGet4 =  2;
    
    ofSetFrameRate(180);
    ofSetVerticalSync(true);
    
    camerause = true;
    
    //CAM POSITIONS
    
    pos1 = ofGetHeight()/2;
    
    pos2 = ofGetWidth()/2;
    
    pos3 = 400;
    
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    
    theColour = 255,0,0;
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    ofSoundUpdate();
    
    float * val = ofSoundGetSpectrum(nBandsToGet);
    for (int i = 0;i < nBandsToGet; i++){
        
        fftSmoothed[i] *= 0.96f;
        
        if (fftSmoothed[i] < val[i]) fftSmoothed[i] = val[i];
        
    }
    
    float * val1 = ofSoundGetSpectrum(nBandsToGet1);
    for (int i = 0;i < nBandsToGet1; i++){
        
        fftSmoothed[i] *= 0.96f;
        
        if (fftSmoothed[i] < val[i]) fftSmoothed[i] = val1[i];
        
    }
    
    float * val2 = ofSoundGetSpectrum(nBandsToGet2);
    for (int i = 0;i < nBandsToGet2; i++){
        
        fftSmoothed[i] *= 0.96f;
        
        if (fftSmoothed[i] < val[i]) fftSmoothed[i] = val2[i];
        
    }
    
    float * val3 = ofSoundGetSpectrum(nBandsToGet3);
    for (int i = 0;i < nBandsToGet3; i++){
        
        fftSmoothed[i] *= 0.96f;
        
        if (fftSmoothed[i] < val[i]) fftSmoothed[i] = val3[i];
        
    }
    
    float * val4 = ofSoundGetSpectrum(nBandsToGet4);
    for (int i = 0;i < nBandsToGet4; i++){
        
        fftSmoothed[i] *= 0.96f;
        
        if (fftSmoothed[i] < val[i]) fftSmoothed[i] = val4[i];
        
    }
    
    for (int i1 = 0;i1 < nBandsToGet; i1++){
        
        for (int i2 = 5;i2 < nBandsToGet1; i2++){
            
            for (int i3 = 10;i3 < nBandsToGet2; i3++){
                
                for (int i5 = 19;i5 < nBandsToGet3; i5++){
                    
                    for (int i4 = 1;i4 < nBandsToGet4; i4++){
                        
                        ofSetBackgroundColor(0 - rise[i1] * 5, 0 - rise[i1] * 5, 0 - rise[i1] * 5);
                        
                        //                        ofBackground(0 + rise[i1]*40, 0 + rise[i1]*40, 0 + rise[i1]*40);
                        glPointSize(5);
                        
                        planet.setMode(OF_PRIMITIVE_LINES);
                        
                        float liquidness = rise[i1] * 2000;
                        
                        float amplitude = .3;
                        
                        float speedDampen = rise[i4] * 5000 + rise[i2] * 5000 - rise[i5] * 5000;
                        
                        auto verts = planet.getVertices();
                        
                        for(unsigned int i = 0; i < verts.size(); i++){
                            verts[i].x += ofSignedNoise(verts[i].x/liquidness, verts[i].y/liquidness,verts[i].z/liquidness, ofGetElapsedTimef()/speedDampen)*amplitude;
                            verts[i].y += ofSignedNoise(verts[i].z/liquidness, verts[i].x/liquidness,verts[i].y/liquidness, ofGetElapsedTimef()/speedDampen)*amplitude;
                            verts[i].z += ofSignedNoise(verts[i].y/liquidness, verts[i].z/liquidness,verts[i].x/liquidness, ofGetElapsedTimef()/speedDampen)*amplitude;
                        }
                    }
                }
            }
        }
    }
}
//--------------------------------------------------------------

void ofApp::draw(){
    
    cam.begin();
    cam.orbit(ofGetElapsedTimef()* 5, ofGetElapsedTimef()* 5, 300);
    planet.drawFaces();
    cam.end();
    
    //  sphere.drawWireframe()
    
    GLfloat lightOnePosition[] = {0, 50, 20.0, 0.0};
    GLfloat lightOneColor[] = {
        0
        ,0
        ,0
        ,0};
    
    GLfloat lightThreePosition[] = {30, 20, 30, 0.0};
    GLfloat lightThreeColor[] = {
        222
        ,111
        ,111
        ,0};
    
    glLightfv (GL_LIGHT0, GL_POSITION, lightOnePosition);
    glLightfv (GL_LIGHT0, GL_DIFFUSE, lightOneColor);
    glEnable (GL_LIGHT0);
    glEnable (GL_LIGHTING);
    glLightfv (GL_LIGHT2, GL_POSITION, lightThreePosition);
    glLightfv (GL_LIGHT2, GL_DIFFUSE, lightThreeColor);
    glEnable (GL_LIGHT2);
    
    glColorMaterial (GL_FRONT_AND_BACK, GL_DIFFUSE);
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
    switch (key) {
        case'f':
            ofToggleFullscreen();
            break;
    }
    
    if( key == '1')
    {
        beat.play();
    }
    
    if( key == '2')
    {
        beat2.play();
    }
    
    if( key == '3')
    {
        beat3.play();
    }
    
    if( key == '4')
    {
        beat4.play();
    }
    
    if( key == 'x')
    {
        beat.stop();
        beat2.stop();
        beat3.stop();
        beat4.stop();
        
    }
    
    if(key == 'n') {
        points.clear();
        speeds.clear();
    }
    
    if( key == 'o')
    {
        camerause=true;
    }
    
    if( key == 'p')
    {
        camerause=false;
    }
    
    //CAM POSITIONS
    
    if( key == 'x')
    {
        ofDrawGrid(1000, 200, false, false, false, false);
    }
    
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
