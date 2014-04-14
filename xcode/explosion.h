//
//  explosion.h
//  creature
//
//  Created by Dan on 3/23/14.
//
//

#pragma once
#include "particle.h"
#include "cinder/TriMesh.h"
#include "cinder/gl/Vbo.h"
#include "cinder/gl/GlslProg.h"
#include <Box2D/Box2D.h>

using namespace ci;

class explosion {
public:
    explosion(){}
    explosion(const ci::Vec2f &pos, int numRays, b2World* world  );
    ~explosion(){}
    void startContact();
    void endContact();
    void update();
    void draw();
    bool isDead();
    int mNumContacts;
    std::list<particle*> explode;
    int mNumRays;
    ci::Vec2f mPosition;
    b2World* mWorld;

private:

};