//
//  ContactListenser.cpp
//  creature
//
//  Created by Dan on 3/20/14.
//
//


#include <Box2D/Box2D.h>
#include "creature.h"
#include "craft.h"
#include "ContactListener.h"

void ContactListener::BeginContact(b2Contact* contact) {
    
    //check if fixture A was a box
    void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
    if ( bodyUserData )
        static_cast<creature*>( bodyUserData )->startContact();
    
    //check if fixture B was a box
    bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
    if ( bodyUserData )
        static_cast<creature*>( bodyUserData )->startContact();
    
}

void ContactListener::EndContact(b2Contact* contact) {
    
    //check if fixture A was a box
    void* bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
    if ( bodyUserData )
        static_cast<creature*>( bodyUserData )->endContact();
    
    //check if fixture B was a box
    bodyUserData = contact->GetFixtureB()->GetBody()->GetUserData();
    if ( bodyUserData )
        static_cast<creature*>( bodyUserData )->endContact();
    
}