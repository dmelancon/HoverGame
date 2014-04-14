//
//  craft.h
//  creature
//
//  Created by Dan on 3/20/14.
//
//

#pragma once
#include "CraftCallback.h"
#include "cinder/TriMesh.h"
#include "cinder/gl/Vbo.h"
#include "cinder/gl/GlslProg.h"
#include <Box2D/Box2D.h>

using namespace ci;

class craft {
public:
    craft(){}
    craft(const ci::Vec2f &pos, b2World* world  );
    ~craft(){}
    void startContact();
    void endContact();
    void addBox();
    void update();
    void drawBox();
    bool isDead();
    int mNumContacts;
    Vec2f  getPosition();
    float & getAngle();
    int myControlState;
    b2Body* mBody;
    b2World* mWorld;

private:
    b2BodyDef bodyDef;
    b2PolygonShape polygonShape;
    b2FixtureDef fixtureDef;
    float t;
    ci::Vec2f mPosition;
    int mLife;
    bool mDead;
    cinder::Color col;
    
    
};