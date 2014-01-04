#pragma once

#include <set>
#include "ofMain.h"
#include "ofdTimer.h"
#include "ofxColorSet.h"

class ofxColorSetAnimated : public ofxColorSet{

    public:
        ofxColorSetAnimated();
        virtual~ofxColorSetAnimated();

    private:
        ofdTimer m_oHueAnim;

    public:
        float m_fSatRatio;
        float m_fHueDecay;
        float m_fPeriod;

        ofColor getCurrentSetByIndex(int _index);
        ofColor getCurrentSetByProgress(float _progress);

    private:
        ofColor doAnimation(ofColor _inColor);

};

