//
//  particle.h
//  creature
//
//  Created by Dan on 3/23/14.
//
//
#pragma once
#include <Box2D/Box2D.h>


class particle {
public:
    particle(){}
    particle(const ci::Vec2f &pos, float angle, int numRays, b2World* world  );
    ~particle(){}
    void draw();
    bool isDead();
    int mNumContacts;
    ci::Vec2f  getPosition();
    float & getAngle();
    ci::Vec2f mPosition;
    b2Body* mBody;
    float mAngle;
    int mNumRays;
    b2World* mWorld;
    b2CircleShape circleShape;

    b2BodyDef bd;
    b2FixtureDef fd;
private:
  
    
};