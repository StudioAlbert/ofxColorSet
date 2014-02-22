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
    
    m_gGroup.add(m_pxChange.set("Change", true));
    
    m_gGroup.add(m_pxColor1.set("Color1", m_oColor1, ofColor::white, ofColor::black));
    m_gGroup.add(m_pxColor2.set("Color2", m_oColor2, ofColor::white, ofColor::black));
    m_gGroup.add(m_pxColor3.set("Color3", m_oColor3, ofColor::white, ofColor::black));
    m_gGroup.add(m_pxColor4.set("Color4", m_oColor4, ofColor::white, ofColor::black));
    
}

// ---------------------------------------------------
void ofxColorSetUI::setNbSets(int _nbSets){
    m_pxCurrentSet.setMax(_nbSets-1);
}