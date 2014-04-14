//
//  CraftCallback.h
//  creature
//
//  Created by Dan on 3/21/14.
//
//
#include <Box2D/Box2D.h>

#pragma once

class CraftCallback : public b2RayCastCallback
{
public:
    CraftCallback();
    float32 ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, float32 fraction);
    bool m_hit;
    b2Vec2 m_point;
};