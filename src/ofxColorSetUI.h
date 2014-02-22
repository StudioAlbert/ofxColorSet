//
//  ofxColorSetUI.h
//  exampleOfxParticleWorld
//
//  Created by Dudley Smith on 10/01/2014.
//
//

#include "ofMain.h"

class ofxColorSetUI {
public:
    void setup();
    
public:
    ofParameterGroup     m_gGroup;
    
private:
    ofParameter<ofColor>  m_pxColor1;
    ofParameter<ofColor>  m_pxColor2;
    ofParameter<ofColor>  m_pxColor3;
    ofParameter<ofColor>  m_pxColor4;
    
    ofColor m_oColor1;
    ofColor m_oColor2;
    ofColor m_oColor3;
    ofColor m_oColor4;
    
    ofParameter<int>      m_pxCurrentSet;
    ofParameter<string>   m_pxCurrentSetName;
    
    ofParameter<bool>    m_pxChange;
    
public:
    void setNbSets(int _nbSets);
    
    ofColor getColor1(){return m_pxColor1;}
    ofColor getColor2(){return m_pxColor2;}
    ofColor getColor3(){return m_pxColor3;}
    ofColor getColor4(){return m_pxColor4;}
    
    void setColor1(ofColor _color){m_pxColor1 = _color;}
    void setColor2(ofColor _color){m_pxColor2 = _color;}
    void setColor3(ofColor _color){m_pxColor3 = _color;}
    void setColor4(ofColor _color){m_pxColor4 = _color;}
    
    int getCurrentSet(){return m_pxCurrentSet;}
    void setCurrentSetName(string _name){m_pxCurrentSetName = _name;}
    void setCurrentSetIdx(int _idx){m_pxCurrentSet = _idx;}
    
    bool getChange(){return m_pxChange;}
    void setChange(bool _change){m_pxChange = _change;}
    
};
