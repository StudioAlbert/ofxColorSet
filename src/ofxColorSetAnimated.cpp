//
//  ofxColorSetAnimated.cpp
//  example_ofxColorSet
//
//  Created by Dudley Smith on 13/09/13.
//
//

#include "ofxColorSetAnimated.h"


ofxColorSetAnimated::ofxColorSetAnimated(){
    // we start with no desat
    m_fSatRatio=1;
}
ofxColorSetAnimated::~ofxColorSetAnimated(){
}
// COLOR SET ANIMATED --------------------------------------------------------------
ofColor ofxColorSetAnimated::getCurrentSetByIndex(int _index){
    return doAnimation(ofxColorSet::getCurrentSetByIndex(_index));
}

ofColor ofxColorSetAnimated::getCurrentSetByProgress(float _progress){
    return doAnimation(ofxColorSet::getCurrentSetByProgress(_progress));
}

ofColor ofxColorSetAnimated::doAnimation(ofColor _inColor){
    
    // You can change the hue
    int newHue;
    float timerValue;
    
    if(m_fPeriod==0){
        newHue = fmod(_inColor.getHue() + 255*m_fHueDecay,255);
    }else{
        
        m_oHueAnim.setPeriod(m_fPeriod*1000);
        timerValue = m_oHueAnim.get(0,m_fHueDecay,TIMER_TYPE_SIN);
        
        newHue = fmod(_inColor.getHue() + 255*timerValue,255);
    }
    _inColor.setHue(newHue);
    // You can change saturation
    _inColor.setSaturation(_inColor.getSaturation()*m_fSatRatio);
    
    return _inColor;
}

