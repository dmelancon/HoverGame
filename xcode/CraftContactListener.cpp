//
//  CraftContactListener.cpp
//  creature
//
//  Created by Dan on 3/21/14.
//
//

#include "CraftContactListener.h"
#include <Box2D/Box2D.h>
#include "craft.h"

void CraftContactListener::BeginContact(b2Contact* contact) {
    
    //check if fixture A was a craft
    void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
    if ( bodyUserData )
        static_cast<craft*>( bodyUserData )->startContact();
    
    //check if fixture B was a box
    bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
    if ( bodyUserData )
        static_cast<craft*>( bodyUserData )->startContact();
    
}

void CraftContactListener::EndContact(b2Contact* contact) {
    
    //check if fixture A was a box
    void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
    if ( bodyUserData )
        static_cast<craft*>( bodyUserData )->endContact();
    
    //check if fixture B was a box
    bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
    if ( bodyUserData )
        static_cast<craft*>( bodyUserData )->endContact();
    
}