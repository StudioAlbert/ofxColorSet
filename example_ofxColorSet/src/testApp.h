#pragma once

#include "ofMain.h"
#include "ofxColorSetAnimated.h"
#include "ofxGui.h"

class testApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void loadFromColorSet();
    
    void keyPressed(int key);
    void keyReleased(int key);
    
private:
    /*
     ofxColorSetAnimated m_colorSet_Base;
     ofxColorSetAnimated m_colorSet_ToSave;
     */
    
    ofxColorSet m_oColorSet;
    
    bool m_loadColorsFromSet;
    
    ofxPanel colorSet;
    ofFloatColor m_color_1;
    ofFloatColor m_color_2;
    ofFloatColor m_color_3;
    ofFloatColor m_color_4;
    ofxLabel    guiLblColorSet;
    
    
    ofxLabel       guiLblNext;
    ofxLabel       guiLblPrev;
    ofxLabel   guiLblLoad;
    ofxLabel   guiLblSave;

    ofxButton   guiAddColorSet;
    ofxButton   guiAddColor;
    
    ofxPanel    colors1;
    ofxPanel    colors2;
    
    ofParameter<ofColor>  guiColor1;
    ofParameter<ofColor>  guiColor2;
    ofParameter<ofColor>  guiColor3;
    ofParameter<ofColor>  guiColor4;
    ofParameter<ofColor>  guiColor5;
    ofParameter<ofColor>  guiColor6;
    ofParameter<ofColor>  guiColor7;
    ofParameter<ofColor>  guiColor8;

    
    string          pathXml;
    
    /*
     float frequency;
     float amplitude;
     */
    
    
};
