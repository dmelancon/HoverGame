//
//  particle.cpp
//  creature
//
//  Created by Dan on 3/23/14.
//
//

#include "particle.h"
#include "cinder/Rand.h"



particle::particle(const ci::Vec2f &pos, float angle, int numRays, b2World* world){
    b2Body* mBody;

    mNumRays = numRays;
//  float angle = toRadians((i / (float)mNumRays) * 360);
    mAngle = angle;
    mWorld = world;
    mPosition = pos;
    float blastPower = cinder::randFloat(30.0f);
    b2Vec2 rayDir( sinf(mAngle), cosf(mAngle) );
    bd.type = b2_dynamicBody;
    bd.fixedRotation = true; // rotation not necessary
    bd.bullet = true; // prevent tunneling at high speed
    bd.linearDamping = 10; // drag due to moving through air
    bd.gravityScale = 0; // ignore gravity
    bd.position.Set(mPosition.x,mPosition.y); // start at blast center
    bd.linearVelocity = blastPower * rayDir;
    mBody = mWorld->CreateBody( &bd );
    // mBody->SetUserData( this );
    circleShape.m_radius = 20.0; // very small
    fd.shape = &circleShape;
    fd.density = 60 / (float)mNumRays; // very high - shared across all particles
    fd.friction = 0; // friction not necessary
    fd.restitution = 0.99f; // high restitution to reflect off obstacles
    fd.filter.groupIndex = -1; // particles should not collide with each other
    mBody->CreateFixture( &fd );
    std::cout<<mBody->GetPosition().x<<std::endl;
    std::cout<<mBody->GetPosition().y<<std::endl;

   }

void particle::draw(){
    
    cinder::Vec2f pos1 = cinder::Vec2f(mBody->GetPosition().x,mBody->GetPosition().y);
    ci::gl::color(1.0,0,0);
    cinder::gl::drawSolidCircle(pos1,20.0);
    
    
}

cinder::Vec2f  particle::getPosition(){
    return cinder::Vec2f(mBody->GetPosition().x,mBody->GetPosition().y);
}