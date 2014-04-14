//
//  ContactListenser.h
//  creature
//
//  Created by Dan on 3/20/14.
//
//

#pragma once

class ContactListener : public b2ContactListener
{
    void BeginContact(b2Contact* contact);
    void EndContact(b2Contact* contact);
};