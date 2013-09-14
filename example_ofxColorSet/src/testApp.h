#pragma once

#include "ofMain.h"
#include "ofxColorSet.h"
#include "ofxGui.h"

class testApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void loadFromColorSet();
    
private:
    /*
     ofdColorSetAnimated m_colorSet_Base;
     ofdColorSetAnimated m_colorSet_ToSave;
     */
    
    ofxColorSet m_oColorSet;
    
    bool m_loadColorsFromSet;
    
    ofFloatColor m_color_1;
    ofFloatColor m_color_2;
    ofFloatColor m_color_3;
    ofFloatColor m_color_4;
    
    ofxPanel gui;
    
    ofxLabel    guiLblColorSet;
    
    ofxButton   guiBtnLoad;
    ofxColorSlider  guiColor_1;
    ofxColorSlider  guiColor_2;
    ofxColorSlider  guiColor_3;
    ofxColorSlider  guiColor_4;
    
    ofxButton       guiNext;
    ofxButton       guiPrev;
    
    /*
     float frequency;
     float amplitude;
     */
    
    
};
