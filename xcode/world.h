//
//  world.h
//  creature
//
//  Created by Dan on 3/20/14.
//
//
#include <Box2D/Box2D.h>
#pragma once

class world{
public:
    world(){}
    world( b2World* world  );
    ~world(){}
    void draw();
    std::list<b2Vec2> thisPoints;
    std::list<ci::Vec2f> points;
private:
 

};