//
//  cargo.cpp
//  creature
//
//  Created by Dan on 3/23/14.
//
//

#include "cargo.h"
#include <Box2D/Box2D.h>
#include "cinder/Rand.h"
using namespace ci;


cargo::cargo(const Vec2f &pos, b2World* world, float size ){
    //createMesh();
    mNumContacts = 0;
    mSize = size;
    mPosition = pos;
    mLife = 6020;
    mDead = false;
    mWorld= world;
    mNumContacts = 0;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set( mPosition.x, mPosition.y );
    bodyDef.linearVelocity.Set(0,0);
    bodyDef.angularVelocity = 0;
    bodyDef.fixedRotation =false;
    mBody = mWorld->CreateBody( &bodyDef );
    mBody->SetUserData( this );
    dynamicBox.SetAsBox( size, size);
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.0f;
    fixtureDef.restitution = 0.00f; // bounce
    mBody->CreateFixture( &fixtureDef );
    
}

//


//box1::~box1(){}
void cargo::startContact() { mNumContacts++;
    
}
void cargo::endContact() { //mNumContacts--;
}


void cargo::update(){
    if (mNumContacts == 3||mLife<0){
        mDead =true;
        mWorld->DestroyBody(mBody);
    }
    mLife--;
}


bool cargo::isDead(){
    return mDead;
}



void cargo::draw(){
    Vec2f pos = Vec2f(mBody->GetPosition().x,mBody->GetPosition().y);
    glPushMatrix();
    t = toDegrees( mBody->GetAngle() );
    gl::color(.5,.5,.5);
    gl::translate(pos);
    gl::rotate( t );
    // gl::draw(mMesh);
    Rectf rect(-mSize,-mSize,mSize,mSize);
    gl::drawSolidRect(rect);
    glPopMatrix();
    
}

Vec2f  cargo::getPosition(){
    return Vec2f(mBody->GetPosition().x,mBody->GetPosition().y);
}