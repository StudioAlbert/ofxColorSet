//
//  ofxBasicColorSet.cpp
//  pointPickerExample
//
//  Created by Dudley Smith on 14/09/13.
//
//

#include "ofxBasicColorSet.h"

ofxBasicColorSet::ofxBasicColorSet(){
    
}

ofxBasicColorSet::~ofxBasicColorSet(){
    
}

ofxBasicColorSet::ofxBasicColorSet( const ofxBasicColorSet& other ) :
m_name( other.m_name), m_colors( other.m_colors )
{
}

bool ofxBasicColorSet::loadFromXml(ofXml &_xml){
    
    oneColor    colorToAdd;
    
    string      msg;
    
    // First get the name -----------------------------------------------
    if(_xml.exists("name")){
        m_name = _xml.getValue("name");
        ofLogVerbose("ofxBasicColorSet") << "Name found : " << m_name;
    }else{
        ofLogError("ofxBasicColorSet") << "No name.";
        return false;
    }
    
    // Check about som colorsetfiles
    if(_xml.exists("color"))
    {
        // This gets the first color
        _xml.setTo("color[0]");
        
        do {
           
            bool doIAddTheColor = false;
            
            if(_xml.exists("probability")){
                colorToAdd.m_proba = _xml.getFloatValue("probability");
                msg += ": proba=" + ofToString(_xml.getFloatValue("probability"));
            }else{
                colorToAdd.m_proba = 0;
            }
            
           // The color can be RGB, or HSB
            if(_xml.exists("red") && _xml.exists("green") && _xml.exists("blue")){
                colorToAdd.m_color.r = _xml.getIntValue("red");
                colorToAdd.m_color.g = _xml.getIntValue("green");
                colorToAdd.m_color.b = _xml.getIntValue("blue");

                doIAddTheColor=true;
                msg += ": RGB=" + ofToString(colorToAdd.m_color.r) + ":" + ofToString(colorToAdd.m_color.g) + ":" + ofToString(colorToAdd.m_color.b);
                
            }else if(_xml.exists("hue") && _xml.exists("saturation") && _xml.exists("brightness")){
                colorToAdd.m_color.setHsb(_xml.getIntValue("hue"),_xml.getIntValue("saturation"),_xml.getIntValue("brightness"));
                
                doIAddTheColor=true;
                msg += ": HSB=" + ofToString(colorToAdd.m_color.getHue())+ ":" + ofToString(colorToAdd.m_color.getSaturation()) + ":" + ofToString(colorToAdd.m_color.getBrightness());

            }
            
            if(_xml.exists("alpha")){
                colorToAdd.m_color.a = _xml.getIntValue("alpha");
                msg += ": Alpha from _xml=" + ofToString(colorToAdd.m_color.a);
            }

            
            if(doIAddTheColor==true){
                addColor(colorToAdd);
                ofLogVerbose("ofxBasicColorSet") << "Color added : " << msg;
            }else{
                ofLogError("ofxBasicColorSet") << "This color is malformed.";
                return false;
            }
            
        }
        while(_xml.setToSibling() ); // go to the next STROKE
        
        // go back up
        _xml.setToParent();
        
    }else{
        ofLogError("ofxBasicColorSet") << "XML empty. no datas.";
        return false;
    }
        
    return true;
    
}

void ofxBasicColorSet::addColorRGB(float _proba, int _r, int _g, int _b, int _a){
    
    oneColor colorToAdd;
    
    colorToAdd.m_color.r = _r;
    colorToAdd.m_color.g = _g;
    colorToAdd.m_color.b = _b;
    colorToAdd.m_color.a = _a;
    colorToAdd.m_proba   = _proba;
    
    addColor(colorToAdd);
    
}

void ofxBasicColorSet::addColorHSB(float _proba, int _h, int _s, int _b, int _a){
    
    oneColor colorToAdd;
    
    colorToAdd.m_color.setHsb(_h,_s,_b,_a);
    colorToAdd.m_proba   = _proba;
    
    addColor(colorToAdd);
    
}

void ofxBasicColorSet::addColor(oneColor _color){
    
    vector<oneColor>::iterator colorInsert;

    for(colorInsert=m_colors.begin();colorInsert!=m_colors.end();colorInsert++){
        // Insertion in order of probability (most prob -> less index)
        if((*colorInsert).m_proba<_color.m_proba || colorInsert==m_colors.end()){
            m_colors.insert(colorInsert,_color);
            break;
        }
    }
    
    // No insertion -> insertion in bottom of vector
    if(colorInsert==m_colors.end()){
        m_colors.push_back(_color);
    }
}

int ofxBasicColorSet::getSize(){
    return m_colors.size();
}