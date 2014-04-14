//
//  CraftContactListener.h
//  creature
//
//  Created by Dan on 3/21/14.
//
//

#pragma once
#include <Box2D/Box2D.h>

class CraftContactListener : public b2ContactListener
{
    void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);
};