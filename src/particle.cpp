#include "particle.h"

particle::particle(){
    setInitialCondition(0,0,0,0);
    damping = 0.05f;
}

void particle::resetForce(){
    frc.set(0,0);
}

void particle::addForce(float x, float y){
    frc.x = frc.x + x;
    frc.y = frc.y + y;
}

void particle::addRepulsionForce(float x, float y, float radius, float scale){
    
    ofVec2f posOfForce;
    posOfForce.set(x,y);
    
    ofVec2f diff	= pos - posOfForce;
    float length	= diff.length();
    
    bool bAmCloseEnough = true;
    if (radius > 0){
        if (length > radius){
            bAmCloseEnough = false;
        }
    }
    
    if (bAmCloseEnough == true){
        float pct = 1 - (length / radius);
        diff.normalize();
        frc.x = frc.x + diff.x * scale * pct;
        frc.y = frc.y + diff.y * scale * pct;
    }
}

void particle::addAttractionForce(float x, float y, float radius, float scale){
    
    ofVec2f posOfForce;
    posOfForce.set(x,y);
    
    ofVec2f diff	= pos - posOfForce;
    float length	= diff.length();
    
    bool bAmCloseEnough = true;
    if (radius > 0){
        if (length > radius){
            bAmCloseEnough = false;
        }
    }
    
    if (bAmCloseEnough == true){
        float pct = 1 - (length / radius);
        diff.normalize();
        frc.x = frc.x - diff.x * scale * pct;
        frc.y = frc.y - diff.y * scale * pct;
    }
}

void particle::addRepulsionForce(particle &p, float radius, float scale){
    
    ofVec2f posOfForce;
    posOfForce.set(p.pos.x,p.pos.y);
    
    ofVec2f diff	= pos - posOfForce;
    float length	= diff.length();
    
    bool bAmCloseEnough = true;
    if (radius > 0){
        if (length > radius){
            bAmCloseEnough = false;
        }
    }
    
    if (bAmCloseEnough == true){
        float pct = 1 - (length / radius);
        diff.normalize();
        frc.x = frc.x + diff.x * scale * pct;
        frc.y = frc.y + diff.y * scale * pct;
        p.frc.x = p.frc.x - diff.x * scale * pct;
        p.frc.y = p.frc.y - diff.y * scale * pct;
    }
}

void particle::addAttractionForce(particle & p, float radius, float scale){
    
    ofVec2f posOfForce;
    posOfForce.set(p.pos.x,p.pos.y);
    
    ofVec2f diff	= pos - posOfForce;
    float length	= diff.length();
    
    bool bAmCloseEnough = true;
    if (radius > 0){
        if (length > radius){
            bAmCloseEnough = false;
        }
    }
    
    if (bAmCloseEnough == true){
        float pct = 1 - (length / radius);
        diff.normalize();
        frc.x = frc.x - diff.x * scale * pct;
        frc.y = frc.y - diff.y * scale * pct;
        p.frc.x = p.frc.x + diff.x * scale * pct;
        p.frc.y = p.frc.y + diff.y * scale * pct;
    }
    
}

void particle::addDampingForce(){
    frc.x = frc.x - vel.x * damping;
    frc.y = frc.y - vel.y * damping;
}

void particle::setInitialCondition(float px, float py, float vx, float vy){
    pos.set(px,py);
    vel.set(vx,vy);
}

void particle::update(){
    vel = vel + frc;
    pos = pos + vel;
}

void particle::draw(){
    ofDrawCircle(pos.x, pos.y, 3);
}

void particle::bounceOffWalls(){
    bool bDampedOnCollision = true;
    bool bDidICollide = false;
    
    float minx = 0;
    float miny = 0;
    float maxx = ofGetWidth();
    float maxy = ofGetHeight();
    
    if (pos.x > maxx){
        pos.x = maxx;
        vel.x *= -1;
        bDidICollide = true;
    } else if (pos.x < minx){
        pos.x = minx;
        vel.x *= -1;
        bDidICollide = true;
    }
    
    if (pos.y > maxy){
        pos.y = maxy;
        vel.y *= -1;
        bDidICollide = true;
    } else if (pos.y < miny){
        pos.y = miny;
        vel.y *= -1;
        bDidICollide = true;
    }
    
    if (bDidICollide == true && bDampedOnCollision == true){
        vel *= 0.3;
    }
}