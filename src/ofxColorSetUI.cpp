//
//  ofxColorSetUI.cpp
//  exampleOfxParticleWorld
//
//  Created by Dudley Smith on 10/01/2014.
//
//

#include "ofxColorSetUI.h"

// ---------------------------------------------------
void ofxColorSetUI::setup(){
    m_gGroup.setName("ColorSet");
    
    m_gGroup.add(m_pxCurrentSet.set("CurrentSet", 0));
    m_gGroup.add(m_pxCurrentSetName.set("No name"));
    
    m_gGroup.add(m_pxColor1.set("Color1", ofColor::blue, ofColor::white, ofColor::black));
    m_gGroup.add(m_pxColor2.set("Color2", ofColor::red, ofColor::white, ofColor::black));
    m_gGroup.add(m_pxColor3.set("Color3", ofColor::green, ofColor::white, ofColor::black));
    m_gGroup.add(m_pxColor4.set("Color4", ofColor::seaShell, ofColor::white, ofColor::black));
    
    
}

// ---------------------------------------------------
void ofxColorSetUI::setNbSets(int _nbSets){
    m_pxCurrentSet.setMax(_nbSets-1);
}