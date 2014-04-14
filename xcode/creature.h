//
//  creature.h
//  creature
//
//  Created by Dan on 3/20/14.
//
//

#pragma once
#include "cinder/TriMesh.h"
#include "cinder/gl/Vbo.h"
#include "cinder/gl/GlslProg.h"
#include <Box2D/Box2D.h>

using namespace ci;

class creature {
public:
    creature(){}
    creature(const ci::Vec2f &pos, b2World* world , float size );
    ~creature(){}
    void startContact();
    void endContact();
    void update();
    void drawBox();
    bool isDead();
    int mNumContacts;
    Vec2f  getPosition();
    float & getAngle();
    bool mDead;
    float mSize;

private:
    b2Body* mBody;
    b2World* mWorld;
    b2BodyDef bodyDef;
    b2PolygonShape dynamicBox;
    b2FixtureDef fixtureDef;
    float t;
    ci::Vec2f mPosition;
    int mLife;
    cinder::Color col;
    
    
};