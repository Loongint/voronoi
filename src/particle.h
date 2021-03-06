#include "ofMain.h"

class particle {
public:
    particle();
    void resetForce();
    void addForce(float x, float y);
    void addRepulsionForce(float x, float y, float radius, float scale);
    void addAttractionForce(float x, float y, float radius, float scale);
    void addRepulsionForce(particle &p, float radius, float scale);
    void addAttractionForce(particle &p, float radius, float scale);
    
    void addDampingForce();
    
    void setInitialCondition(float px, float py, float vx, float vy);
    void update();
    void draw();
    
    void bounceOffWalls();
    
    float damping;
    
    ofVec2f pos;
    ofVec2f vel;
    ofVec2f frc;
};
