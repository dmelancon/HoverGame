//
//  craft.cpp
//  creature
//
//  Created by Dan on 3/20/14.
//
//

#include "craft.h"
#include <Box2D/Box2D.h>

craft::craft(const Vec2f &pos, b2World* world ){
    
    mDead = false;
    mWorld = world;
    mPosition = pos;
    bodyDef.type = b2_dynamicBody;
    bodyDef.fixedRotation =true;
    bodyDef.angularDamping = 0.999;
    bodyDef.gravityScale = .9;

    bodyDef.position.Set(mPosition.x,mPosition.y);
    mBody = mWorld->CreateBody(&bodyDef);
    mBody->SetUserData( this );
    polygonShape.SetAsBox(8,4.0f);//4x1 box
    fixtureDef.shape = &polygonShape;
    fixtureDef.density = .5;
    fixtureDef.friction = .0f;
    mBody->CreateFixture(&fixtureDef);
}


void craft::update(){
    if (mNumContacts == 3){
        mDead =true;
        mWorld->DestroyBody(mBody);
    }else{
    float targetHeight =20;
    float springConstant = 60;
    //make the ray at least as long as the target distance
    b2Vec2 startOfRay = mBody->GetWorldPoint( b2Vec2(0, 0.5f));
    b2Vec2 endOfRay = mBody->GetWorldPoint( b2Vec2(0,40) );
  
    CraftCallback callback;
    mWorld->RayCast(&callback, startOfRay, endOfRay);
//    glColor3f(1,0,0);
//    glBegin(GL_LINES);
//    glVertex2f(startOfRay.x, startOfRay.y);
//    glVertex2f(endOfRay.x, endOfRay.y);
//    glEnd();
    if ( callback.m_hit ) {
        float distanceAboveGround = (startOfRay - callback.m_point).Length();
        //dont do anything if too far above ground
        if ( distanceAboveGround < targetHeight ) {
            distanceAboveGround += 0.25f * mBody->GetLinearVelocity().y;
            float distanceAwayFromTargetHeight = targetHeight - distanceAboveGround;
            mBody->ApplyForce( b2Vec2(0,-springConstant*distanceAwayFromTargetHeight),
                                       mBody->GetWorldCenter() );
            mBody->ApplyForce( mBody->GetMass() * -mWorld->GetGravity(), mBody->GetWorldCenter() );
        }
        }
    b2Vec2 startOfRay1 = mBody->GetWorldPoint( b2Vec2(0, -0.5f));
    b2Vec2 endOfRay1 = mBody->GetWorldPoint( b2Vec2(0,-40) );
    
    CraftCallback callback1;
    mWorld->RayCast(&callback1, startOfRay1, endOfRay1);
//    glColor3f(1,0,0);
//    glBegin(GL_LINES);
//    glVertex2f(startOfRay1.x, startOfRay1.y);
//    glVertex2f(endOfRay1.x, endOfRay1.y);
//    glEnd();
    if ( callback1.m_hit ) {
        float distanceAboveGround = (startOfRay1 - callback1.m_point).Length();
        //dont do anything if too far above ground
        if ( distanceAboveGround < targetHeight ) {
            distanceAboveGround += 0.25f * mBody->GetLinearVelocity().y;
            float distanceAwayFromTargetHeight = targetHeight - distanceAboveGround;
            mBody->ApplyForce( b2Vec2(0,springConstant*distanceAwayFromTargetHeight),
                              mBody->GetWorldCenter() );
            mBody->ApplyForce( mBody->GetMass() * -mWorld->GetGravity(), mBody->GetWorldCenter() );
        }
    }
    b2Vec2 startOfRayR = mBody->GetWorldPoint( b2Vec2(.5f, 0));
    b2Vec2 endOfRayR = mBody->GetWorldPoint( b2Vec2(40 ,0) );
    
    CraftCallback callbackR;
    mWorld->RayCast(&callbackR, startOfRayR, endOfRayR);
//    glColor3f(1,0,0);
//    glBegin(GL_LINES);
//    glVertex2f(startOfRayR.x, startOfRayR.y);
//    glVertex2f(endOfRayR.x, endOfRayR.y);
//    glEnd();
    if ( callbackR.m_hit ) {
        float distanceAboveGround = (startOfRayR - callbackR.m_point).Length();
        //dont do anything if too far above ground
        if ( distanceAboveGround < targetHeight ) {
            distanceAboveGround += 0.5f * mBody->GetLinearVelocity().x;
            float distanceAwayFromTargetHeight = targetHeight - distanceAboveGround;
            mBody->ApplyForce( b2Vec2(0,springConstant*distanceAwayFromTargetHeight),
                              mBody->GetWorldCenter() );
            //mBody->ApplyForce( mBody->GetMass() * -mWorld->GetGravity(), mBody->GetWorldCenter() );
        }
    }
    b2Vec2 startOfRayL = mBody->GetWorldPoint( b2Vec2(-.5f, 0));
    b2Vec2 endOfRayL = mBody->GetWorldPoint( b2Vec2(-40 ,0) );
    
    CraftCallback callbackL;
    mWorld->RayCast(&callbackL, startOfRayL, endOfRayL);
//    glColor3f(1,0,0);
//    glBegin(GL_LINES);
//    glVertex2f(startOfRayL.x, startOfRayL.y);
//    glVertex2f(endOfRayL.x, endOfRayL.y);
//    glEnd();
    if ( callbackL.m_hit ) {
        float distanceAboveGround = (startOfRayL - callbackL.m_point).Length();
        //dont do anything if too far above ground
        if ( distanceAboveGround < targetHeight ) {
            distanceAboveGround += 0.25f * mBody->GetLinearVelocity().x;
            float distanceAwayFromTargetHeight = targetHeight - distanceAboveGround;
            mBody->ApplyForce( b2Vec2(0,springConstant*distanceAwayFromTargetHeight),
                              mBody->GetWorldCenter() );
            //mBody->ApplyForce( mBody->GetMass() * -mWorld->GetGravity(), mBody->GetWorldCenter() );
        }
    }
    myControlState=0;
    
    }}
void craft::startContact() { mNumContacts++;
    
}
void craft::endContact(){}
bool craft::isDead(){
    return mDead;
}

void craft::drawBox(){
    
    Vec2f pos = Vec2f(mBody->GetPosition().x,mBody->GetPosition().y);
    glPushMatrix();
    t = toDegrees( mBody->GetAngle() );
    gl::translate(pos);
    gl::rotate( t );
    gl::color(1.0,1.0,0);

  //  gl::draw(mMesh);
    Rectf rect(-8,-4.0,8,4.0);
    gl::drawSolidRect( rect );
//    gl::draw( mesh );
    glPopMatrix();
    
    
}

float &craft::getAngle(){
    return t;}
Vec2f  craft::getPosition(){
    return Vec2f(mBody->GetPosition().x,mBody->GetPosition().y);
}
