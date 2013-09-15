//
//  ofxBasicColorSet.h
//  pointPickerExample
//
//  Created by Dudley Smith on 14/09/13.
//
//

#pragma once

#include "ofMain.h"

typedef struct{
    ofColor m_color;
    float   m_proba;
} oneColor;

class ofxBasicColorSet{
    // ----------------------------------------
public:
    
    ofxBasicColorSet();
    virtual ~ofxBasicColorSet();
    ofxBasicColorSet( const ofxBasicColorSet& other );
    
    bool loadFromXml(ofXml &_xml);
    ofXml saveIntoXml();
    
    string           m_name;
    vector<oneColor> m_colors;
    
    int getSize();
    
    void addColor(oneColor proba);
    void addColorRGB(float proba, int _r, int _g, int _b, int _a=255);
    void addColorHSB(float proba, int _h, int _s, int _b, int _a=255);
    
};
