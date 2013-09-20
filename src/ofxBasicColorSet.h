//
//  ofxBasicColorSet.h
//  pointPickerExample
//
//  Created by Dudley Smith on 14/09/13.
//
//

#pragma once

#include "ofMain.h"

#define TAG_ColorSet "colorSet"
#define TAG_Root_ColorSets "colorSets"

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

private:
    vector<oneColor> m_colors;
public:
    oneColor getColorLoop(int _index);
    oneColor getColorNoLoop(int _index);
    oneColor getColorByProba();
    oneColor getColorByProgress(float _progress);
    
public:
    int getSize();

public:
    void setColor(int _index, oneColor _color);
    void setColor(int _index, ofColor color);

    void setEndColor(oneColor _color);
    void setEndColor(float proba, ofColor color);
    
private:
    void addColor(oneColor proba);
    void addColor(float proba, ofColor color);
    void addColorRGB(float proba, int _r, int _g, int _b, int _a=255);
    void addColorHSB(float proba, int _h, int _s, int _b, int _a=255);
    
    ofColor colorMix(float _ratio, ofColor _color1, ofColor _color2);
    
};
