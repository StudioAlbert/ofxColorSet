#pragma once

#include <set>

#include "ofMain.h"
#include "ofxBasicColorSet.h"

#define noCurrentSet -1

class ofxColorSet{

	public:
        ofxColorSet();
        virtual~ofxColorSet();

    bool loadFromXml(string _xmlFile);
    void saveIntoXml(string _xmlFile);
    
    public:
        int m_currentSet;

    private:
        vector<ofxBasicColorSet>  m_aSets;

        void addSet(ofxBasicColorSet);
    
    
    public:
        void addSet(string _name);
        void addColorToKnownSet(string _name, oneColor proba);
        void addColorToKnownSet_RGB(string _name, float proba, int _r, int _g, int _b, int _a=255);
        void addColorToKnownSet_HSB(string _name, float proba, int _h, int _s, int _b, int _a=255);

        ofColor getCurrentSetByIndex(int _index);
        ofColor getCurrentSetByProba();
        ofColor getCurrentSetByProgress(float _progress);

        void setCurrentSetColor(int _index, ofColor _color);
        void setCurrentSetColorRGB(int _index, float _r, float _g, float _b, float _a=255);
        void setCurrentSetColorHSB(int _index, float _h, float _s, float _b, float _a=255);

        void    changeSetByNum(int _num);
        void    changeSetByName(string _set);
        void    nextSet();
        void    prevSet();

        int     nbSets(){return m_aSets.size();};

        ofxBasicColorSet    currentSet();

        vector<string> getList();

     private:
        ofColor getInSetNumByIndex(int _num, int _index);
        ofColor getInSetNameByIndex(string _name, int _index);

        ofColor getInSetNumByProba(int _num);
        ofColor getInSetByProba(string _name);

        ofColor getInSetNumByProgress(int _num, float _progress);
        ofColor getInSetByProgress(string _name, float _progress);

        ofColor colorMix(float _ratio, ofColor _color1, ofColor _color2);

        private:
            int findNumByName(string _name);
};


