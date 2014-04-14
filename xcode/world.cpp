//
//  world.cpp
//  creature
//
//  Created by Dan on 3/20/14.
//
//
#include "cinder/rand.h"
#include "world.h"
#include <Box2D/Box2D.h>
#include "cinder/Rand.h"
#include "cinder/Perlin.h"
using namespace ci;

world::world(b2World* world  ){
    b2BodyDef bodyDef;
    b2Body* groundBody = world->CreateBody(&bodyDef);
    float height = 28;
    b2EdgeShape edgeShape;
    Perlin p;
    float x=0;
    b2Vec2 lastPoint( -60, cinder::app::getWindowHeight()-150+  p.noise(1.0)*height );
    for (int i = 0; i < 3000; i+=15) {
        b2Vec2 thisPoint(i,cinder::app::getWindowHeight()-150+p.noise(x) * height);
        edgeShape.Set( lastPoint, thisPoint );
        thisPoints.push_back(lastPoint);
        lastPoint = thisPoint;
        groundBody->CreateFixture(&edgeShape, 0);
        x+=.2;
    }
    
    b2BodyDef rightBodyDef;
    b2Body* rightSideBody = world->CreateBody(&rightBodyDef);
    b2EdgeShape rightEdgeShape;
    rightEdgeShape.Set(b2Vec2(0,0),  b2Vec2(0,::cinder::app::getWindowHeight()));
    rightSideBody->CreateFixture(&rightEdgeShape, 0);
    b2BodyDef leftBodyDef;
    b2Body* leftSideBody = world->CreateBody(&leftBodyDef);
    b2EdgeShape leftEdgeShape;
    leftEdgeShape.Set(b2Vec2(cinder::app::getWindowWidth(),0),  b2Vec2(cinder::app::getWindowWidth(),::cinder::app::getWindowHeight()));
    leftSideBody->CreateFixture(&leftEdgeShape, 0);
    b2BodyDef topBodyDef;
    b2Body* topSideBody = world->CreateBody(&topBodyDef);
    b2EdgeShape topEdgeShape;
    topEdgeShape.Set(b2Vec2(cinder::app::getWindowWidth(),0),  b2Vec2(0,0));
    topSideBody->CreateFixture(&topEdgeShape, 0);
    
}
void world::draw(){
    std::list<b2Vec2>::iterator it = thisPoints.begin();
    for (int i = 1 ; i<thisPoints.size()-2;i++){
    cinder::gl::lineWidth(1);
    cinder::gl::color(1.0,1.0,1.0);
    ci::Vec2f v1 = ci::Vec2f(it->x,it++->y);
    ci::Vec2f v2 = ci::Vec2f(it->x,it->y);
    ++it;
    ci::Vec2f v3 = ci::Vec2f(it->x,it++->y);
    ci::Vec2f v4 = ci::Vec2f(it->x, it->y);
        it--;
    //it;
   // cinder::gl::drawLine(v1, v2);
    cinder::gl::drawLine(v3,v4);
    float dx = (v2.x-v1.x);
    float dy = (v2.y-v1.y);
    //float nextdx = (v4.x-v3.x);
    //float nextdy = (v4.y-v3.y);
    glPushMatrix();
    cinder::gl::translate(v1);
    cinder::gl::drawLine(2*ci::Vec2f(-dy,dx),ci::Vec2f(dy,-dx)/100);
    //cinder::gl::translate(v4);
        ++it;
        ci::Vec2f v5 = ci::Vec2f(it->x,it++->y);
        ci::Vec2f v6 = ci::Vec2f(it->x, it->y);
  //      float moredx = (v6.x-v5.x);
  //      float moredy = (v6.y-v5.y);
  //  cinder::gl::drawLine(2*ci::Vec2f(-nextdy,nextdx),ci::Vec2f(moredy,-moredx)/100);
   // cinder::gl::drawLine(2*ci::Vec2f(-dy,dx), ci::Vec2f(-nextdy,nextdx));
    glPopMatrix();
        it--;
        it--;
//    points.push_back(Vec2f(-dy+v1.x,dx+v1.y));
    
        
        
    }
//    std::list<ci::Vec2f>::iterator it2 = points.begin();
//    for(int x = 0; x<points.size()-1; x++){
//    cinder::gl::drawLine(ci::Vec2f(it2->x,it2++->y),ci::Vec2f(it2->x, it2->y));
//    }
    



}