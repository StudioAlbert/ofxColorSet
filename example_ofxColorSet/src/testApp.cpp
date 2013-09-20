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
    colorSet.setup("Choose a color set", "settings.xml", ofGetWidth() - 300, 10);
    colorSet.add(guiLblColorSet.setup("ColorSet", ""));
    colorSet.add(guiLblNext.setup("Next", "Right to Next Set"));
    colorSet.add(guiLblPrev.setup("Prev", "Left to Prev Set"));
    colorSet.add(guiLblLoad.setup("Load", "L/l to load from xml"));
    colorSet.add(guiLblSave.setup("Save", "S/s to Save into xml"));
   // colorSet.add(guiAddColorSet.setup("Add a colorset"));
   // colorSet.add(guiAddColor.setup("Add a color"));
    
    colors1.setup("colors 1", "settings.xml", 10, 10);
    colors1.add(guiColor1.set("Color 1",ofColor(100,100,140),ofColor(0,0),ofColor(255,255)));
    colors1.add(guiColor2.set("Color 2",ofColor(100,140,100),ofColor(0,0),ofColor(255,255)));
    colors1.add(guiColor3.set("Color 3",ofColor(140,100,100),ofColor(0,0),ofColor(255,255)));
    colors1.add(guiColor4.set("Color 4",ofColor(140,100,140),ofColor(0,0),ofColor(255,255)));
    
    colors2.setup("colors 2", "settings.xml", 250, 10);
    colors2.add(guiColor5.set("Color 5",ofColor(140,100,140),ofColor(0,0),ofColor(255,255)));
    colors2.add(guiColor6.set("Color 6",ofColor(140,100,140),ofColor(0,0),ofColor(255,255)));
    colors2.add(guiColor7.set("Color 7",ofColor(140,100,140),ofColor(0,0),ofColor(255,255)));
    colors2.add(guiColor8.set("Color 8",ofColor(140,100,140),ofColor(0,0),ofColor(255,255)));
    
    loadFromColorSet();

}

//--------------------------------------------------------------
void testApp::update(){
    
    if(guiAddColorSet){
        m_oColorSet.addSet("toto");
    }
    
    if(guiAddColor){
        m_oColorSet.currentSet().setEndColor(0.5, ofColor(127));
    }
        
    
    // Puts the colors into the current Set
    m_oColorSet.setCurrentSetColor(0, guiColor1);
    m_oColorSet.setCurrentSetColor(1, guiColor2);
    m_oColorSet.setCurrentSetColor(2, guiColor3);
    m_oColorSet.setCurrentSetColor(3, guiColor4);
    m_oColorSet.setCurrentSetColor(4, guiColor5);
    m_oColorSet.setCurrentSetColor(5, guiColor6);
    m_oColorSet.setCurrentSetColor(6, guiColor7);
    m_oColorSet.setCurrentSetColor(7, guiColor8);
    
    guiLblColorSet = m_oColorSet.currentSet().m_name;

}

void testApp::loadFromColorSet(){
    guiColor1 = m_oColorSet.ofxColorSet::getCurrentSetByIndex(0);
    guiColor2 = m_oColorSet.ofxColorSet::getCurrentSetByIndex(1);
    guiColor3 = m_oColorSet.ofxColorSet::getCurrentSetByIndex(2);
    guiColor4 = m_oColorSet.ofxColorSet::getCurrentSetByIndex(3);
    guiColor5 = m_oColorSet.ofxColorSet::getCurrentSetByIndex(4);
    guiColor6 = m_oColorSet.ofxColorSet::getCurrentSetByIndex(5);
    guiColor7 = m_oColorSet.ofxColorSet::getCurrentSetByIndex(6);
    guiColor8 = m_oColorSet.ofxColorSet::getCurrentSetByIndex(7);
}

//--------------------------------------------------------------
void testApp::draw(){

    int step = 50;
    ofBackground(100);

    // GUI -------------------------------------------------
    colorSet.draw();
    colors1.draw();
    colors2.draw();
    
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

// ---------------------------------------
void testApp::keyPressed(int key){
    
}
void testApp::keyReleased(int key){
    // Navigate into your sets
    if(key==OF_KEY_RIGHT){
        m_oColorSet.nextSet();
        loadFromColorSet();
    }
    if(key==OF_KEY_LEFT){
        m_oColorSet.prevSet();
        loadFromColorSet();
    }
    
    // Reload a file
    if(key=='l' || key=='L'){
        ofFileDialogResult   pathToLoad = ofSystemLoadDialog("Select a file to load");
        
        if(pathToLoad.bSuccess){
            pathXml = pathToLoad.getPath();
            m_oColorSet.loadFromXml(pathXml);
        }
        
    }
    
    // Save into file
    if (key=='s' || key=='S'){
        ofFileDialogResult   pathToSave = ofSystemSaveDialog("colorSets.xml", "Select a file to save");
        
        if(pathToSave.bSuccess){
            pathXml = pathToSave.getPath();
            m_oColorSet.saveIntoXml(pathXml);
        }
        
    }
    
   
}
