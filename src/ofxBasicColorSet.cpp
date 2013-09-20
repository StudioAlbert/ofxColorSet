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
           
            bool        doIAddTheColor = false;
            string      msg = "";
            
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

ofXml ofxBasicColorSet::saveIntoXml(){
    
    ofXml xml;
    int     idxColor = 0;
    
    vector<oneColor>::iterator colorToSave;
    
    // First put the name -----------------------------------------------
    xml.addChild(TAG_ColorSet);
    xml.setTo(TAG_ColorSet);
    
    xml.addValue("name", m_name);
    //xml.setToPrevSibling();
    
    for(colorToSave=m_colors.begin(); colorToSave!=m_colors.end(); colorToSave++){
    
        xml.addChild("color");
        xml.setTo("color[" + ofToString(idxColor++) + "]");
        
        xml.addValue("probability", ofToString((*colorToSave).m_proba));
        // RGB or HSB ????
        // HSB is my best
        xml.addValue("hue",(*colorToSave).m_color.getHue());
        xml.addValue("saturation",(*colorToSave).m_color.getSaturation());
        xml.addValue("brightness",(*colorToSave).m_color.getBrightness());
        // don't know why, alpha sucks...
        int alpha = (*colorToSave).m_color.a;
        xml.addValue("alpha", alpha);
    
        // go back up
        xml.setToParent();
        
    }
    
    // go back up
    //xml.setToPrevSibling();

    // go back up
    return xml;
    
}

// -----------------------------------------------------------------------------
void ofxBasicColorSet::setColor(int _index, ofColor _color){
    
    oneColor colorToAdd;
    
    colorToAdd.m_color = _color;
    
    setColor(_index, colorToAdd);
}

void ofxBasicColorSet::setColor(int _index, oneColor _color){
    
    if(_index<getSize()){
        m_colors[_index].m_color = _color.m_color;
    }
    
}


void ofxBasicColorSet::setEndColor(oneColor _color){
    addColor(_color);
}

void ofxBasicColorSet::setEndColor(float _proba, ofColor _color){
    addColor(_proba, _color);
}


// ---------------------------------------------------------------------------
void ofxBasicColorSet::addColor(float _proba, ofColor _color){
    
    oneColor colorToAdd;
    
    colorToAdd.m_color = _color;
    colorToAdd.m_proba   = _proba;
    
    addColor(colorToAdd);
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


oneColor ofxBasicColorSet::getColorLoop(int _index){
    
    int noLoopIndex = _index % getSize();
    return getColorNoLoop(_index);
    
}

oneColor ofxBasicColorSet::getColorNoLoop(int _index){

    oneColor toReturn;
    
    if(_index >= getSize()){
        toReturn.m_proba = 1;
        toReturn.m_color = ofColor(0, 0);
    }else{
        toReturn.m_proba = m_colors[_index].m_proba;
        toReturn.m_color = m_colors[_index].m_color;
    }
    
    return toReturn;
    
}

oneColor ofxBasicColorSet::getColorByProba(){

    float tirageProba = ofRandom(0,1);
    float probasSum = 0;
    vector<oneColor>::iterator colorProba;
    
    for(colorProba=m_colors.begin();colorProba!=m_colors.end();colorProba++){
    
        // Sum every proba found until it goes right (at the end it's 1, and it goes right)
        // If sum of every probas of every colors is equal to 1
        probasSum += (*colorProba).m_proba;
        if( tirageProba < probasSum){
            // We stop when the first prob is under the sum (CQFD : the colors are in order of theirs probanilities)
            break;
        }
    }

    return (*colorProba);

}


oneColor ofxBasicColorSet::getColorByProgress(float _progress){
    
    float grandSum = 0;
    float lilSum = 0;
    float relativeRatio = 0;
    
    oneColor colorProba_prev;
    oneColor colorProba_next;
    oneColor returnColor;

    for( int i=0; i<getSize(); i++){
    
        colorProba_prev = m_colors[i];
        //colorProba_next = getColorLoop(i+1);
        
         if(i<getSize()-1){
             colorProba_next = m_colors[i+1];
         }else{
             colorProba_next = m_colors[0];
         }
        
        // Sum every proba found until it goes right (at the end it's 1, and it goes right)
        // If sum of every probas of every colors is equal to 1
        grandSum += colorProba_prev.m_proba;
        if( _progress < grandSum){
            // We stop when the first prob is under the sum (CQFD : the colors are in order of theis probs)
            break;
        }
        lilSum += colorProba_prev.m_proba;
    }

    relativeRatio = abs(_progress-lilSum)/abs(lilSum-grandSum);

    returnColor.m_color = colorMix(relativeRatio, colorProba_prev.m_color, colorProba_next.m_color);
    returnColor.m_proba = 1;
    
    return returnColor;
}

ofColor ofxBasicColorSet::colorMix(float _ratio, ofColor _color1, ofColor _color2){
    
    ofColor mixedColor;
    
    // Mixing 2 colors ---------------------------------------------------------------------
    mixedColor.r = (1-_ratio)*_color1.r + _ratio*_color2.r;
    mixedColor.g = (1-_ratio)*_color1.g + _ratio*_color2.g;
    mixedColor.b = (1-_ratio)*_color1.b + _ratio*_color2.b;
    mixedColor.a = (1-_ratio)*_color1.a + _ratio*_color2.a;
    
    return mixedColor;
    
}
