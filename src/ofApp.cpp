#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(0);
    
    bounds = ofRectangle(0,0, ofGetWidth(), ofGetHeight());
    
    radius		= 40;
    strength	= 0.5f;
    
    int pointCount = 500;
    
    for (int i = 0; i < pointCount; i ++) {
        particle p;
        p.setInitialCondition(ofRandom(0, ofGetWidth()), ofRandom(0, ofGetHeight()), 0,0);
        particles.push_back(p);
    }
    
    vector<ofPoint> points;
    for (int i = 0; i < particles.size(); i++) {
        points.push_back(particles[i].pos);
    }
    
    voronoi.setBounds(bounds);
    voronoi.setPoints(points);
    
    voronoi.generate();
}

//--------------------------------------------------------------
void ofApp::update(){
    for(int i = 0; i < particles.size(); i++) {
        particles[i].resetForce();
    }
    
    for (int i = 0; i < particles.size(); i++){
        particles[i].addAttractionForce(ofGetWidth()/2, ofGetHeight()/2, 1500, 1);
        for(int j = 0; j < attractors.size(); j++){
            particles[i].addAttractionForce(attractors[j].x, attractors[j].y, 800, 1);
        }
        for(int j = 0; j < repulsiors.size(); j++){
            particles[i].addRepulsionForce(repulsiors[j].x, repulsiors[j].y, 400, 1);
        }
        for (int j = 0; j < i; j++){
            particles[i].addRepulsionForce(particles[j], 50, 2);
        }
    }
    
    for (int i = 0; i < particles.size(); i++){
        particles[i].addDampingForce();
        particles[i].update();
    }
    
    bounds = ofRectangle(10, 10, ofGetWidth()-20, ofGetHeight()-20);
        
    vector<ofPoint> points;
    for (int i = 0; i < particles.size(); i++) {
        points.push_back(particles[i].pos);
    }
    
    voronoi.setBounds(bounds);
    voronoi.setPoints(points);
    
    voronoi.generate();
}

//--------------------------------------------------------------
void ofApp::draw(){
    vector <ofxVoronoiCell> cells = voronoi.getCells();
    ofRectangle bounds = voronoi.getBounds();
    
    ofSetLineWidth(1);
    ofNoFill();
    
    for(int i=0; i<cells.size(); i++) {
        ofSetColor(0,255,0);
        for(int j=0; j<cells[i].pts.size(); j++) {
            ofPoint lastPt = cells[i].pts[cells[i].pts.size()-1];
            if(j > 0) {
                lastPt = cells[i].pts[j-1];
            }
            ofPoint thisPt = cells[i].pts[j];
            
            if(!isBorder(lastPt) || !isBorder(thisPt)) {
                ofDrawLine(lastPt, thisPt);
            }
        }
        
        ofSetColor(0,255,0);
        ofFill();
        ofDrawCircle(cells[i].pt, 2);
    }
}

//--------------------------------------------------------------
bool ofApp::isBorder(ofPoint _pt){
    ofRectangle bounds = voronoi.getBounds();
    
    return (_pt.x == bounds.x || _pt.x == bounds.x+bounds.width
            || _pt.y == bounds.y || _pt.y == bounds.y+bounds.height);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == '1') {
        attractors.push_back(ofPoint(mouseX,mouseY));
        
        if(attractors.size()>5) {
            attractors.erase(attractors.begin());
        }
    }
    if(key == '2') {
        repulsiors.push_back(ofPoint(mouseX,mouseY));
        
        if(repulsiors.size()>5) {
            repulsiors.erase(repulsiors.begin());
        }
    }
    if(key == ' ') {
        attractors.clear();
        repulsiors.clear();
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
