//
//  CraftCallback.cpp
//  creature
//
//  Created by Dan on 3/21/14.
//
//

#include "CraftCallback.h"


CraftCallback::CraftCallback(){
    m_hit=false;
}

float32 CraftCallback::ReportFixture(b2Fixture* fixture, const b2Vec2& point, const b2Vec2& normal, Float32 fraction)
{
    m_hit = true;
    m_point = point;
    return fraction;
}
