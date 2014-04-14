//
//  explosion.cpp
//  creature
//
//  Created by Dan on 3/23/14.
//
//
#include "particle.h"

#include "explosion.h"
#include "cinder/Rand.h"

explosion::explosion(const ci::Vec2f &pos, int numRays, b2World* world  ){
    mPosition = pos;
    mWorld = world;
    mNumRays = numRays;
    explode.clear();
    explode.resize(mNumRays);
for (int i = 0; i < mNumRays; i++) {
    float angle = toRadians((i / (float)numRays) * 360);
    particle* p = new particle(mPosition, angle, mNumRays, mWorld);
    explode.push_back(p);
}
}


void explosion::draw(){
    for( std::list<particle*>::iterator it1 = explode.begin(); it1 != explode.end(); ++it1 ) {
        (*it1)->draw();
    }
}

