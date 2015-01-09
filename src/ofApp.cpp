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
    
    ofEnableAlphaBlending();
    ofSetupScreen();
    ofSetVerticalSync(true);
    
    sampleRate 			= 44100;
    initialBufferSize	= 512;
    
    //creating new buttons and filters
    numFilters = 2;
    filters = new Filter[numFilters];
    btns = new Button[numFilters];
    filters[0] = *new Filter(100, 200, "lores");
    filters[1] = *new Filter(100, 200, "hires");
    filters[0].activate();
    btns[0] = *new Button(155, 430, "lores");
    btns[1] = *new Button(205, 430, "hires");
    btns[0].activate();
    
    buffer = new float[initialBufferSize];
    
    //loading the song
    beat.load(ofToDataPath("song1.wav"));
    screenRatio = ((float)2*ofGetWidth()/3)/(initialBufferSize/2);
    
    //setting up the FFT
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
    
    //drawing the FFT spectrum.
    for(int i =0; i < fft.bins; i++){
        ofLine(ofGetWidth()/3 + i*screenRatio, ofGetHeight()/3 - 3*fft.magnitudes[i], ofGetWidth()/3 + (i+1)*screenRatio, ofGetHeight()/3 - 3*fft.magnitudes[i+1]);
    }
    
    //drawing the buffer.
    for(int i = 0 ; i < initialBufferSize-1; i++){
        ofLine(ofGetWidth()/3 + i*screenRatio, 2*ofGetHeight()/3 + 50*buffer[i], ofGetWidth()/3 + (i+1)*screenRatio, 2*ofGetHeight()/3 + 50*buffer[i+1]);
    }
    
    //drawing the right box - according to the selected filter.
    for(int i = 0; i < numFilters; i++){
        if(filters[i].isActivated()){
            filters[i].draw();
        }
        //drawing the buttons.
        btns[i].draw();
    }
}

//--------------------------------------------------------------
void ofApp::audioRequested 	(float * output, int bufferSize, int nChannels){
    
    for (int i = 0; i < bufferSize; i++){
        
        sample=beat.play();
        
        //processing the buffer through the filter
        for(int j = 0; j < numFilters; j++){
            if(filters[j].isActivated()){
                sample = filters[j].process(sample);
            }
        }
        
        //process the FFT
        fft.process(sample);
        
        //store the buffer in an array.
        buffer[i] = sample;
        
        //make it stereo.
        mymix.stereo(sample, outputs, 0.5);
        
        output[i*nChannels    ] = outputs[0];
        output[i*nChannels + 1] = outputs[1];
    }
    
}

//--------------------------------------------------------------
void ofApp::audioReceived(float * input, int bufferSize, int nChannels){
    
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
    
    //changing the values of the cutoff and resonance when dragging the mouse.
    for(int i = 0; i < numFilters; i++){
        if(filters[i].isActivated() && filters[i].isInBounds(x, y)){
            int filterX = filters[i].x;
            int filterY = filters[i].y;
            int cutoffRange = filters[i].cutOffRange;
            int resRange = filters[i].resRange;
            filters[i].setCutOffValue(((float)(x-filterX)/filters[i].w)*cutoffRange);
            filters[i].setResValue(resRange-(((float)(y-filterY)/filters[i].h)*resRange));
        }
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    //changing the values of the cutoff and resonance when pressing the mouse.
    for(int i = 0; i < numFilters; i++){
        if(filters[i].isActivated() && filters[i].isInBounds(x, y)){
            int filterX = filters[i].x;
            int filterY = filters[i].y;
            int cutoffRange = filters[i].cutOffRange;
            int resRange = filters[i].resRange;
            filters[i].setCutOffValue(((float)(x-filterX)/filters[i].w)*cutoffRange);
            filters[i].setResValue(resRange-(((float)(y-filterY)/filters[i].h)*resRange));
        }
        //activating/deactivating the buttons when clicked
        else if(btns[i].isInBounds(x, y)){
            btns[i].activate();
            filters[i].activate();
            for(int j = 0 ; j < numFilters; j++){
                if(i!=j){
                    btns[j].deactivate();
                    filters[j].deactivate();
                }
            }
        }
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