//
//  creature.cpp
//  creature
//
//  Created by Dan on 3/20/14.
//
//

#include "creature.h"
#include <Box2D/Box2D.h>
#include "cinder/Rand.h"
using namespace ci;


creature::creature(const Vec2f &pos, b2World* world, float size ){
    //createMesh();
    mNumContacts = 0;
    mSize = size;
    mPosition = pos;
    mLife = 120;
    mDead = false;
    mWorld= world;
    mNumContacts = 0;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set( mPosition.x, mPosition.y );
    bodyDef.linearVelocity.Set(randFloat(-80.0,80.0),randFloat(-80.0,80.0));
    bodyDef.angularVelocity = randFloat(1.0);
    bodyDef.gravityScale = 0;
    mBody = mWorld->CreateBody( &bodyDef );
    mBody->SetUserData( this );
    dynamicBox.SetAsBox( size, size);
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 20.0f;
    fixtureDef.friction = 0.0f;
    fixtureDef.restitution = 0.00f; // bounce
    mBody->CreateFixture( &fixtureDef );
    
}

//


//box1::~box1(){}
void creature::startContact() { mNumContacts++;
    
}
void creature::endContact() { //mNumContacts--;
}


void creature::update(){
    if (mNumContacts == 3||mLife<0){
        mDead =true;
        mWorld->DestroyBody(mBody);
    }
    mLife--;
}


bool creature::isDead(){
    return mDead;
}



void creature::drawBox(){
    Vec2f pos = Vec2f(mBody->GetPosition().x,mBody->GetPosition().y);
    glPushMatrix();
    t = toDegrees( mBody->GetAngle() );
    gl::color(1.0,1.0,1.0);
    gl::translate(pos);
    gl::rotate( t );
   // gl::draw(mMesh);
    Rectf rect(-mSize,-mSize,mSize,mSize);
    gl::drawSolidRect(rect);
    glPopMatrix();
    
}
float &creature::getAngle(){
    return t;}
Vec2f  creature::getPosition(){
    return Vec2f(mBody->GetPosition().x,mBody->GetPosition().y);
}
