#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

#include <Box2D/Box2D.h>
#include "cinder/Rand.h"
#include "creature.h"
#include "world.h"
#include "craft.h"
#include "ContactListener.h"
#include "cinder/gl/GlslProg.h"
#include "cinder/gl/Fbo.h"
#include "Resources.h"
#include "cinder/gl/Texture.h"
#include "CraftContactListener.h"
#include "particleSystem.h"
#include "cargo.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class creatureApp : public AppNative {
  public:
	void setup();
    void prepareSettings(Settings*);
	void mouseDrag( MouseEvent event );
    void keyDown(KeyEvent  event);
	void update();
	void draw();
    b2World				*mWorld;
    world mGround;
    ContactListener myContactListenerInstance;
    CraftContactListener myCraftContactListenerInstance;
	list<creature*> mCreatures;
    list<craft*> mCrafts;
    list<particleSystem*> ps;
    cargo c;
};
void creatureApp::prepareSettings(cinder::app::AppBasic::Settings *settings){
    settings->setWindowSize(1200,800);
}
void creatureApp::setup()
{
    b2Vec2 gravity( 0.0f,0.3f );
	mWorld = new b2World( gravity );
    mWorld->SetContactListener(&myContactListenerInstance);
    mWorld->SetContactListener(&myCraftContactListenerInstance);

    mGround = world(mWorld);
    for(int i = 0; i<1; i++){
    craft* m = new craft(Vec2f(randFloat(getWindowWidth()),150), mWorld);
    mCrafts.push_back(m);}
    c = cargo(Vec2f(randFloat(getWindowWidth()),450), mWorld,randFloat(5,20));
}



void creatureApp::update()
{
    if (randFloat(1)>.95){
    creature* b1 = new creature(Vec2f(randFloat(getWindowWidth()),randFloat(400)),mWorld, randFloat(2,10));
        mCreatures.push_back(b1);}
    for( int i = 0; i < 10; ++i ){
        mWorld->Step( 1 / 30.0f, 10, 10 );
    }
    for( list<creature*>::iterator boxIt = mCreatures.begin(); boxIt != mCreatures.end(); ) {
        if((*boxIt)->isDead()){
            ps.push_back(new particleSystem(100,(*boxIt)->getPosition(), (*boxIt)->getAngle()));
            boxIt = mCreatures.erase(boxIt);
        }else {
            (*boxIt)->update();
            ++boxIt;
        }
    }
    for( list<craft*>::iterator it = mCrafts.begin(); it != mCrafts.end(); ) {
        if((*it)->isDead()){
        it = mCrafts.erase(it);
        }else {
            (*it)->update();
            ++it;
}
    }
    for( list<particleSystem*>::iterator psIt = ps.begin(); psIt != ps.end();) {
        if((*psIt)->isDead() == true){
            psIt = ps.erase(psIt);}
        else{
            (*psIt)->update();
            ++psIt;
        }
        
    }
    c.update();
}

void creatureApp::mouseDrag( MouseEvent event )
{
    
    
}
void creatureApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 0, 0, 0) );
    mGround.draw();
    for( list<creature*>::iterator boxIt = mCreatures.begin(); boxIt != mCreatures.end(); ++boxIt ) {
        (*boxIt)->drawBox();
	}
    for( list<craft*>::iterator it = mCrafts.begin(); it != mCrafts.end(); ++it ) {
       (*it)->update();
       (*it)->drawBox();}
    
    for( list<particleSystem*>::iterator psIt = ps.begin(); psIt != ps.end(); ++psIt ) {
        (*psIt)->draw();
	}
    c.draw();
}

void creatureApp::keyDown(KeyEvent event)
{
//    
//    float maxLateralVelocity = 10;
//    float maxVerticalVelocity = 10;
//    float lateralForce = 50;
//    float flyForce = 100;
//    
//    b2Vec2 controlForce(0,0);
    for( list<craft*>::iterator it = mCrafts.begin(); it != mCrafts.end(); ++it ) {
//
//    int lateral = (*it)->myControlState & (KeyEvent::KEY_RIGHT|KeyEvent::KEY_LEFT);
//    if ( lateral == KeyEvent::KEY_LEFT && (*it)->mBody->GetLinearVelocity().x > -maxLateralVelocity )
//        controlForce.x = -lateralForce;
//    else if ( lateral == KeyEvent::KEY_RIGHT && (*it)->mBody->GetLinearVelocity().x < maxLateralVelocity )
//        controlForce.x = lateralForce;
//    
//    if ( (*it)->myControlState & KeyEvent::KEY_UP  && (*it)->mBody->GetLinearVelocity().y < maxVerticalVelocity )
//        controlForce.y = flyForce;
//    
//    (*it)->mBody->ApplyForce( controlForce, (*it)->mBody->GetWorldCenter() );
//

    if( event.getCode() == KeyEvent::KEY_RIGHT ) {
        (*it)->mBody->ApplyLinearImpulse( b2Vec2(250,0),(*it)->mBody->GetWorldCenter() );
        console() << "Right Arrow pressed" << std::endl;

    }
    
    else if( event.getCode() == KeyEvent::KEY_LEFT ) {
            (*it)->mBody->ApplyLinearImpulse( b2Vec2(-250,0), (*it)->mBody->GetWorldCenter() );
        }
    
    else if( event.getCode() == KeyEvent::KEY_UP ) {
        (*it)->mBody->ApplyLinearImpulse( b2Vec2(0,-250), (*it)->mBody->GetWorldCenter() );
    }
    
    else if( event.getCode() == KeyEvent::KEY_DOWN ) {
        (*it)->mBody->ApplyLinearImpulse( b2Vec2(0,250), (*it)->mBody->GetWorldCenter() );
    }
    
    }
}
CINDER_APP_NATIVE( creatureApp, RendererGl )
