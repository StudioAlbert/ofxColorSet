#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    ofSetBackgroundColor(50);
    ofSetVerticalSync(true);
    ofSetFrameRate(25);

    m_oColorSet.loadFromXml("ColorSets.xml");
    
    // QQES SLIDERS --
    gui.setup("Choose a color set");
    
    gui.add(guiNext.setup("Next"));
    gui.add(guiPrev.setup("Prev"));
    gui.add(guiLblColorSet.setup("ColorSet", ""));
            
    gui.add(  guiBtnLoad.setup("Load colors from set"));
    gui.add(  guiColor_1.setup("Color 1",ofColor(100,100,140),ofColor(0,0),ofColor(255,255)));
    gui.add(  guiColor_2.setup("Color 2",ofColor(100,140,100),ofColor(0,0),ofColor(255,255)));
    gui.add(  guiColor_3.setup("Color 3",ofColor(140,100,100),ofColor(0,0),ofColor(255,255)));
    gui.add(  guiColor_4.setup("Color 4",ofColor(140,100,140),ofColor(0,0),ofColor(255,255)));

}

//--------------------------------------------------------------
void testApp::update(){
    
    if(guiNext){
        m_oColorSet.nextSet();
        loadFromColorSet();
    }
    if(guiPrev){
        m_oColorSet.prevSet();
        loadFromColorSet();
    }
    
        // Reload Colors
    if(guiBtnLoad){
        loadFromColorSet();

    }else{

        m_oColorSet.m_currentSet = m_oColorSet.m_currentSet;

        m_oColorSet.setCurrentSetColor(0, guiColor_1);
        m_oColorSet.setCurrentSetColor(1, guiColor_2);
        m_oColorSet.setCurrentSetColor(2, guiColor_3);
        m_oColorSet.setCurrentSetColor(3, guiColor_4);
        
    }

    guiLblColorSet = m_oColorSet.currentSet().m_name;

}

void testApp::loadFromColorSet(){
    guiColor_1 = m_oColorSet.ofxColorSet::getCurrentSetByIndex(0);
    guiColor_2 = m_oColorSet.ofxColorSet::getCurrentSetByIndex(1);
    guiColor_3 = m_oColorSet.ofxColorSet::getCurrentSetByIndex(2);
    guiColor_4 = m_oColorSet.ofxColorSet::getCurrentSetByIndex(3);
}

//--------------------------------------------------------------
void testApp::draw(){

    int step = 50;
    ofBackground(100);

    // GUI -------------------------------------------------
    gui.draw();
    
    //DEMONSTRATION OF COLOR SET ---------------------------
    ofPushStyle();

        ofEnableAlphaBlending();
        ofEnableSmoothing();
        ofSetCircleResolution(36);

     ofPushMatrix();
       ofTranslate(0.75*ofGetWidth(),0.6*ofGetHeight());

        for(int idxColor=0;idxColor<m_oColorSet.currentSet().getSize();idxColor++){
            ofRotate(360*((float)idxColor/(float)m_oColorSet.currentSet().getSize()));
            ofSetColor(m_oColorSet.getCurrentSetByIndex(idxColor));
            ofCircle(0,-0.75*step,step);
        }
    
    ofPopMatrix();

    ofPushMatrix();
        int height = 20;
        int width = 0.4*ofGetWidth();
        float progress;

        ofTranslate(0.75*ofGetWidth() - 0.5*width,ofGetHeight()-2.5*height);

        for(int idxColor=0;idxColor<width;idxColor++){
            progress = (float)idxColor/(float)width;
            ofSetColor(m_oColorSet.getCurrentSetByProgress(progress));
            ofSetLineWidth(1);
            ofLine(idxColor,0,idxColor,height);
        }
    ofPopMatrix();

    ofPushMatrix();

        height = 20;
        width = 0.4*ofGetWidth();

        ofTranslate(0.75*ofGetWidth() - 0.5*width,ofGetHeight()-1.5*height);

        for(int idxColor=0;idxColor<width;idxColor++){
            ofSetColor(m_oColorSet.getCurrentSetByProba());
            ofSetLineWidth(1);
            ofLine(idxColor,0,idxColor,height);
        }
    ofPopMatrix();

    ofPopStyle();
    
}

