#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    ofSetLogLevel(OF_LOG_VERBOSE);
    
    ofSetBackgroundColor(50);
    ofSetVerticalSync(true);
    ofSetFrameRate(25);

    pathXml = "ColorSets.xml";
    m_oColorSet.loadFromXml(pathXml);
    
    // QQES SLIDERS --
    colorSet.setup("Choose a color set", "settings.xml", 10, 10);
    colorSet.add(guiLblColorSet.setup("ColorSet", ""));
    colorSet.add(guiNext.setup("Next"));
    colorSet.add(guiPrev.setup("Prev"));
    colorSet.add(guiBtnLoad.setup("Load colors from xml"));
    colorSet.add(guiBtnSave.setup("Save colors into xml"));
   // colorSet.add(guiAddColorSet.setup("Add a colorset"));
   // colorSet.add(guiAddColor.setup("Add a color"));
    
    colors.setup("colors", "settings.xml", 250, 10);
    colors.add(guiColor_1.setup("Color 1",ofColor(100,100,140),ofColor(0,0),ofColor(255,255)));
    colors.add(guiColor_2.setup("Color 2",ofColor(100,140,100),ofColor(0,0),ofColor(255,255)));
    colors.add(guiColor_3.setup("Color 3",ofColor(140,100,100),ofColor(0,0),ofColor(255,255)));
    colors.add(guiColor_4.setup("Color 4",ofColor(140,100,140),ofColor(0,0),ofColor(255,255)));
    
    loadFromColorSet();

}

//--------------------------------------------------------------
void testApp::update(){
    
    // Navigate into your sets
    if(guiNext){
        m_oColorSet.nextSet();
        loadFromColorSet();
    }
    if(guiPrev){
        m_oColorSet.prevSet();
        loadFromColorSet();
    }
    
    // Reload a file
    if(guiBtnLoad){
        ofFileDialogResult   pathToLoad = ofSystemLoadDialog("Select a file to load");
        
        if(pathToLoad.bSuccess){
            pathXml = pathToLoad.getPath();
            m_oColorSet.loadFromXml(pathXml);
        }
        
    }
    
    // Save into file
    if (guiBtnSave){
        ofFileDialogResult   pathToSave = ofSystemSaveDialog("colorSets.xml", "Select a file to save");
        
        if(pathToSave.bSuccess){
            pathXml = pathToSave.getPath();
            m_oColorSet.saveIntoXml(pathXml);
        }
        
    }

    if(guiAddColorSet){
        m_oColorSet.addSet("toto");
    }
    
    if(guiAddColor){
        float proba = 0.5;
        ofColor color(127);
        m_oColorSet.currentSet().addColor(proba, color);
    }
        
    
    // Puts the colors into the current Set
    m_oColorSet.setCurrentSetColor(0, guiColor_1);
    m_oColorSet.setCurrentSetColor(1, guiColor_2);
    m_oColorSet.setCurrentSetColor(2, guiColor_3);
    m_oColorSet.setCurrentSetColor(3, guiColor_4);
    
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
    colorSet.draw();
    colors.draw();
    
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

