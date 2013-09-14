#include "ofxColorSet.h"


// COLOR SET --------------------------------------------------------------
ofxColorSet::ofxColorSet(){
    m_currentSet = noCurrentSet;
}

bool ofxColorSet::loadFromXml(string _xmlFile){
    
    ofXml   xml;
    ofFile  fileControl(_xmlFile);
    
     
    if(!fileControl.exists()){
        ofLogError("ofxColorSet") << "The file [" << fileControl.getAbsolutePath() << "] does not exist.";
        return false;
    }
    
    if(!xml.load(_xmlFile)){
        ofLogError("ofxColorSet") << "XML file [" << _xmlFile << "] can not be loaded.";
        return false;
    }

    ofLogVerbose("ofxColorSet") << "XML file [" << _xmlFile << "] correctly loaded";
    ofLogVerbose("ofxColorSet") << "XML Content" << endl << xml.toString();

    // Check about som colorsetfiles
    if(xml.exists("colorSet"))
    {
        
        int idxColorSet = 0;
        
        // This gets the first file
        xml.setTo("colorSet[0]");
        
        do {
            ofxBasicColorSet setToAdd;
            
            //ofLogVerbose() << idxColorSet++ << " : " << xml.getValue("name") << ":" << xml.getNumChildren();

            if(setToAdd.loadFromXml(xml)){
                // We can add, the set seems good
                addSet(setToAdd);
            }
        }
        while(xml.setToSibling()); // go to the next STROKE

        // go back up
        xml.setToParent();
    }

 
    return true;
    
}

ofxColorSet::~ofxColorSet(){
}

void ofxColorSet::addSet(string _name){

    ofxBasicColorSet voidSet;

    voidSet.m_name = _name;
    addSet(voidSet);
    
}


void ofxColorSet::addSet(ofxBasicColorSet _set){
    
    m_aSets.push_back(_set);
    m_currentSet = m_aSets.size() - 1;
    
}

void ofxColorSet::addColorToKnownSet_RGB(string _name, float _proba, int _r, int _g, int _b, int _a){

    oneColor colorToAdd;

    colorToAdd.m_color.r = _r;
    colorToAdd.m_color.g = _g;
    colorToAdd.m_color.b = _b;
    colorToAdd.m_color.a = _a;
    colorToAdd.m_proba   = _proba;

    addColorToKnownSet(_name, colorToAdd);

}

void ofxColorSet::addColorToKnownSet_HSB(string _name, float _proba, int _h, int _s, int _b, int _a){

    oneColor colorToAdd;

    colorToAdd.m_color.setHsb(_h,_s,_b,_a);
    colorToAdd.m_proba   = _proba;

    addColorToKnownSet(_name, colorToAdd);

}

void ofxColorSet::addColorToKnownSet(string _name, oneColor _color){

    vector<oneColor>::iterator colorInsert;

    int numFound = findNumByName(_name);
    if(numFound==-1) return;

    m_aSets[numFound].addColor(_color);
    
}

void ofxColorSet::setCurrentSetColorRGB(int _index, float _r, float _g, float _b, float _a){

    ofColor color;
    color.r = _r;
    color.g = _g;
    color.b = _b;
    color.a = _a;

    setCurrentSetColor( _index, color);
};

void ofxColorSet::setCurrentSetColorHSB(int _index, float _h, float _s, float _b, float _a){

    ofColor color;
    color.setHsb(_h,_s,_b,_a);

    setCurrentSetColor( _index, color);
};

void ofxColorSet::setCurrentSetColor(int _index, ofColor _color){

    if(m_currentSet>0 && m_currentSet<m_aSets.size()){
        if(_index<m_aSets[m_currentSet].m_colors.size()){
            m_aSets[m_currentSet].m_colors[_index].m_color = _color;
        }
    }

}

// Get a color in order of probability giving an index
ofColor ofxColorSet::getInSetNameByIndex(string _name, int _index){

    int numFound = findNumByName(_name);

    if(numFound != -1 && numFound<m_aSets.size()){
        getInSetNumByIndex(numFound, _index);
    }

}

// Get a color in order of probability giving an index
ofColor ofxColorSet::getInSetNumByIndex(int _num, int _index){

    if(_num != -1 && _num<m_aSets.size()){

        _index %= m_aSets[_num].m_colors.size();
        return m_aSets[_num].m_colors[_index].m_color;

    }else{
        return ofColor(0);
    }
}

ofColor ofxColorSet::getCurrentSetByIndex(int _index){
    return getInSetNumByIndex(m_currentSet, _index);
}

ofColor ofxColorSet::getCurrentSetByProba(){
    return getInSetNumByProba(m_currentSet);
}

ofColor ofxColorSet::getInSetNumByProba(int _num){

    float tirageProba = ofRandom(0,1);
    float probasSum = 0;
    vector<oneColor>::iterator colorProba;

    for(colorProba=m_aSets[_num].m_colors.begin();colorProba!=m_aSets[_num].m_colors.end();colorProba++){

        // Sum every proba found until it goes right (at the end it's 1, and it goes right)
        // If sum of every probas of every colors is equal to 1
        probasSum += (*colorProba).m_proba;
        if( tirageProba < probasSum){
            // We stop when the first prob is under the sum (CQFD : the colors are in order of theis probs)
            break;
        }
    }

    return (*colorProba).m_color;

}

ofColor ofxColorSet::getCurrentSetByProgress(float _progress){
        return getInSetNumByProgress(m_currentSet, _progress);
}

ofColor ofxColorSet::getInSetByProgress(string _name, float _progress){

    int numFound = findNumByName(_name);

    if(numFound != -1 && numFound<m_aSets.size()){
        getInSetNumByProgress(numFound, _progress);
    }else{
        return ofColor(0);
    }

}

ofColor ofxColorSet::getInSetNumByProgress(int _num, float _progress){

    float grandSum = 0;
    float lilSum = 0;
    float relativeRatio = 0;

    oneColor colorProba_prev;
    oneColor colorProba_next;

    for( int i=0; i<m_aSets[_num].getSize(); i++){

        colorProba_prev = m_aSets[_num].m_colors[i];

        if(i<(m_aSets[_num].getSize()-1)){
            colorProba_next = m_aSets[_num].m_colors[i+1];
        }else{
            colorProba_next = m_aSets[_num].m_colors[0];
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

    return colorMix(relativeRatio, colorProba_prev.m_color, colorProba_next.m_color);

}

// Change current set
void ofxColorSet::changeSetByNum(int _num){

    if(_num >= m_aSets.size())  _num=0;
    if(_num == -1)          _num=m_aSets.size()-1;

    m_currentSet = _num;

}

void ofxColorSet::changeSetByName(string _name){
        changeSetByNum(findNumByName(_name));
}

ofxBasicColorSet ofxColorSet::currentSet(){
    
    ofxBasicColorSet returnSet;
    
    if(m_currentSet!=noCurrentSet){
        returnSet = m_aSets[m_currentSet];
    }
    
    return returnSet;
}

void ofxColorSet::nextSet(){
    changeSetByNum(m_currentSet+1);
}

void ofxColorSet::prevSet(){
    changeSetByNum(m_currentSet-1);
}

int ofxColorSet::findNumByName(string _name){

    int foundNum = -1;
    int num = 0;

    vector<ofxBasicColorSet>::iterator seek;

    for(seek=m_aSets.begin(); seek!=m_aSets.end(); seek++){
        if((*seek).m_name == _name){
            foundNum = num;
            break;
        }
        num++;
    }

    return foundNum;

}

vector<string> ofxColorSet::getList(){

    vector<string> listOfSetsName;

    for(int i=0; i<m_aSets.size(); i++){
        listOfSetsName.push_back(m_aSets[i].m_name);
    }

    return listOfSetsName;

}

ofColor ofxColorSet::colorMix(float _ratio, ofColor _color1, ofColor _color2){

    ofColor mixedColor;

     // Mixing 2 colors ---------------------------------------------------------------------
    mixedColor.r = (1-_ratio)*_color1.r + _ratio*_color2.r;
    mixedColor.g = (1-_ratio)*_color1.g + _ratio*_color2.g;
    mixedColor.b = (1-_ratio)*_color1.b + _ratio*_color2.b;
    mixedColor.a = (1-_ratio)*_color1.a + _ratio*_color2.a;

    return mixedColor;

}
