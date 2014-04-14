//
//  particleSystem.h
//  Box2d
//
//  Created by Dan on 3/9/14.
//
//

#pragma once
#include "cinder/gl/GlslProg.h"
#include "cinder/gl/Vbo.h"

struct Particle {
    ci::Vec3f mPosition;
    ci::Vec3f mVelocity;
    ci::Vec3f mAcceleration;
    int mLife;
};

class particleSystem {
    
public:
    
    particleSystem();
    particleSystem(int, ci::Vec2f, float);
    ~particleSystem();
    void update();
    void addParticles();
    bool isDead();
    void draw();
    int mSize;
    int mPos;
    float angle;
    ci::gl::VboMeshRef myMesh;

private:
    std::list<Particle> mParticles;

    float x;
};