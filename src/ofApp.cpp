/* This is an example of how to integrate maximilain into openFrameworks,
 including using audio received for input and audio requested for output.
 
 
 You can copy and paste this and use it as a starting example.
 
 */


#include "ofApp.h"



//-------------------------------------------------------------
ofApp::~ofApp() {
    
}


//--------------------------------------------------------------
void ofApp::setup(){
    /* some standard setup stuff*/
    
    ofEnableAlphaBlending();
    ofSetupScreen();
    ofSetVerticalSync(true);
    
    sampleRate 			= 44100; /* Sampling Rate */
    initialBufferSize	= 512;	/* Buffer Size. you have to fill this buffer with sound*/
    
    lofilter = *new Filter(300, 350, "lores");
    hifilter = *new Filter(300, 350, "hires");
    
    buffer = new float[initialBufferSize];
    beat.load(ofToDataPath("song1.wav"));
    screenRatio = (float)ofGetWidth()/(initialBufferSize/2);
    fft.setup(initialBufferSize, initialBufferSize, initialBufferSize);
    ofSoundStreamSetup(2,0,this, sampleRate, initialBufferSize, 4);/* Call this last ! */
}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(30);
    ofSetColor(200, 200, 200);
    for(int i =0; i < fft.bins; i++){
        ofLine(i*screenRatio, ofGetHeight()/2 - 3*fft.magnitudes[i], (i+1)*screenRatio, ofGetHeight()/2 - 3*fft.magnitudes[i+1]);
    }
    lofilter.draw();
}

//--------------------------------------------------------------
void ofApp::audioRequested 	(float * output, int bufferSize, int nChannels){
    
    for (int i = 0; i < bufferSize; i++){
        
        sample=beat.play();

        sample = lofilter.process(sample);
        fft.process(sample);
        mymix.stereo(sample, outputs, 0.5);
        
        output[i*nChannels    ] = outputs[0];
        output[i*nChannels + 1] = outputs[1];
    }
    
}

//--------------------------------------------------------------
void ofApp::audioReceived 	(float * input, int bufferSize, int nChannels){
    
    
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
    if(lofilter.isInBounds(x, y)){
        int filterX = lofilter.x;
        int filterY = lofilter.y;
        int cutoffRange = lofilter.cutOffRange;
        int resRange = lofilter.resRange;
        lofilter.setCutOffValue(((float)(x-filterX)/lofilter.w)*cutoffRange);
        lofilter.setResValue(resRange-(((float)(y-filterY)/lofilter.h)*resRange));
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    if(lofilter.isInBounds(x, y)){
        int filterX = lofilter.x;
        int filterY = lofilter.y;
        int cutoffRange = lofilter.cutOffRange;
        int resRange = lofilter.resRange;
        lofilter.setCutOffValue(((float)(x-filterX)/lofilter.w)*cutoffRange);
        lofilter.setResValue(resRange-(((float)(y-filterY)/lofilter.h)*resRange));
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
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